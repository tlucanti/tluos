
.global _start
.section .text

_start:
	la sp, _kernel_stack
	call start_kernel

loop:	j loop

