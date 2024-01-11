
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

	csrr a2, mstatus	# read machine-mode status register
	ori a2, a2, 0x8		# add MACHINE_INTERRUPT_ENABLE bit to mask to
				# enable machine-mode interrupts
	csrw mstatus, a2	# write back changed register value

	csrr a2, mie		# read machine-mode interrupt enable mask
	ori a2, a2, 0x80	# add MACHINE_TIMER_INTERRUPTS_ENABLE bit to
				# mask to allow machine-mode timer interrupts
	csrw mie, a2		# write back changed interrupt mask

loop:
	j loop			# wait for interrupt

.align 4			# interrupt handler must be aligned on 4 bytes
timervec:
	li a1, 0x10000000	# UART address

	li a0, 'i'		# 'i'
	sb a0, (a1)		# write 'i' to UART when interrupt came

	li a0, '\n'		# '\n'
	sb a0, (a1)		# write '\n' to UART

	li a1, 0x2004000	# CLINT mtimecmp register address
	li a0, 0xffffffffffff	# write big number to mtimecmp register to
				# prevent repeated interrupts
	sw a0, (a1)		# store value to mtimercmp

	mret			# return from interrupt handler back to loop

