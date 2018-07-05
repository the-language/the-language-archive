	.file	"memory.c"
	.text
	.p2align 4,,15
	.globl	memory_maybeAlloc
	.type	memory_maybeAlloc, @function
memory_maybeAlloc:
.LFB18:
	.cfi_startproc
	jmp	malloc@PLT
	.cfi_endproc
.LFE18:
	.size	memory_maybeAlloc, .-memory_maybeAlloc
	.p2align 4,,15
	.globl	memory_alloc
	.type	memory_alloc, @function
memory_alloc:
.LFB19:
	.cfi_startproc
	pushq	%rbx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	movq	%rdi, %rbx
	.p2align 4,,10
	.p2align 3
.L4:
	movq	%rbx, %rdi
	call	malloc@PLT
	testq	%rax, %rax
	je	.L4
	popq	%rbx
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE19:
	.size	memory_alloc, .-memory_alloc
	.p2align 4,,15
	.globl	memory_free
	.type	memory_free, @function
memory_free:
.LFB20:
	.cfi_startproc
	jmp	free@PLT
	.cfi_endproc
.LFE20:
	.size	memory_free, .-memory_free
	.ident	"GCC: (Ubuntu 7.3.0-16ubuntu3) 7.3.0"
	.section	.note.GNU-stack,"",@progbits
