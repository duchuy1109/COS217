### --------------------------------------------------------------------
### euclidopt.s
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
        .equ    LABSSECOND, %r13  # Callee-saved
        .equ    LABSFIRST,  %r14  # Callee-saved
        .equ    LTEMP,      %r15  # Callee-saved
 
        ## Parameters:
        .equ    LSECOND,    %rsi  # Caller-saved
        .equ    LFIRST,     %rdi  # Caller-saved

        .type   gcd,@function

gcd:

        pushq   %r13  # Save callee-saved register
        pushq   %r14  # Save callee-saved register
        pushq   %r15  # Save callee-saved register
        
        ## long lTemp
        ## long lAbsFirst
        ## long lAbsSecond
        
        ## lAbsFirst = labs(lFirst)
        pushq   %rdi  # Save caller-saved register (unnecessary)
        pushq   %rsi  # Save caller-saved register
        movq    LFIRST, %rdi  # (unnecessary)
        call    labs
        movq    %rax, LABSFIRST
        popq    %rsi  # Restore caller-saved register
        popq    %rdi  # Restore caller-saved register (unnecessary)
        
        ## lAbsSecond = labs(lSecond)
        pushq   %rdi  # Save caller-saved register (unnecessary)
        pushq   %rsi  # Save caller-saved register (unnecessary)
        movq    LSECOND, %rdi
        call    labs
        movq    %rax, LABSSECOND      
        popq    %rsi  # Restore caller-saved register (unnecessary)
        popq    %rdi  # Restore caller-saved register (unnecessary)
        
loop1:
   
        ## if (lAbsSecond == 0) goto loopend1
        cmpq    $0, LABSSECOND
        je      loopend1
        
        ## lTemp = lAbsFirst % lAbsSecond
        movq    LABSFIRST, %rax  # Copy lAbsFirst to RDX:RAX
        cqto                     # Copy lAbsFirst to RDX:RAX
        idivq   LABSSECOND       # Divide by lAbsSecond
        movq    %rdx, LTEMP      # Copy remainder to lTemp
        
        ## lAbsFirst = lAbsSecond
        movq    LABSSECOND, LABSFIRST

        ## lAbsSecond = lTemp
        movq    LTEMP, LABSSECOND
        
        ## goto loop1
        jmp     loop1
        
loopend1:

        ## return lAbsFirst
        movq    LABSFIRST, %rax
        popq    %r15  # Restore callee-saved register
        popq    %r14  # Restore callee-saved register
        popq    %r13  # Restore callee-saved register
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
