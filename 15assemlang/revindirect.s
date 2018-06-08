### --------------------------------------------------------------------
### revindirect.s
### Author: Bob Dondero
### --------------------------------------------------------------------

        .equ    ARRAY_LENGTH, 5

### --------------------------------------------------------------------

        .section ".rodata"

cPrompt:
        .string "Enter %d integers:\n"
cScanfFormat:
        .string "%ld"
cNewLine:
        .string "\n"
cMessage:
        .string "The integers in reverse order are:\n"
cPrintfFormat:
        .string "%ld\n"

### --------------------------------------------------------------------

        .section ".data"

### --------------------------------------------------------------------

        .section ".bss"

lNums:
        .skip   8 * ARRAY_LENGTH
lIndex:
        .skip   8

### --------------------------------------------------------------------

        .section ".text"

        ## -------------------------------------------------------------
        ## Read ARRAY_LENGTH integers from stdin, and write them in
        ## reverse order to stdout. Return 0.
        ## -------------------------------------------------------------

        .globl  main
        .type   main,@function

main:

        ## printf("Enter %d integers:\n", ARRAY_LENGTH)
        movq    $cPrompt, %rdi
        movl    $ARRAY_LENGTH, %esi
        movl    $0, %eax
        call    printf

        ## lIndex = 0
        movq    $0, lIndex

loop1:

        ## if (lIndex >= ARRAY_LENGTH) goto loopend1
        cmpq    $ARRAY_LENGTH, lIndex
        jge     loopend1

        ## scanf("%ld", &alNums[lIndex])
        movq    $cScanfFormat, %rdi
        movq    lIndex, %rsi
        salq    $3, %rsi
        addq    $lNums, %rsi
        movl    $0, %eax
        call    scanf

        ## lIndex++
        incq    lIndex

        ## goto loop1
        jmp     loop1

loopend1:

        ## printf("\n")
        movq    $cNewLine, %rdi
        movl    $0, %eax
        call    printf

        ## printf("The integers in reverse order are:\n")
        movq    $cMessage, %rdi
        movl    $0, %eax
        call    printf

        ## lIndex = ARRAY_LENGTH-1
        movq    $ARRAY_LENGTH-1, lIndex

loop2:

        ## if (lIndex < 0) goto loopend2
        cmpq    $0, lIndex
        jl      loopend2

        ## printf("%ld\n", alNums[lIndex])
        movq    $cPrintfFormat, %rdi
        movq    lIndex, %rsi
        salq    $3, %rsi
        addq    $lNums, %rsi
        movq    (%rsi), %rsi     # Indirect addressing
        movl    $0, %eax
        call    printf

        ## lIndex--
        decq    lIndex

        ## goto loop2
        jmp     loop2

loopend2:

        ## return 0
        movl    $0, %eax
        ret
