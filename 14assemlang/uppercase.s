### --------------------------------------------------------------------
### uppercase.s
### Author: Bob Dondero
### --------------------------------------------------------------------

        .equ    LOWER_TO_UPPER, -32

### --------------------------------------------------------------------

        .section ".rodata"

### --------------------------------------------------------------------

        .section ".data"

### --------------------------------------------------------------------

        .section ".bss"

cChar:
        .skip   1

### --------------------------------------------------------------------

        .section ".text"

        ## -------------------------------------------------------------
        ## Read a letter from stdin, and write its uppercase
        ## equivalent to stdout.  Return 0.
        ## int main(void)
        ## -------------------------------------------------------------

        .globl  main
        .type   main,@function

main:
        
        ## cChar = (char)getchar()
        call    getchar
        movb    %al, cChar

        ## cChar += LOWER_TO_UPPER
        addb    $LOWER_TO_UPPER, cChar

        ## putchar((int)cChar)
        movsbl  cChar, %edi
        call    putchar

        ## putchar('\n')
        movl    $'\n', %edi
        call    putchar

        ## return 0
        movl    $0, %eax
        ret
