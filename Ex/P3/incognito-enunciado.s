	.file	"incognito.c"
	.option nopic
	.attribute arch, "rv32i2p0_m2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 16
	.text
	.align	2
	.globl	inc
	.type	inc, @function
inc:
	mv	a5,a0
	mv	a0,a1
	sw	a2,0(a5)
	slli	a4,a1,2
	add	a5,a5,a4
.L2:
	addi	a0,a0,-1
	addi	a5,a5,-4
	lw	a4,0(a5)
	bne	a4,a2,.L2
	ret
	.size	inc, .-inc
	.ident	"GCC: (GNU) 11.1.0"
