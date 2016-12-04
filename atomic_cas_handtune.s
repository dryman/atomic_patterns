	.file	"atomic_wait_free_cas.c"
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"atomic counter val: %lu\n"
	.section	.text.unlikely,"ax",@progbits
.LCOLDB1:
	.text
.LHOTB1:
	.p2align 4,,15
	.globl	test
	.type	test, @function
test:
.LFB38:
	.cfi_startproc
	subq	$24, %rsp
	.cfi_def_cfa_offset 32
	movl	(%rdi), %ecx
	movl	$1, %eax
	salq	%cl, %rax
	testq	%rax, %rax
	je	.L6
	movq	%rax, %rcx
	xorl	%esi, %esi
.L8:
	movq	atomic_counter(%rip), %rax
	.p2align 4,,10
	.p2align 3
.L12:
# cmpxchgq
# Compare RAX with r/m64. If equal, ZF is set and r64 is loaded into r/m64.
# Else, clear ZF and load r/m64 into RAX
#  Original compiled program:
#	movq	%rax, 8(%rsp)
#	leaq	1(%rax), %rdx
#	movq	8(%rsp), %rax
#	lock cmpxchgq	%rdx, atomic_counter(%rip)
#	jne	.L12
	leaq	1(%rax), %rdx
	lock cmpxchgq	%rdx, atomic_counter(%rip)
	jne	.L12
	addq	$1, %rsi
	cmpq	%rsi, %rcx
	jne	.L8
.L6:
	movq	atomic_counter(%rip), %rsi
	movl	$.LC0, %edi
	xorl	%eax, %eax
	call	printf
	xorl	%eax, %eax
	addq	$24, %rsp
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE38:
	.size	test, .-test
	.section	.text.unlikely
.LCOLDE1:
	.text
.LHOTE1:
	.local	atomic_counter
	.comm	atomic_counter,8,8
	.ident	"GCC: (GNU) 5.2.1 20150902 (Red Hat 5.2.1-2)"
	.section	.note.GNU-stack,"",@progbits
