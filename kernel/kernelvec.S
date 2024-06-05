
.global kernelvec
.section .text

.align 4
kernelvec:
	csrw mscratch, a0 # save value of a0 to mscratch

	la a0, trapframe # load value of trapframe variable

        # save the registers.
	sd ra,	  0(a0)
	sd sp,	  8(a0)
	sd gp,	 16(a0)
	sd tp,	 24(a0)
	sd t0,	 32(a0)
	sd t1,	 40(a0)
	sd t2,	 48(a0)
	sd s0,	 56(a0)
	sd s1,	 64(a0)
	# store a0 later
	sd a1,	 80(a0)
	sd a2,	 88(a0)
	sd a3,	 96(a0)
	sd a4,	104(a0)
	sd a5,	112(a0)
	sd a6,	120(a0)
	sd a7,	128(a0)
	sd s2,	136(a0)
	sd s3,	144(a0)
	sd s4,	152(a0)
	sd s5,	160(a0)
	sd s6,	168(a0)
	sd s7,	176(a0)
	sd s8,	184(a0)
	sd s9,	192(a0)
	sd s10,	200(a0)
	sd s11,	208(a0)
	sd t3,	216(a0)
	sd t4,	224(a0)
	sd t5,	232(a0)
	sd t6,	240(a0)

	# load back initial value of a0 from mscratch
	csrr t0, mscratch
	# save a0 value to trapframe
	sd t0, 72(a0)

	# call trap handler c function
	la sp, _kernel_stack # load address of _kernel_stack
	li t0, 4096
	add sp, sp, t0 # set stack for kernel
	call trap_handler

	la a0, trapframe # load address of trapframe to a0

	ld t0, 72(a0) # load value of a0 from trapframe to t0
	csrw mscratch, t0 # save value of a0 to mscratch

	ld ra,	  0(a0)
	ld sp,	  8(a0)
	ld gp,	 16(a0)
	ld tp,	 24(a0)
	ld t0,	 32(a0)
	ld t1,	 40(a0)
	ld t2,	 48(a0)
	ld s0,	 56(a0)
	ld s1,	 64(a0)
	# load a0 later
	ld a1,	 80(a0)
	ld a2,	 88(a0)
	ld a3,	 96(a0)
	ld a4,	104(a0)
	ld a5,	112(a0)
	ld a6,	120(a0)
	ld a7,	128(a0)
	ld s2,	136(a0)
	ld s3,	144(a0)
	ld s4,	152(a0)
	ld s5,	160(a0)
	ld s6,	168(a0)
	ld s7,	176(a0)
	ld s8,	184(a0)
	ld s9,	192(a0)
	ld s10,	200(a0)
	ld s11,	208(a0)
	ld t3,	216(a0)
	ld t4,	224(a0)
	ld t5,	232(a0)
	ld t6,	240(a0)

	csrr a0, mscratch # load initial value of a0 from mscratch

	mret

