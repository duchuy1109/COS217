### --------------------------------------------------------------------
### rect.s
### Author: Bob Dondero
### --------------------------------------------------------------------

        .section ".rodata"

cLengthPrompt:
        .string "Rectangle length:  "

cWidthPrompt:
        .string "Rectangle width:  "

cScanfFormat:
        .string "%d"

cResult:
        .string "The rectangle's perimeter is %d.\n"

### --------------------------------------------------------------------

        .section ".data"

### --------------------------------------------------------------------

        .section ".bss"

iLength:
        .skip   4

iWidth:
        .skip   4

iPerim:
        .skip   4

### --------------------------------------------------------------------

        .section ".text"

        ## -------------------------------------------------------------
        ## Read a rectangles length and width from stdin, and write
        ## its perimeter to stdout.  Return 0.
        ## int main(void)
        ## -------------------------------------------------------------

        .globl  main
        .type   main,@function

main:
        
        ## printf("Rectangle length:  ")
        movq    $cLengthPrompt, %rdi
        movl    $0, %eax
        call    printf

        ## scanf("%d", &iLength)
        movq    $cScanfFormat, %rdi
        movq    $iLength, %rsi
        movl    $0, %eax
        call    scanf

        ## printf("Rectangle width:  ")
        movq    $cWidthPrompt, %rdi
        movl    $0, %eax
        call    printf

        ## scanf("%d", &iWidth)
        movq    $cScanfFormat, %rdi
        movq    $iWidth, %rsi
        movl    $0, %eax
        call    scanf

        ## iPerimeter = 2 * (iLength + iWidth)
        movl    iLength, %eax
        addl    iWidth, %eax
        sall    $1, %eax
           ## Alternatives to sall (any one of these three):
           ##    addl %eax, %eax
           ##    imull $2, %eax
           ##    movl $2, %ecx; imull %ecx
        movl    %eax, iPerim

        ## printf("The rectangle's perimeter is %d.\n", iPerim)
        movq    $cResult, %rdi
        movl    iPerim, %esi
        movl    $0, %eax
        call    printf

        ## return 0
        movl    $0, %eax        
        ret
