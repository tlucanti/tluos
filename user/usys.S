
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

.global spawn
spawn:
	li a7, 3
	ecall
	ret

.global sched
sched:
	li a7, 4
	ecall
	ret

