/*--------------------------------------------------------------------*/
/* stack.c (Version 6)                                                */
/* Author: Bob Dondero                                                */
/*--------------------------------------------------------------------*/

#include <assert.h>
#include <stdlib.h>
#include "stack.h"

/*--------------------------------------------------------------------*/

/* Each item is stored in a StackNode.  StackNodes are linked to
   form a list.  */

struct StackNode
{
   /* The item. */
   const void *pvItem;

   /* The address of the next StackNode. */
   struct StackNode *psNextNode;
};

/*--------------------------------------------------------------------*/

/* A Stack is a "dummy" node that points to the first StackNode. */

struct Stack
{
   /* The address of the first StackNode. */
   struct StackNode *psFirstNode;
};

/*--------------------------------------------------------------------*/

Stack_T Stack_new(void)
{
   Stack_T oStack;

   oStack = (Stack_T)malloc(sizeof(struct Stack));
   if (oStack == NULL)
      return NULL;

   oStack->psFirstNode = NULL;
   return oStack;
}

/*--------------------------------------------------------------------*/

void Stack_free(Stack_T oStack)
{
   struct StackNode *psCurrentNode;
   struct StackNode *psNextNode;

   assert(oStack != NULL);

   for (psCurrentNode = oStack->psFirstNode;
        psCurrentNode != NULL;
        psCurrentNode = psNextNode)
   {
      psNextNode = psCurrentNode->psNextNode;
      free(psCurrentNode);
   }

   free(oStack);
}

/*--------------------------------------------------------------------*/

int Stack_push(Stack_T oStack, const void *pvItem)
{
   struct StackNode *psNewNode;

   assert(oStack != NULL);

   psNewNode = (struct StackNode*)malloc(sizeof(struct StackNode));
   if (psNewNode == NULL)
      return 0;

   psNewNode->pvItem = pvItem;
   psNewNode->psNextNode = oStack->psFirstNode;
   oStack->psFirstNode = psNewNode;
   return 1;
}

/*--------------------------------------------------------------------*/

void *Stack_pop(Stack_T oStack)
{
   const void *pvItem;
   struct StackNode *psNextNode;

   assert(oStack != NULL);
   assert(oStack->psFirstNode != NULL);

   pvItem = oStack->psFirstNode->pvItem;
   psNextNode = oStack->psFirstNode->psNextNode;
   free(oStack->psFirstNode);
   oStack->psFirstNode = psNextNode;
   return (void*)pvItem;
}

/*--------------------------------------------------------------------*/

int Stack_isEmpty(Stack_T oStack)
{
   assert(oStack != NULL);

   return oStack->psFirstNode == NULL;
}

/*--------------------------------------------------------------------*/

void Stack_map(Stack_T oStack,
               void (*pfApply)(void *pvItem, void *pvExtra),
               const void *pvExtra)
{
   struct StackNode *psCurrentNode;

   assert(oStack != NULL);
   assert(pfApply != NULL);

   for (psCurrentNode = oStack->psFirstNode;
        psCurrentNode != NULL;
        psCurrentNode = psCurrentNode->psNextNode)
      (*pfApply)((void*)psCurrentNode->pvItem, (void*)pvExtra);
}
