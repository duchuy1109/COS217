### --------------------------------------------------------------------
### powerunsigned.s
### Author: Bob Dondero
### --------------------------------------------------------------------

        .section ".rodata"

cPrompt1:
        .string "Enter the base:  "

cPrompt2:
        .string "Enter the exponent:  "

cScanfFormat:
        .string "%lu"

cResult:
        .string "%lu to the %lu power is %lu.\n"

### --------------------------------------------------------------------

        .section ".data"

ulPower:
        .quad   1

### --------------------------------------------------------------------

        .section ".bss"

ulBase:
        .skip   8

ulExp:
        .skip   8

ulIndex:
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

        ## scanf("%d", &ulBase)
        movq    $cScanfFormat, %rdi        
        movq    $ulBase, %rsi
        movl    $0, %eax
        call    scanf

        ## printf("Enter the exponent:  ")
        movq    $cPrompt2, %rdi
        movl    $0, %eax
        call    printf

        ## scanf("%d", &ulExp)
        movq    $cScanfFormat, %rdi
        movq    $ulExp, %rsi        
        movl    $0, %eax
        call    scanf

        ## ulIndex = 1
        movq    $1, ulIndex

loop1:

        ## if (ulIndex > ulExp) goto loopend1
        movq    ulIndex, %rax
        cmpq    ulExp, %rax
        ja      loopend1

        ## ulPower *= ulBase
        movq    ulPower, %rax
        mulq    ulBase
        movq    %rax, ulPower

        ## ulIndex++
        incq    ulIndex

        ## goto loop1
        jmp     loop1

loopend1:

        ## printf("%lu to the %lu power is %lu.\n", 
        ##    ulBase, ulExp, ulPower)
        movq    $cResult, %rdi
        movq    ulBase, %rsi
        movq    ulExp, %rdx                       
        movq    ulPower, %rcx
        movl    $0, %eax
        call    printf

        ## return 0
        movl    $0, %eax       
        ret
