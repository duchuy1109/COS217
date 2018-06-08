### --------------------------------------------------------------------
### powerstack.s
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

### --------------------------------------------------------------------

        .section ".bss"

### --------------------------------------------------------------------

        .section ".text"

        ## -------------------------------------------------------------
        ## Read a non-negative base and exponent from stdin.  Write
        ## base raised to the exponent power to stdout.  Return 0.
        ## int main(void)
        ## -------------------------------------------------------------

        ##  Local variables:
        .equ    LINDEX, 0
        .equ    LPOWER, 8
        .equ    LEXP,  16
        .equ    LBASE, 24

        .equ    STACK_BYTECOUNT, 32
        
        .globl  main
        .type   main,@function

main:

        ## long lBase
        subq    $8, %rsp

        ## long lExp
        subq    $8, %rsp

        ## long lPower = 1
        pushq   $1

        ## long lIndex
        subq    $8, %rsp

        ## printf("Enter the base:  ")
        movq    $cPrompt1, %rdi
        movl    $0, %eax
        call    printf

        ## scanf("%ld", &lBase)
        leaq    LBASE(%rsp), %rsi
           ## Alternative to leaq:
           ##    movq %rsp, %rsi
           ##    addq $LBASE, %rsi
        movq    $cScanfFormat, %rdi
        movl    $0, %eax
        call    scanf

        ## printf("Enter the exponent:  ")
        movq    $cPrompt2, %rdi
        movl    $0, %eax
        call    printf

        ## scanf("%ld", &lExp)
        leaq    LEXP(%rsp), %rsi
           ## Alternative to leaq:
           ##    movq %rsp, %rsi
           ##    addq $LEXP, %rsi
        movq    $cScanfFormat, %rdi
        movl    $0, %eax
        call    scanf

        ## lIndex = 1
        movq    $1, LINDEX(%rsp)

loop1:

        ## if (lIndex > lExp) goto loopend1
        movq    LINDEX(%rsp), %rax
        cmpq    LEXP(%rsp), %rax
        jg      loopend1

        ## lPower *= lBase
        movq    LPOWER(%rsp), %rax
        imulq   LBASE(%rsp)
        movq    %rax, LPOWER(%rsp)

        ## iIndex++
        incq    LINDEX(%rsp)

        ## goto loop1
        jmp     loop1

loopend1:

        ## printf("%ld to the %ld power is %ld.\n", lBase, lExp, lPower)
        movq    $cResult, %rdi
        movq    LBASE(%rsp), %rsi
        movq    LEXP(%rsp), %rdx
        movq    LPOWER(%rsp), %rcx
        movl    $0, %eax
        call    printf

        ## return 0
        movl    $0, %eax
        addq    $STACK_BYTECOUNT, %rsp
        ret
