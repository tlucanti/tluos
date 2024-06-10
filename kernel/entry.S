
.global _start
.section .text

_start:
	la sp, _kernel_stack # _kernel_stack has address of end of kernel stack
	li a0, 4096 # start of stack is upper by stack size
	add sp, sp, a0
	call start_kernel

loop:	j loop

