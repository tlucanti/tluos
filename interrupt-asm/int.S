
.global _start
.section .text

_start:
	li a1, 0x200bff8	# CLINT mtime register address
	ld a2, (a1)		# load current machine time
				# from CLINT mtime register

	li a3, 10000000		# 1e7 ticks
	add a2, a2, a3		# add 1e6 ticks to current time

	li a1, 0x2004000	# CLINT mtimecmp register address
	sd a2, (a1)		# set alarm in 1e6 ticks from current time
				# by writing to CLINT mtimecmp register

	la a1, timervec		# load interrupt handler address to register
	csrw mtvec, a1		# set interrupt handler

	csrr a2, mstatus
	ori a2, a2, 0x8
	csrw mstatus, a2

	csrr a2, mie		# read machine interrupt enable mask
	ori a2, a2, 0x80	# add MTIE bit to mask to enable
				# MACHINE_TIMER_INTERRUPTS

	csrw mie, a2		# write back changed interrupt mask

	j loop

.align 4			# interrupt handler must be aligned on 4 bytes
timervec:
	li a1, 0x10000000	# UART address

	li a0, 'i'		# 'i'
	sb a0, (a1)		# write 'i' to UART when interrupt came

	j _start		# start over

loop:				# wait for interrupt
	j loop
