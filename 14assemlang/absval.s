### --------------------------------------------------------------------
### absval.s
### Author: Bob Dondero
### --------------------------------------------------------------------

        .section ".rodata"

cPrompt:
        .string "Enter an integer:  "

cScanfFormat:
        .string "%d"

cResult:
        .string "The integer's absolute value is %d.\n"

### --------------------------------------------------------------------

        .section ".data"

### --------------------------------------------------------------------

        .section ".bss"

iInput:
        .skip   4

iAbsVal:
        .skip   4

### --------------------------------------------------------------------

        .section ".text"

        ## -------------------------------------------------------------
        ## Read an integer from stdin, and write its absolute value
        ## to stdout.  Return 0.
        ## int main(void)
        ## -------------------------------------------------------------

        .globl  main
        .type   main,@function

main:
        
        ## printf("Enter an integer:  ")
        movq    $cPrompt, %rdi
        movl    $0, %eax
        call    printf

        ## scanf("%d", &iInput)
        movq    $cScanfFormat, %rdi
        movq    $iInput, %rsi
        movl    $0, %eax
        call    scanf

        ## iAbsVal = abs(iInput)
        movl    iInput, %edi
        call    abs
        movl    %eax, iAbsVal

        ## printf("The integer's absolute value is %d.\n", iAbsVal)
        movq    $cResult, %rdi
        movl    iAbsVal, %esi
        movl    $0, %eax
        call    printf

        ## return 0
        movl    $0, %eax
        ret
