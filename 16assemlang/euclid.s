### --------------------------------------------------------------------
### euclid.s
### Author: Bob Dondero
### --------------------------------------------------------------------

        .section ".rodata"

cPrompt:
        .string "Enter an integer: "
        
cScanfFormat:
        .string "%ld"
        
cPrintfFormat:
        .string "The gcd is %ld\n"

### --------------------------------------------------------------------

        .section ".data"

### --------------------------------------------------------------------

        .section ".bss"

### --------------------------------------------------------------------

        .section ".text"

        ## -------------------------------------------------------------
        ## Return the greatest common divisor of lFirst and lSecond.
        ## long gcd(long lFirst, long lSecond)
        ## -------------------------------------------------------------
        
        ## Local variables:
        .equ    LABSSECOND, 0
        .equ    LABSFIRST,  8
        .equ    LTEMP,     16
 
        ## Parameters:
        .equ    LSECOND,   24
        .equ    LFIRST,    32
        
        .equ    STACK_BYTECOUNT, 40

        .type   gcd,@function

gcd:

        ## Save lFirst to the stack.
        pushq   %rdi
        
        ## Save lSecond to the stack.
        pushq   %rsi
        
        ## long lTemp
        subq    $8, %rsp
        
        ## long lAbsFirst
        subq    $8, %rsp
        
        ## long lAbsSecond
        subq    $8, %rsp
        
        ## lAbsFirst = labs(lFirst)
        movq    LFIRST(%rsp), %rdi
        call    labs
        movq    %rax, LABSFIRST(%rsp)
        
        ## lAbsSecond = labs(lSecond)
        movq    LSECOND(%rsp), %rdi
        call    labs
        movq    %rax, LABSSECOND(%rsp)        
   
loop1:
   
        ## if (lAbsSecond == 0) goto loopend1
        cmpq    $0, LABSSECOND(%rsp)
        je      loopend1
        
        ## lTemp = lAbsFirst % lAbsSecond
        movq    LABSFIRST(%rsp), %rax  # Copy lAbsFirst to RDX:RAX
        cqto                           # Copy lAbsFirst to RDX:RAX
        idivq   LABSSECOND(%rsp)       # Divide by lAbsSecond
        movq    %rdx, LTEMP(%rsp)      # Copy remainder to lTemp
        
        ## lAbsFirst = lAbsSecond
        movq    LABSSECOND(%rsp), %rax
        movq    %rax, LABSFIRST(%rsp)
        
        ## lAbsSecond = lTemp
        movq    LTEMP(%rsp), %rax
        movq    %rax, LABSSECOND(%rsp)
        
        ## goto loop1
        jmp     loop1
        
loopend1:

        ## return lAbsFirst
        movq    LABSFIRST(%rsp), %rax
        addq    $STACK_BYTECOUNT, %rsp
        ret        

        ## -------------------------------------------------------------
        ## Read two integers from stdin. Compute their greatest common
        ## divisor, and write it to stdout. Return 0.
        ## int main(void)
        ## -------------------------------------------------------------
        
        ## Local variables:
        .equ    LGCD, 0
        .equ    L2,   8
        .equ    L1,  16

        .equ    STACK_BYTECOUNT, 24
                
        .globl  main
        .type   main,@function

main:

        ## long l1
        subq    $8, %rsp
        
        ## long l2
        subq    $8, %rsp

        ## long lGcd
        subq    $8, %rsp

        ## printf("Enter an integer: ")
        movq    $cPrompt, %rdi
        movl    $0, %eax
        call    printf
        
        ## scanf("%ld", &l1)
        movq    $cScanfFormat, %rdi
        leaq    L1(%rsp), %rsi
        movl    $0, %eax
        call    scanf
        
        ## printf("Enter an integer: ")
        movq    $cPrompt, %rdi
        movl    $0, %eax
        call    printf
        
        ## scanf("%ld", &l2)
        movq    $cScanfFormat, %rdi
        leaq    L2(%rsp), %rsi
        movl    $0, %eax
        call    scanf
       
        ## lGcd = gcd(l1, l2)
        movq    L1(%rsp), %rdi
        movq    L2(%rsp), %rsi
        call    gcd
        movq    %rax, LGCD(%rsp)
        
        ## printf("The gcd is %ld\n", lGcd)
        movq    $cPrintfFormat, %rdi
        movq    LGCD(%rsp), %rsi
        movl    $0, %eax
        call    printf

        ## return 0
        movl    $0, %eax
        addq    $STACK_BYTECOUNT, %rsp
        ret

