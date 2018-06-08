### --------------------------------------------------------------------
### power.s
### Author: Bob Dondero
### --------------------------------------------------------------------

        .section ".rodata"

cPrompt1:
        .string "Enter the base:  "

cPrompt2:
        .string "Enter the exponent:  "

cScanfFormat:
        .string "%ld"

cResult:
        .string "%ld to the %ld power is %ld.\n"

### --------------------------------------------------------------------

        .section ".data"

lPower:
        .quad   1

### --------------------------------------------------------------------

        .section ".bss"

lBase:
        .skip   8

lExp:
        .skip   8

lIndex:
        .skip   8

### --------------------------------------------------------------------

        .section ".text"

        ## -------------------------------------------------------------
        ## Read a non-negative base and exponent from stdin.  Write
        ## base raised to the exponent power to stdout.  Return 0.
        ## int main(void)
        ## -------------------------------------------------------------

        .globl  main
        .type   main,@function

main:
        
        ## printf("Enter the base:  ")
        movq    $cPrompt1, %rdi
        movl    $0, %eax
        call    printf

        ## scanf("%d", &lBase)
        movq    $cScanfFormat, %rdi
        movq    $lBase, %rsi
        movl    $0, %eax
        call    scanf

        ## printf("Enter the exponent:  ")
        movq    $cPrompt2, %rdi
        movl    $0, %eax
        call    printf

        ## scanf("%d", &lExp)
        movq    $cScanfFormat, %rdi        
        movq    $lExp, %rsi
        movl    $0, %eax
        call    scanf

        ## lIndex = 1
        movq    $1, lIndex

loop1:

        ## if (lIndex > lExp) goto loopend1
        movq    lIndex, %rax
        cmpq    lExp, %rax
        jg      loopend1

        ## lPower *= lBase
        movq    lPower, %rax
        imulq   lBase
        movq    %rax, lPower

        ## lIndex++
        incq    lIndex

        ## goto loop1
        jmp     loop1

loopend1:

        ## printf("%ld to the %ld power is %ld.\n", lBase, lExp, lPower)
        movq    $cResult, %rdi
        movq    lBase, %rsi        
        movq    lExp, %rdx
        movq    lPower, %rcx
        movl    $0, %eax
        call    printf

        ## return 0
        movl    $0, %eax       
        ret
