	.file	"greedy.c"
	.intel_syntax noprefix
	.text
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"Thread %d: i = %d\n"
	.text
	.p2align 4
	.type	greedy._omp_fn.0, @function
greedy._omp_fn.0:
	endbr64
	push	r15
	push	r14
	mov	r14, rdi
	push	r13
	push	r12
	push	rbp
	push	rbx
	sub	rsp, 24
	mov	r13, QWORD PTR [rdi]
	movsx	r12, DWORD PTR 28[rdi]
	call	omp_get_num_threads@PLT
	mov	ebx, eax
	call	omp_get_thread_num@PLT
	mov	ebp, eax
	mov	rax, QWORD PTR 16[r13]
	mov	eax, DWORD PTR [rax+r12*4]
	cdq
	idiv	ebx
	cmp	ebp, edx
	jl	.L2
.L5:
	mov	ecx, eax
	imul	ecx, ebp
	add	edx, ecx
	lea	ecx, [rax+rdx]
	cmp	edx, ecx
	jge	.L7
	movsx	rdx, edx
	mov	r15d, DWORD PTR 24[r14]
	mov	rbx, QWORD PTR 16[r14]
	dec	eax
	mov	r14, QWORD PTR 8[r14]
	lea	rax, 1[rdx+rax]
	lea	rsi, 0[0+r12*8]
	lea	r12, 0[0+rdx*4]
	sal	rax, 2
	mov	QWORD PTR [rsp], rsi
	mov	QWORD PTR 8[rsp], rax
	.p2align 4
	.p2align 3
.L4:
	mov	rax, QWORD PTR 24[r13]
	mov	edi, 1
	mov	rsi, QWORD PTR [rsp]
	mov	rax, QWORD PTR [rax+rsi]
	lea	rsi, .LC0[rip]
	movsx	rax, DWORD PTR [rax+r12]
	mov	eax, DWORD PTR [r14+rax*4]
	test	eax, eax
	lea	edx, 63[rax]
	mov	ecx, eax
	cmovns	edx, eax
	sar	ecx, 31
	add	r12, 4
	shr	ecx, 26
	sar	edx, 6
	add	eax, ecx
	movsx	rdx, edx
	and	eax, 63
	sub	eax, ecx
	mov	ecx, r15d
	shlx	rax, rdi, rax
	or	QWORD PTR [rbx+rdx*8], rax
	mov	edx, ebp
	xor	eax, eax
	call	__printf_chk@PLT
	cmp	QWORD PTR 8[rsp], r12
	jne	.L4
.L7:
	add	rsp, 24
	pop	rbx
	pop	rbp
	pop	r12
	pop	r13
	pop	r14
	pop	r15
	ret
	.p2align 4
	.p2align 3
.L2:
	inc	eax
	xor	edx, edx
	jmp	.L5
	.size	greedy._omp_fn.0, .-greedy._omp_fn.0
	.section	.rodata.str1.1
.LC1:
	.string	"src/graph.algorithms/greedy.c"
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC2:
	.string	"0 <= ORDER[i] && ORDER[i] < g->nvertices"
	.section	.rodata.str1.1
.LC3:
	.string	"nbits > 0"
.LC4:
	.string	"bits"
	.section	.rodata.str1.8
	.align 8
.LC5:
	.string	"1 <= colors[v] && colors[v] <= g->Delta + 1"
	.section	.rodata.str1.1
.LC6:
	.string	"n > 0"
	.text
	.p2align 4
	.globl	greedy
	.type	greedy, @function
greedy:
	endbr64
	push	rbp
	mov	rbp, rsp
	push	r15
	push	r14
	push	r13
	push	r12
	mov	r13, rdi
	push	rbx
	and	rsp, -32
	sub	rsp, 96
	mov	ecx, DWORD PTR [rdi]
	mov	QWORD PTR 32[rsp], rsi
	mov	QWORD PTR 40[rsp], rdx
	mov	rax, QWORD PTR fs:40
	mov	QWORD PTR 88[rsp], rax
	xor	eax, eax
	test	ecx, ecx
	jle	.L11
	lea	edx, -1[rcx]
	mov	rax, rsi
	lea	rsi, 4[rsi+rdx*4]
	.p2align 4
	.p2align 3
.L14:
	mov	edx, DWORD PTR [rax]
	test	edx, edx
	js	.L36
	cmp	edx, ecx
	jge	.L36
	add	rax, 4
	cmp	rax, rsi
	jne	.L14
.L11:
	mov	rdi, QWORD PTR 40[rsp]
	movsx	rdx, ecx
	xor	esi, esi
	sal	rdx, 2
	call	memset@PLT
	mov	eax, DWORD PTR 8[r13]
	cmp	eax, -2
	jl	.L50
	lea	edi, 66[rax]
	sar	edi, 6
	movsx	rdi, edi
	sal	rdi, 3
	call	malloc@PLT
	mov	r14, rax
	mov	eax, DWORD PTR 0[r13]
	test	eax, eax
	jle	.L16
	mov	rax, QWORD PTR 32[rsp]
	movsx	r8, DWORD PTR [rax]
	mov	rax, QWORD PTR 16[r13]
	lea	r12, 0[0+r8*4]
	mov	rbx, r8
	mov	eax, DWORD PTR [rax+r12]
	lea	edx, 3[rax]
	test	r14, r14
	je	.L51
	vmovq	xmm4, r13
	vpinsrq	xmm3, xmm4, QWORD PTR 40[rsp], 1
	xor	r15d, r15d
	vmovaps	XMMWORD PTR 16[rsp], xmm3
	.p2align 4
	.p2align 3
.L17:
	test	edx, edx
	jle	.L52
	lea	edx, 66[rax]
	xor	esi, esi
	mov	rdi, r14
	sar	edx, 6
	movsx	rdx, edx
	sal	rdx, 3
	call	memset@PLT
	vmovaps	xmm2, XMMWORD PTR 16[rsp]
	xor	edx, edx
	lea	rsi, 48[rsp]
	xor	ecx, ecx
	lea	rdi, greedy._omp_fn.0[rip]
	mov	DWORD PTR 76[rsp], ebx
	mov	DWORD PTR 72[rsp], r15d
	mov	QWORD PTR 64[rsp], r14
	vmovaps	XMMWORD PTR 48[rsp], xmm2
	call	GOMP_parallel@PLT
	mov	rax, QWORD PTR 40[rsp]
	mov	rdx, QWORD PTR [r14]
	lea	r8, [rax+r12]
	cmp	rdx, -1
	jne	.L34
	mov	eax, 1
	.p2align 4
	.p2align 3
.L21:
	mov	ecx, eax
	inc	rax
	mov	rdx, QWORD PTR -8[r14+rax*8]
	cmp	rdx, -1
	je	.L21
	sal	ecx, 6
.L20:
	not	rdx
	inc	r15
	tzcnt	rdx, rdx
	add	edx, ecx
	mov	DWORD PTR [r8], edx
	mov	r8d, DWORD PTR 0[r13]
	cmp	r8d, r15d
	jle	.L53
	mov	rax, QWORD PTR 32[rsp]
	movsx	r8, DWORD PTR [rax+r15*4]
	mov	rax, QWORD PTR 16[r13]
	lea	r12, 0[0+r8*4]
	mov	rbx, r8
	mov	eax, DWORD PTR [rax+r12]
	lea	edx, 3[rax]
	jmp	.L17
	.p2align 4
	.p2align 3
.L53:
	test	r8d, r8d
	jle	.L16
	mov	rdi, QWORD PTR 40[rsp]
	lea	eax, -1[r8]
	mov	r15, rax
	lea	rsi, 4[rdi+rax*4]
	mov	r12, rdi
	mov	rax, rdi
	.p2align 4
	.p2align 3
.L25:
	mov	ecx, DWORD PTR [rax]
	test	ecx, ecx
	jle	.L23
	mov	ebx, DWORD PTR 8[r13]
	lea	edx, 1[rbx]
	cmp	ecx, edx
	jg	.L23
	add	rax, 4
	cmp	rax, rsi
	jne	.L25
	mov	rdi, r14
	mov	DWORD PTR 32[rsp], r8d
	call	free@PLT
	mov	rax, QWORD PTR 40[rsp]
	mov	r8d, DWORD PTR 32[rsp]
	mov	eax, DWORD PTR [rax]
	cmp	r8d, 1
	je	.L10
	lea	edx, -2[r8]
	cmp	edx, 6
	jbe	.L35
	vmovd	xmm0, eax
	mov	eax, r15d
	shr	eax, 3
	vpbroadcastd	ymm0, xmm0
	sal	rax, 5
	add	rax, QWORD PTR 40[rsp]
	.p2align 4
	.p2align 3
.L28:
	vpmaxsd	ymm0, ymm0, YMMWORD PTR 4[r12]
	add	r12, 32
	cmp	r12, rax
	jne	.L28
	vextracti128	xmm1, ymm0, 0x1
	mov	ecx, r15d
	vpmaxsd	xmm0, xmm1, xmm0
	and	ecx, -8
	vpsrldq	xmm1, xmm0, 8
	vpmaxsd	xmm0, xmm0, xmm1
	lea	edx, 1[rcx]
	vpsrldq	xmm1, xmm0, 4
	vpmaxsd	xmm0, xmm0, xmm1
	vmovd	eax, xmm0
	cmp	ecx, r15d
	je	.L54
	vzeroupper
.L27:
	mov	rdi, QWORD PTR 40[rsp]
	movsx	rcx, edx
	mov	ecx, DWORD PTR [rdi+rcx*4]
	cmp	eax, ecx
	cmovl	eax, ecx
	lea	ecx, 1[rdx]
	cmp	r8d, ecx
	jle	.L10
	movsx	rcx, ecx
	mov	ecx, DWORD PTR [rdi+rcx*4]
	cmp	eax, ecx
	cmovl	eax, ecx
	lea	ecx, 2[rdx]
	cmp	r8d, ecx
	jle	.L10
	movsx	rcx, ecx
	mov	ecx, DWORD PTR [rdi+rcx*4]
	cmp	eax, ecx
	cmovl	eax, ecx
	lea	ecx, 3[rdx]
	cmp	r8d, ecx
	jle	.L10
	movsx	rcx, ecx
	mov	ecx, DWORD PTR [rdi+rcx*4]
	cmp	eax, ecx
	cmovl	eax, ecx
	lea	ecx, 4[rdx]
	cmp	r8d, ecx
	jle	.L10
	movsx	rcx, ecx
	mov	ecx, DWORD PTR [rdi+rcx*4]
	cmp	eax, ecx
	cmovl	eax, ecx
	lea	ecx, 5[rdx]
	cmp	r8d, ecx
	jle	.L10
	movsx	rcx, ecx
	mov	ecx, DWORD PTR [rdi+rcx*4]
	cmp	eax, ecx
	cmovl	eax, ecx
	add	edx, 6
	cmp	r8d, edx
	jle	.L10
	movsx	rdx, edx
	mov	edx, DWORD PTR [rdi+rdx*4]
	cmp	eax, edx
	cmovl	eax, edx
.L10:
	mov	rdi, QWORD PTR 88[rsp]
	xor	rdi, QWORD PTR fs:40
	jne	.L55
	lea	rsp, -40[rbp]
	pop	rbx
	pop	r12
	pop	r13
	pop	r14
	pop	r15
	pop	rbp
	ret
	.p2align 4
	.p2align 3
.L34:
	xor	ecx, ecx
	jmp	.L20
.L16:
	mov	rdi, r14
	call	free@PLT
	lea	rcx, __PRETTY_FUNCTION__.4441[rip]
	mov	edx, 68
	lea	rsi, .LC1[rip]
	lea	rdi, .LC6[rip]
	call	__assert_fail@PLT
.L54:
	vzeroupper
	jmp	.L10
.L35:
	mov	edx, 1
	jmp	.L27
.L36:
	lea	rcx, __PRETTY_FUNCTION__.4453[rip]
	mov	edx, 98
	lea	rsi, .LC1[rip]
	lea	rdi, .LC2[rip]
	call	__assert_fail@PLT
.L23:
	lea	rcx, __PRETTY_FUNCTION__.4453[rip]
	mov	edx, 118
	lea	rsi, .LC1[rip]
	lea	rdi, .LC5[rip]
	call	__assert_fail@PLT
.L51:
	lea	rcx, __PRETTY_FUNCTION__.4418[rip]
	mov	edx, 22
	lea	rsi, .LC1[rip]
	lea	rdi, .LC4[rip]
	call	__assert_fail@PLT
.L52:
	lea	rcx, __PRETTY_FUNCTION__.4418[rip]
	mov	edx, 23
	lea	rsi, .LC1[rip]
	lea	rdi, .LC3[rip]
	call	__assert_fail@PLT
.L55:
	call	__stack_chk_fail@PLT
.L50:
	lea	rcx, __PRETTY_FUNCTION__.4411[rip]
	mov	edx, 13
	lea	rsi, .LC1[rip]
	lea	rdi, .LC3[rip]
	call	__assert_fail@PLT
	.size	greedy, .-greedy
	.section	.rodata
	.align 8
	.type	__PRETTY_FUNCTION__.4441, @object
	.size	__PRETTY_FUNCTION__.4441, 12
__PRETTY_FUNCTION__.4441:
	.string	"maximum_i32"
	.align 8
	.type	__PRETTY_FUNCTION__.4418, @object
	.size	__PRETTY_FUNCTION__.4418, 11
__PRETTY_FUNCTION__.4418:
	.string	"bits_clear"
	.align 8
	.type	__PRETTY_FUNCTION__.4411, @object
	.size	__PRETTY_FUNCTION__.4411, 9
__PRETTY_FUNCTION__.4411:
	.string	"bits_new"
	.type	__PRETTY_FUNCTION__.4453, @object
	.size	__PRETTY_FUNCTION__.4453, 7
__PRETTY_FUNCTION__.4453:
	.string	"greedy"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	 1f - 0f
	.long	 4f - 1f
	.long	 5
0:
	.string	 "GNU"
1:
	.align 8
	.long	 0xc0000002
	.long	 3f - 2f
2:
	.long	 0x3
3:
	.align 8
4:
