/*--------------------------------------------------------------------*/
/* dfa.c                                                              */
/* Author: Bob Dondero                                                */
/*--------------------------------------------------------------------*/

#include "dynarray.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/*--------------------------------------------------------------------*/

/* The name of the executable binary file. */
static const char *pcPgmName;

/*--------------------------------------------------------------------*/

/* A Token object can be either a number or a word. */
enum TokenType {TOKEN_NUMBER, TOKEN_WORD};

/*--------------------------------------------------------------------*/

/* A Token is either a number or a word, expressed as a string. */

struct Token
{
   /* The type of the token. */
   enum TokenType eType;

   /* The string which is the token's value. */
   char *pcValue;
};

/*--------------------------------------------------------------------*/

/* If no lines remain in psFile, then return NULL. Otherwise read a line
   of psFile and return it as a string. The string does not contain a
   terminating newline character. The caller owns the string. */

static char *readLine(FILE *psFile)
{
   enum {INITIAL_LINE_LENGTH = 2};
   enum {GROWTH_FACTOR = 2};

   size_t uLineLength = 0;
   size_t uPhysLineLength = INITIAL_LINE_LENGTH;
   char *pcLine;
   int iChar;

   assert(psFile != NULL);

   /* If no lines remain, return NULL. */
   if (feof(psFile))
      return NULL;
   iChar = fgetc(psFile);
   if (iChar == EOF)
      return NULL;

   /* Allocate memory for the string. */
   pcLine = (char*)malloc(uPhysLineLength);
   if (pcLine == NULL)
      {perror(pcPgmName); exit(EXIT_FAILURE);}

   /* Read characters into the string. */
   while ((iChar != '\n') && (iChar != EOF))
   {
      if (uLineLength == uPhysLineLength)
      {
         uPhysLineLength *= GROWTH_FACTOR;
         pcLine = (char*)realloc(pcLine, uPhysLineLength);
         if (pcLine == NULL)
            {perror(pcPgmName); exit(EXIT_FAILURE);}
      }
      pcLine[uLineLength] = (char)iChar;
      uLineLength++;
      iChar = fgetc(psFile);
   }

   /* Append a null character to the string. */
   if (uLineLength == uPhysLineLength)
   {
      uPhysLineLength++;
      pcLine = (char*)realloc(pcLine, uPhysLineLength);
      if (pcLine == NULL)
         {perror(pcPgmName); exit(EXIT_FAILURE);}
   }
   pcLine[uLineLength] = '\0';

   return pcLine;
}

/*--------------------------------------------------------------------*/

/* Write all tokens in oTokens to stdout.  First write the number
   tokens; then write the word tokens. */

static void writeTokens(DynArray_T oTokens)
{
   size_t u;
   size_t uLength;
   struct Token *psToken;

   assert(oTokens != NULL);

   uLength = DynArray_getLength(oTokens);

   printf("Numbers:  ");
   for (u = 0; u < uLength; u++)
   {
      psToken = DynArray_get(oTokens, u);
      if (psToken->eType == TOKEN_NUMBER)
         printf("%s ", psToken->pcValue);
   }
   printf("\n");

   printf("Words:  ");
   for (u = 0; u < uLength; u++)
   {
      psToken = DynArray_get(oTokens, u);
      if (psToken->eType == TOKEN_WORD)
         printf("%s ", psToken->pcValue);
   }
   printf("\n");
}

/*--------------------------------------------------------------------*/

/* Free all of the tokens in oTokens. */

static void freeTokens(DynArray_T oTokens)
{
   size_t u;
   size_t uLength;
   struct Token *psToken;

   assert(oTokens != NULL);

   uLength = DynArray_getLength(oTokens);

   for (u = 0; u < uLength; u++)
   {
      psToken = DynArray_get(oTokens, u);
      free(psToken->pcValue);
      free(psToken);
   }
}

/*--------------------------------------------------------------------*/

/* Create and return a token whose type is eTokenType and whose
   value consists of string pcValue.  The caller owns the token. */

static struct Token *newToken(enum TokenType eTokenType,
   char *pcValue)
{
   struct Token *psToken;

   assert(pcValue != NULL);

   psToken = (struct Token*)malloc(sizeof(struct Token));
   if (psToken == NULL)
      {perror(pcPgmName); exit(EXIT_FAILURE);}
   psToken->eType = eTokenType;
   psToken->pcValue = (char*)malloc(strlen(pcValue) + 1);
   if (psToken->pcValue == NULL)
      {perror(pcPgmName); exit(EXIT_FAILURE);}
   strcpy(psToken->pcValue, pcValue);

   return psToken;
}

/*--------------------------------------------------------------------*/

/* Lexically analyze string pcLine.  If pcLine contains a lexical
   error, then return NULL.  Otherwise return a DynArray object
   containing the tokens in pcLine.  The caller owns the DynArray
   object and the tokens that it contains. */

static DynArray_T lexLine(const char *pcLine)
{
   /* lexLine() uses a DFA approach.  It "reads" its characters from
      pcLine. The DFA has these three states: */
   enum LexState {STATE_START, STATE_IN_NUMBER, STATE_IN_WORD};

   /* The current state of the DFA. */
   enum LexState eState = STATE_START;

   /* An index into pcLine. */
   size_t uLineIndex = 0;

   /* Pointer to a buffer in which the characters comprising each
      token are accumulated. */
   char *pcBuffer;

   /* An index into the buffer. */
   int uBufferIndex = 0;

   char c;
   struct Token *psToken;
   DynArray_T oTokens;
   int iSuccessful;

   assert(pcLine != NULL);

   /* Create an empty token DynArray object. */
   oTokens = DynArray_new(0);
   if (oTokens == NULL)
      {perror(pcPgmName); exit(EXIT_FAILURE);}

   /* Allocate memory for a buffer that is large enough to store the
      largest token that might appear within pcLine. */
   pcBuffer = (char*)malloc(strlen(pcLine) + 1);
   if (pcBuffer == NULL)
      {perror(pcPgmName); exit(EXIT_FAILURE);}

   for (;;)
   {
      /* "Read" the next character from pcLine. */
      c = pcLine[uLineIndex++];

      switch (eState)
      {
         /* Handle the START state. */
         case STATE_START:
            if (c == '\0')
            {
               free(pcBuffer);
               return oTokens;
            }
            else if (isdigit(c))
            {
               pcBuffer[uBufferIndex++] = c;
               eState = STATE_IN_NUMBER;
            }
            else if (isalpha(c))
            {
               pcBuffer[uBufferIndex++] = c;
               eState = STATE_IN_WORD;
            }
            else if (isspace(c))
               eState = STATE_START;
            else
            {
               fprintf(stderr, "Invalid line\n");
               free(pcBuffer);
               freeTokens(oTokens);
               DynArray_free(oTokens);
               return NULL;
            }
            break;

         /* Handle the IN_NUMBER state. */
         case STATE_IN_NUMBER:
            if (c == '\0')
            {
               /* Create a NUMBER token. */
               pcBuffer[uBufferIndex] = '\0';
               psToken = newToken(TOKEN_NUMBER, pcBuffer);
               iSuccessful = DynArray_add(oTokens, psToken);
               if (! iSuccessful)
                  {perror(pcPgmName); exit(EXIT_FAILURE);}
               uBufferIndex = 0;
               free(pcBuffer);
               return oTokens;
            }
            else if (isdigit(c))
            {
               pcBuffer[uBufferIndex++] = c;
               eState = STATE_IN_NUMBER;
            }
            else if (isspace(c))
            {
               /* Create a NUMBER token. */
               pcBuffer[uBufferIndex] = '\0';
               psToken = newToken(TOKEN_NUMBER, pcBuffer);
               iSuccessful = DynArray_add(oTokens, psToken);
               if (! iSuccessful)
                  {perror(pcPgmName); exit(EXIT_FAILURE);}
               uBufferIndex = 0;
               eState = STATE_START;
            }
            else
            {
               fprintf(stderr, "Invalid line\n");
               free(pcBuffer);
               freeTokens(oTokens);
               DynArray_free(oTokens);
               return NULL;
            }
            break;

         /* Handle the IN_WORD state. */
         case STATE_IN_WORD:
            if (c == '\0')
            {
               /* Create a WORD token. */
               pcBuffer[uBufferIndex] = '\0';
               psToken = newToken(TOKEN_WORD, pcBuffer);
               iSuccessful = DynArray_add(oTokens, psToken);
               if (! iSuccessful)
                  {perror(pcPgmName); exit(EXIT_FAILURE);}
               uBufferIndex = 0;
               free(pcBuffer);
               return oTokens;
            }
            else if (isalpha(c))
            {
               pcBuffer[uBufferIndex++] = c;
               eState = STATE_IN_WORD;
            }
            else if (isspace(c))
            {
               /* Create a WORD token. */
               pcBuffer[uBufferIndex] = '\0';
               psToken = newToken(TOKEN_WORD, pcBuffer);
               iSuccessful = DynArray_add(oTokens, psToken);
               if (! iSuccessful)
                  {perror(pcPgmName); exit(EXIT_FAILURE);}
               uBufferIndex = 0;

               eState = STATE_START;
            }
            else
            {
               fprintf(stderr, "Invalid line\n");
               free(pcBuffer);
               freeTokens(oTokens);
               DynArray_free(oTokens);
               return NULL;
            }
            break;

         default:
            assert(0);
      }
   }
}

/*--------------------------------------------------------------------*/

/* A "number" consists of decimal digit characters, and a "word"
   consists of alphabetic characters.  Read a line from stdin.  Write
   the line to stdout. If the line contains a non-number or a non-word,
   then write an error message to stderr and reject the line. 
   Otherwise write to stdout each number that the line contains
   followed by each word that the line contains.  Repeat until EOF.
   Return 0 iff successful. As always, argc is the command-line
   argument count and argv is an array of command-line arguments. */

int main(int argc, char *argv[])
{
   char *pcLine;
   DynArray_T oTokens;
   int iRet;

   pcPgmName = argv[0];

   printf("------------------------------------\n");

   while ((pcLine = readLine(stdin)) != NULL)
   {
      printf("Line: %s\n", pcLine);
      iRet = fflush(stdout);
      if (iRet == EOF)
         {perror(pcPgmName); exit(EXIT_FAILURE);}
      oTokens = lexLine(pcLine);
      if (oTokens != NULL)
      {
         writeTokens(oTokens);
         freeTokens(oTokens);
         DynArray_free(oTokens);
      }

      printf("------------------------------------\n");
      free(pcLine);
   }

   return 0;
}
