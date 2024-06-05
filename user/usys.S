
.global getcpu
getcpu:
	li a7, 1
	ecall
	ret

.global print
print:
	li a7, 2
	ecall
	ret

