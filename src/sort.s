	.text
	.p2align 4
	.globl _sort_array
_sort_array:
LFB0:
	leal	-1(%rsi), %edx
	movq	%rdi, %r8
	testl	%edx, %edx
	jle	L1
	leaq	4(%rdi), %r9
	.p2align 4,,10
	.p2align 3
L3:
	subl	$1, %edx
	movq	%r8, %rax
	leaq	(%r9,%rdx,4), %rsi
	movq	%rdx, %rdi
	.p2align 4,,10
	.p2align 3
L5:
	movl	(%rax), %edx
	movl	4(%rax), %ecx
	cmpl	%ecx, %edx
	jle	L4
	movl	%ecx, (%rax)
	movl	%edx, 4(%rax)
L4:
	addq	$4, %rax
	cmpq	%rax, %rsi
	jne	L5
	testl	%edi, %edi
	movl	%edi, %edx
	jne	L3
L1:
	ret
LSCIE1:
	.long	0
	.byte	0x1
	.ascii "zR\0"
	.byte	0x1
	.byte	0x78
	.byte	0x10
	.byte	0x1
	.byte	0x10
	.byte	0xc
	.byte	0x7
	.byte	0x8
	.byte	0x90
	.byte	0x1
