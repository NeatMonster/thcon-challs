.section .text

.globl _start
_start:
    popq %rdi
    movq %rsp, %rsi
    pushq %rdi
    call main
    movl %eax, %edi
    call exit
.size _start, . - _start
