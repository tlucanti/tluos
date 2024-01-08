
.global _start
.section .text

_start:
	li a1, 0x10000000	# UART address to a1

	li a0, 'h'		# 'h' to a0
	sb a0, (a1)		# write 'h' to UART

	li a0, 'e'		# 'e' to a0
	sb a0, (a1)		# write 'e' to UART

	li a0, 'l'		# 'l' to a0
	sb a0, (a1)		# write 'l' to UART

	li a0, 'l'		# 'l' to a0
	sb a0, (a1)		# write 'l' to UART

	li a0, 'o'		# 'o' to a0
	sb a0, (a1)		# write 'o' to UART

	li a0, '\n'		# '\n' to a0
	sb a0, (a1)		# write '\n' to UART

loop:	j loop

