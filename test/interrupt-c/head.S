
.global _start
.section .text

_start:
	la sp, _kernel_stack
	call start_kernel

loop:	j loop

.global timervec
.align 4
timervec:
	li a1, 0x200bff8	# CLINT mtime register address
	ld a2, (a1)		# load current machine time
				# from CLINT mtime register

	li a3, 10000000		# 1e7 ticks
	add a2, a2, a3		# add 1e6 ticks to current time

	li a1, 0x2004000	# CLINT mtimecmp register address
	sd a2, (a1)		# set alarm in 1e6 ticks from current time
				# by writing to CLINT mtimecmp register

	li s1, 0x10000000	# UART address

	li s0, 'i'		# 'i'
	sb s0, (s1)		# write 'i' to UART when interrupt came

	li s0, '\n'		# '\n'
	sb s0, (s1)		# write 'i' to UART

	mret

