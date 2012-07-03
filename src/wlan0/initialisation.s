	.file	"initialisation.cpp"
	.text
.globl _ZN5Modal4mainEiPPc
	.type	_ZN5Modal4mainEiPPc, @function
_ZN5Modal4mainEiPPc:
.LFB8:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	movq	%rsp, %rbp
	.cfi_offset 6, -16
	.cfi_def_cfa_register 6
	movl	%edi, -4(%rbp)
	movq	%rsi, -16(%rbp)
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE8:
	.size	_ZN5Modal4mainEiPPc, .-_ZN5Modal4mainEiPPc
	.section	.rodata
	.align 8
.LC0:
	.string	"%-8.16s  Interface doesn't support scanning.\n\n"
.LC1:
	.string	"essid"
	.align 8
.LC2:
	.string	"Too few arguments for scanning option [%s]\n"
.LC3:
	.string	"last"
.LC4:
	.string	"Invalid scanning option [%s]\n"
	.align 8
.LC5:
	.string	"%-8.16s  Interface doesn't support scanning : %s\n\n"
	.align 8
.LC6:
	.string	"Unhandled signal - exiting...\n"
.LC7:
	.string	"%s: Allocation failed\n"
	.align 8
.LC8:
	.string	"%-8.16s  Failed to read scan data : %s\n\n"
.LC9:
	.string	"%-8.16s  Scan completed :\n"
	.align 8
.LC10:
	.string	"          Cell %02d - Address: %s\n"
	.align 8
.LC11:
	.string	"                    NWID:off/any"
.LC12:
	.string	"                    NWID:%X\n"
.LC13:
	.string	"                    %s\n"
.LC14:
	.string	"                    Mode:%s\n"
	.align 8
.LC15:
	.string	"                    Protocol:%-1.16s\n"
	.align 8
.LC16:
	.string	"                    ESSID:\"%s\" [%d]\n"
	.align 8
.LC17:
	.string	"                    ESSID:\"%s\"\n"
	.align 8
.LC18:
	.string	"                    ESSID:off/any/hidden"
	.align 8
.LC19:
	.string	"                    Encryption key:"
.LC20:
	.string	"off"
.LC21:
	.string	"%s"
.LC22:
	.string	" [%d]"
.LC23:
	.string	"   Security mode:restricted"
.LC24:
	.string	"   Security mode:open"
	.align 8
.LC25:
	.string	"                    Bit Rates:"
	.align 8
.LC26:
	.string	"\n                              "
.LC27:
	.string	"; "
	.align 8
.LC28:
	.string	"                    Modulations :"
.LC29:
	.string	"\n                        "
.LC30:
	.string	" ; "
.LC31:
	.string	"                    Extra:%s\n"
	.align 8
.LC32:
	.string	"                    (Unknown Wireless Token 0x%04X)\n"
.LC33:
	.string	"%-8.16s  No scan results\n\n"
	.text
	.type	_ZN5ModalL19print_scanning_infoEiPcPS0_i, @function
_ZN5ModalL19print_scanning_infoEiPcPS0_i:
.LFB10:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	movq	%rsp, %rbp
	.cfi_offset 6, -16
	.cfi_def_cfa_register 6
	pushq	%r12
	pushq	%rbx
	subq	$1680, %rsp
	movl	%edi, -1668(%rbp)
	movq	%rsi, -1680(%rbp)
	movq	%rdx, -1688(%rbp)
	movl	%ecx, -1692(%rbp)
	movl	$0, -20(%rbp)
	movq	$0, -32(%rbp)
	movl	$4096, -36(%rbp)
	movl	$15000000, -40(%rbp)
	leaq	-1664(%rbp), %rdx
	movq	-1680(%rbp), %rcx
	movl	-1668(%rbp), %eax
	movq	%rcx, %rsi
	movl	%eax, %edi
	.cfi_offset 3, -32
	.cfi_offset 12, -24
	call	iw_get_range_info
	notl	%eax
	shrl	$31, %eax
	movl	%eax, -44(%rbp)
	cmpl	$0, -44(%rbp)
	je	.L3
	movzbl	-1384(%rbp), %eax
	cmpb	$13, %al
	ja	.L4
.L3:
	movq	stderr(%rip), %rax
	movq	-1680(%rbp), %rdx
	movl	$.LC0, %esi
	movq	%rax, %rdi
	movl	$0, %eax
	call	fprintf
	movl	$-1, %eax
	jmp	.L5
.L4:
	movq	$0, -240(%rbp)
	movq	$250000, -232(%rbp)
	leaq	-1072(%rbp), %rax
	movl	$316, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	memset
	jmp	.L6
.L12:
	subl	$1, -1692(%rbp)
	movq	-1688(%rbp), %rax
	movq	(%rax), %rax
	movl	$5, %edx
	movl	$.LC1, %esi
	movq	%rax, %rdi
	call	strncmp
	testl	%eax, %eax
	jne	.L7
	cmpl	$0, -1692(%rbp)
	jg	.L8
	movq	-1688(%rbp), %rax
	movq	(%rax), %rdx
	movq	stderr(%rip), %rax
	movl	$.LC2, %esi
	movq	%rax, %rdi
	movl	$0, %eax
	call	fprintf
	movl	$-1, %eax
	jmp	.L5
.L8:
	addq	$8, -1688(%rbp)
	subl	$1, -1692(%rbp)
	movq	-1688(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, %rdi
	call	strlen
	movb	%al, -1071(%rbp)
	movzbl	-1071(%rbp), %eax
	movzbl	%al, %edx
	movq	-1688(%rbp), %rax
	movq	(%rax), %rax
	leaq	-1072(%rbp), %rcx
	addq	$20, %rcx
	movq	%rax, %rsi
	movq	%rcx, %rdi
	call	memcpy
	movzwl	-1068(%rbp), %eax
	testw	%ax, %ax
	jne	.L9
	movw	$1, -1068(%rbp)
	leaq	-1072(%rbp), %rax
	addq	$6, %rax
	movl	$6, %edx
	movl	$255, %esi
	movq	%rax, %rdi
	call	memset
.L9:
	orl	$2, -20(%rbp)
	jmp	.L10
.L7:
	movq	-1688(%rbp), %rax
	movq	(%rax), %rax
	movl	$4, %edx
	movl	$.LC3, %esi
	movq	%rax, %rdi
	call	strncmp
	testl	%eax, %eax
	jne	.L11
	orl	$32768, -20(%rbp)
	jmp	.L10
.L11:
	movq	-1688(%rbp), %rax
	movq	(%rax), %rdx
	movq	stderr(%rip), %rax
	movl	$.LC4, %esi
	movq	%rax, %rdi
	movl	$0, %eax
	call	fprintf
	movl	$-1, %eax
	jmp	.L5
.L10:
	addq	$8, -1688(%rbp)
.L6:
	cmpl	$0, -1692(%rbp)
	setg	%al
	testb	%al, %al
	jne	.L12
	cmpl	$0, -20(%rbp)
	je	.L13
	leaq	-1072(%rbp), %rax
	movq	%rax, -336(%rbp)
	movw	$316, -328(%rbp)
	movl	-20(%rbp), %eax
	movw	%ax, -326(%rbp)
	jmp	.L14
.L13:
	movq	$0, -336(%rbp)
	movw	$0, -326(%rbp)
	movw	$0, -328(%rbp)
.L14:
	cmpl	$32768, -20(%rbp)
	jne	.L15
	movq	$0, -232(%rbp)
	jmp	.L16
.L15:
	movl	-1668(%rbp), %eax
	movl	%eax, -80(%rbp)
	movq	-1680(%rbp), %rax
	movq	%rax, -88(%rbp)
	movl	$35608, -92(%rbp)
	leaq	-352(%rbp), %rax
	movq	%rax, -104(%rbp)
	movq	-104(%rbp), %rax
	movq	-88(%rbp), %rcx
	movl	$16, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	strncpy
	movl	-92(%rbp), %eax
	movslq	%eax, %rcx
	movq	-104(%rbp), %rdx
	movl	-80(%rbp), %eax
	movq	%rcx, %rsi
	movl	%eax, %edi
	movl	$0, %eax
	call	ioctl
	shrl	$31, %eax
	testb	%al, %al
	je	.L16
	call	__errno_location
	movl	(%rax), %eax
	cmpl	$1, %eax
	jne	.L17
	cmpl	$0, -20(%rbp)
	je	.L18
.L17:
	call	__errno_location
	movl	(%rax), %eax
	movl	%eax, %edi
	call	strerror
	movq	%rax, %rcx
	movq	stderr(%rip), %rax
	movq	-1680(%rbp), %rdx
	movl	$.LC5, %esi
	movq	%rax, %rdi
	movl	$0, %eax
	call	fprintf
	movl	$-1, %eax
	jmp	.L5
.L18:
	movq	$0, -232(%rbp)
.L16:
	movl	-40(%rbp), %edx
	movq	-232(%rbp), %rax
	movl	%edx, %ecx
	subl	%eax, %ecx
	movl	%ecx, %eax
	movl	%eax, -40(%rbp)
	jmp	.L33
.L75:
	nop
.L33:
	movl	$0, %eax
	movl	$16, %edx
	leaq	-752(%rbp), %rbx
	movq	%rdx, %rcx
	movq	%rbx, %rdi
#APP
# 341 "initialisation.cpp" 1
	cld; rep; stosq
# 0 "" 2
#NO_APP
	movl	%edi, %ebx
	movl	%ecx, %r12d
	movl	%r12d, -48(%rbp)
	movl	%ebx, -52(%rbp)
	movl	$-1, -56(%rbp)
	movl	-56(%rbp), %eax
	leal	1(%rax), %ebx
	leaq	-240(%rbp), %rdx
	leaq	-752(%rbp), %rax
	movq	%rdx, %r8
	movl	$0, %ecx
	movl	$0, %edx
	movq	%rax, %rsi
	movl	%ebx, %edi
	call	select
	movl	%eax, -60(%rbp)
	cmpl	$0, -60(%rbp)
	jns	.L19
	call	__errno_location
	movl	(%rax), %eax
	cmpl	$11, %eax
	je	.L20
	call	__errno_location
	movl	(%rax), %eax
	cmpl	$4, %eax
	jne	.L21
.L20:
	jmp	.L22
.L21:
	movq	stderr(%rip), %rax
	movq	%rax, %rcx
	movl	$30, %edx
	movl	$1, %esi
	movl	$.LC6, %edi
	call	fwrite
	movl	$-1, %eax
	jmp	.L5
.L19:
	cmpl	$0, -60(%rbp)
	jne	.L75
.L23:
	movl	-36(%rbp), %eax
	movslq	%eax, %rdx
	movq	-32(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	realloc
	movq	%rax, -72(%rbp)
	cmpq	$0, -72(%rbp)
	jne	.L24
	cmpq	$0, -32(%rbp)
	je	.L25
	movq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	free
.L25:
	movq	stderr(%rip), %rax
	movl	$_ZZN5ModalL19print_scanning_infoEiPcPS0_iE12__FUNCTION__, %edx
	movl	$.LC7, %esi
	movq	%rax, %rdi
	movl	$0, %eax
	call	fprintf
	movl	$-1, %eax
	jmp	.L5
.L24:
	movq	-72(%rbp), %rax
	movq	%rax, -32(%rbp)
	movq	-32(%rbp), %rax
	movq	%rax, -336(%rbp)
	movw	$0, -326(%rbp)
	movl	-36(%rbp), %eax
	movw	%ax, -328(%rbp)
	movl	-1668(%rbp), %eax
	movl	%eax, -108(%rbp)
	movq	-1680(%rbp), %rax
	movq	%rax, -120(%rbp)
	movl	$35609, -124(%rbp)
	leaq	-352(%rbp), %rax
	movq	%rax, -136(%rbp)
	movq	-136(%rbp), %rax
	movq	-120(%rbp), %rcx
	movl	$16, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	strncpy
	movl	-124(%rbp), %eax
	movslq	%eax, %rcx
	movq	-136(%rbp), %rdx
	movl	-108(%rbp), %eax
	movq	%rcx, %rsi
	movl	%eax, %edi
	movl	$0, %eax
	call	ioctl
	shrl	$31, %eax
	testb	%al, %al
	je	.L26
	call	__errno_location
	movl	(%rax), %eax
	cmpl	$7, %eax
	jne	.L27
	movzbl	-1384(%rbp), %eax
	cmpb	$16, %al
	jbe	.L27
	movzwl	-328(%rbp), %eax
	movzwl	%ax, %eax
	cmpl	-36(%rbp), %eax
	jle	.L28
	movzwl	-328(%rbp), %eax
	movzwl	%ax, %eax
	movl	%eax, -36(%rbp)
	jmp	.L23
.L28:
	sall	-36(%rbp)
	jmp	.L23
.L27:
	call	__errno_location
	movl	(%rax), %eax
	cmpl	$11, %eax
	jne	.L30
	movq	$0, -240(%rbp)
	movq	$100000, -232(%rbp)
	movl	-40(%rbp), %edx
	movq	-232(%rbp), %rax
	movl	%edx, %ecx
	subl	%eax, %ecx
	movl	%ecx, %eax
	movl	%eax, -40(%rbp)
	cmpl	$0, -40(%rbp)
	jle	.L30
	jmp	.L22
.L30:
	movq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	free
	call	__errno_location
	movl	(%rax), %eax
	movl	%eax, %edi
	call	strerror
	movq	%rax, %rcx
	movq	stderr(%rip), %rax
	movq	-1680(%rbp), %rdx
	movl	$.LC8, %esi
	movq	%rax, %rdi
	movl	$0, %eax
	call	fprintf
	movl	$-2, %eax
	jmp	.L5
.L26:
	movzwl	-328(%rbp), %eax
	testw	%ax, %ax
	jne	.L31
	jmp	.L74
.L22:
	jmp	.L33
.L31:
	movl	$1, -320(%rbp)
	movl	$0, -316(%rbp)
	movq	-1680(%rbp), %rax
	movq	%rax, %rsi
	movl	$.LC9, %edi
	movl	$0, %eax
	call	printf
	movzwl	-328(%rbp), %eax
	movzwl	%ax, %edx
	movq	-32(%rbp), %rcx
	leaq	-304(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	iw_init_event_stream
.L72:
	movzbl	-1384(%rbp), %eax
	movzbl	%al, %edx
	leaq	-272(%rbp), %rcx
	leaq	-304(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	iw_extract_event_stream
	movl	%eax, -76(%rbp)
	cmpl	$0, -76(%rbp)
	jle	.L34
	leaq	-304(%rbp), %rax
	movq	%rax, -144(%rbp)
	leaq	-272(%rbp), %rax
	movq	%rax, -152(%rbp)
	leaq	-320(%rbp), %rax
	movq	%rax, -160(%rbp)
	leaq	-1664(%rbp), %rax
	movq	%rax, -168(%rbp)
	movl	-44(%rbp), %eax
	movl	%eax, -172(%rbp)
	movq	-152(%rbp), %rax
	movzwl	2(%rax), %eax
	movzwl	%ax, %eax
	cmpl	$35611, %eax
	je	.L41
	cmpl	$35611, %eax
	jg	.L47
	cmpl	$35589, %eax
	je	.L38
	cmpl	$35589, %eax
	jg	.L48
	cmpl	$35585, %eax
	je	.L36
	cmpl	$35587, %eax
	je	.L37
	jmp	.L35
.L48:
	cmpl	$35591, %eax
	je	.L39
	cmpl	$35605, %eax
	je	.L40
	jmp	.L35
.L47:
	cmpl	$35631, %eax
	je	.L44
	cmpl	$35631, %eax
	jg	.L49
	cmpl	$35617, %eax
	je	.L42
	cmpl	$35627, %eax
	je	.L43
	jmp	.L35
.L49:
	cmpl	$35841, %eax
	je	.L45
	cmpl	$35842, %eax
	je	.L46
	jmp	.L35
.L40:
	movq	-152(%rbp), %rax
	addq	$8, %rax
	movq	%rax, -184(%rbp)
	leaq	-480(%rbp), %rax
	movq	%rax, -192(%rbp)
	movq	-184(%rbp), %rax
	addq	$2, %rax
	movq	-192(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	iw_ether_ntop
	movq	-192(%rbp), %rax
	movq	%rax, %rdx
	movq	-160(%rbp), %rax
	movl	(%rax), %eax
	movl	%eax, %esi
	movl	$.LC10, %edi
	movl	$0, %eax
	call	printf
	movq	-160(%rbp), %rax
	movl	(%rax), %eax
	leal	1(%rax), %edx
	movq	-160(%rbp), %rax
	movl	%edx, (%rax)
	jmp	.L34
.L37:
	movq	-152(%rbp), %rax
	movzbl	13(%rax), %eax
	testb	%al, %al
	je	.L50
	movl	$.LC11, %edi
	call	puts
	jmp	.L34
.L50:
	movq	-152(%rbp), %rax
	movl	8(%rax), %eax
	movl	%eax, %esi
	movl	$.LC12, %edi
	movl	$0, %eax
	call	printf
	jmp	.L34
.L38:
	movl	$-1, -196(%rbp)
	movq	-152(%rbp), %rax
	addq	$8, %rax
	movq	%rax, %rdi
	call	iw_freq2float
	movsd	%xmm0, -208(%rbp)
	cmpl	$0, -172(%rbp)
	je	.L51
	movq	-168(%rbp), %rax
	movsd	-208(%rbp), %xmm0
	movq	%rax, %rdi
	call	iw_freq_to_channel
	movl	%eax, -196(%rbp)
.L51:
	movq	-152(%rbp), %rax
	movzbl	15(%rax), %eax
	movzbl	%al, %ecx
	movl	-196(%rbp), %edx
	movsd	-208(%rbp), %xmm0
	leaq	-480(%rbp), %rax
	movl	$128, %esi
	movq	%rax, %rdi
	call	iw_print_freq
	leaq	-480(%rbp), %rax
	movq	%rax, %rsi
	movl	$.LC13, %edi
	movl	$0, %eax
	call	printf
	jmp	.L34
.L39:
	movq	-152(%rbp), %rax
	movl	8(%rax), %eax
	cmpl	$6, %eax
	jbe	.L52
	movq	-152(%rbp), %rax
	movl	$7, 8(%rax)
.L52:
	movq	-152(%rbp), %rax
	movl	8(%rax), %eax
	mov	%eax, %eax
	movq	iw_operation_mode(,%rax,8), %rax
	movq	%rax, %rsi
	movl	$.LC14, %edi
	movl	$0, %eax
	call	printf
	jmp	.L34
.L36:
	movq	-152(%rbp), %rax
	addq	$8, %rax
	movq	%rax, %rsi
	movl	$.LC15, %edi
	movl	$0, %eax
	call	printf
	jmp	.L34
.L41:
	leaq	-752(%rbp), %rax
	movl	$33, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	memset
	movq	-152(%rbp), %rax
	movq	8(%rax), %rax
	testq	%rax, %rax
	je	.L53
	movq	-152(%rbp), %rax
	movzwl	16(%rax), %eax
	testw	%ax, %ax
	je	.L53
	movq	-152(%rbp), %rax
	movzwl	16(%rax), %eax
	movzwl	%ax, %edx
	movq	-152(%rbp), %rax
	movq	8(%rax), %rcx
	leaq	-752(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	memcpy
.L53:
	movq	-152(%rbp), %rax
	movzwl	18(%rax), %eax
	testw	%ax, %ax
	je	.L54
	movq	-152(%rbp), %rax
	movzwl	18(%rax), %eax
	movzwl	%ax, %eax
	andl	$255, %eax
	cmpl	$1, %eax
	jle	.L55
	movq	-152(%rbp), %rax
	movzwl	18(%rax), %eax
	movzwl	%ax, %eax
	movzbl	%al, %edx
	leaq	-752(%rbp), %rax
	movq	%rax, %rsi
	movl	$.LC16, %edi
	movl	$0, %eax
	call	printf
	jmp	.L34
.L55:
	leaq	-752(%rbp), %rax
	movq	%rax, %rsi
	movl	$.LC17, %edi
	movl	$0, %eax
	call	printf
	jmp	.L34
.L54:
	movl	$.LC18, %edi
	call	puts
	jmp	.L34
.L43:
	movq	-152(%rbp), %rax
	movq	8(%rax), %rax
	testq	%rax, %rax
	je	.L56
	movq	-152(%rbp), %rax
	movzwl	16(%rax), %eax
	movzwl	%ax, %edx
	movq	-152(%rbp), %rax
	movq	8(%rax), %rcx
	leaq	-752(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	memcpy
	jmp	.L57
.L56:
	movq	-152(%rbp), %rax
	movzwl	18(%rax), %eax
	movl	%eax, %edx
	orb	$8, %dh
	movq	-152(%rbp), %rax
	movw	%dx, 18(%rax)
.L57:
	movl	$.LC19, %edi
	movl	$0, %eax
	call	printf
	movq	-152(%rbp), %rax
	movzwl	18(%rax), %eax
	testw	%ax, %ax
	jns	.L58
	movl	$.LC20, %edi
	call	puts
	jmp	.L34
.L58:
	movq	-152(%rbp), %rax
	movzwl	18(%rax), %eax
	movzwl	%ax, %ebx
	movq	-152(%rbp), %rax
	movzwl	16(%rax), %eax
	movzwl	%ax, %ecx
	leaq	-752(%rbp), %rdx
	leaq	-480(%rbp), %rax
	movl	%ebx, %r8d
	movl	$128, %esi
	movq	%rax, %rdi
	call	iw_print_key
	leaq	-480(%rbp), %rax
	movq	%rax, %rsi
	movl	$.LC21, %edi
	movl	$0, %eax
	call	printf
	movq	-152(%rbp), %rax
	movzwl	18(%rax), %eax
	movzwl	%ax, %eax
	andl	$255, %eax
	cmpl	$1, %eax
	jle	.L59
	movq	-152(%rbp), %rax
	movzwl	18(%rax), %eax
	movzwl	%ax, %eax
	andl	$255, %eax
	movl	%eax, %esi
	movl	$.LC22, %edi
	movl	$0, %eax
	call	printf
.L59:
	movq	-152(%rbp), %rax
	movzwl	18(%rax), %eax
	movzwl	%ax, %eax
	andl	$16384, %eax
	testl	%eax, %eax
	je	.L60
	movl	$.LC23, %edi
	movl	$0, %eax
	call	printf
.L60:
	movq	-152(%rbp), %rax
	movzwl	18(%rax), %eax
	movzwl	%ax, %eax
	andl	$8192, %eax
	testl	%eax, %eax
	je	.L61
	movl	$.LC24, %edi
	movl	$0, %eax
	call	printf
.L61:
	movl	$10, %edi
	call	putchar
	jmp	.L34
.L42:
	movq	-160(%rbp), %rax
	movl	4(%rax), %eax
	testl	%eax, %eax
	jne	.L62
	movl	$.LC25, %edi
	movl	$0, %eax
	call	printf
	jmp	.L63
.L62:
	movq	-160(%rbp), %rax
	movl	4(%rax), %ecx
	movl	$1717986919, %edx
	movl	%ecx, %eax
	imull	%edx
	sarl	%edx
	movl	%ecx, %eax
	sarl	$31, %eax
	subl	%eax, %edx
	movl	%edx, %eax
	sall	$2, %eax
	addl	%edx, %eax
	movl	%ecx, %edx
	subl	%eax, %edx
	testl	%edx, %edx
	jne	.L64
	movl	$.LC26, %edi
	movl	$0, %eax
	call	printf
	jmp	.L63
.L64:
	movl	$.LC27, %edi
	movl	$0, %eax
	call	printf
.L63:
	movq	-152(%rbp), %rax
	movl	8(%rax), %edx
	leaq	-480(%rbp), %rax
	movl	$128, %esi
	movq	%rax, %rdi
	call	iw_print_bitrate
	leaq	-480(%rbp), %rax
	movq	%rax, %rsi
	movl	$.LC21, %edi
	movl	$0, %eax
	call	printf
	movq	-144(%rbp), %rax
	movq	16(%rax), %rax
	testq	%rax, %rax
	jne	.L65
	movl	$10, %edi
	call	putchar
	movq	-160(%rbp), %rax
	movl	$0, 4(%rax)
	jmp	.L34
.L65:
	movq	-160(%rbp), %rax
	movl	4(%rax), %eax
	leal	1(%rax), %edx
	movq	-160(%rbp), %rax
	movl	%edx, 4(%rax)
	jmp	.L34
.L44:
	movq	-152(%rbp), %rax
	movl	8(%rax), %eax
	movl	%eax, -212(%rbp)
	movl	$0, -216(%rbp)
	movl	$.LC28, %edi
	movl	$0, %eax
	call	printf
	movl	$0, -220(%rbp)
	jmp	.L66
.L70:
	movl	-220(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	addq	$iw_modul_list, %rax
	movl	(%rax), %eax
	movl	%eax, %ecx
	andl	-212(%rbp), %ecx
	movl	-220(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	addq	$iw_modul_list, %rax
	movl	(%rax), %eax
	cmpl	%eax, %ecx
	jne	.L67
	movl	-216(%rbp), %eax
	movl	%eax, %edx
	sarl	$31, %edx
	shrl	$29, %edx
	addl	%edx, %eax
	andl	$7, %eax
	subl	%edx, %eax
	cmpl	$7, %eax
	sete	%al
	addl	$1, -216(%rbp)
	testb	%al, %al
	je	.L68
	movl	$.LC29, %edi
	movl	$0, %eax
	call	printf
	jmp	.L69
.L68:
	movl	$.LC30, %edi
	movl	$0, %eax
	call	printf
.L69:
	movl	-220(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	addq	$iw_modul_list, %rax
	addq	$4, %rax
	movq	%rax, %rsi
	movl	$.LC21, %edi
	movl	$0, %eax
	call	printf
.L67:
	addl	$1, -220(%rbp)
.L66:
	cmpl	$15, -220(%rbp)
	setle	%al
	testb	%al, %al
	jne	.L70
	movl	$10, %edi
	call	putchar
	jmp	.L34
.L45:
	movq	-152(%rbp), %rax
	leaq	8(%rax), %rbx
	movl	-172(%rbp), %ecx
	movq	-168(%rbp), %rdx
	leaq	-480(%rbp), %rax
	movl	%ecx, %r8d
	movq	%rdx, %rcx
	movq	%rbx, %rdx
	movl	$128, %esi
	movq	%rax, %rdi
	call	iw_print_stats
	leaq	-480(%rbp), %rax
	movq	%rax, %rsi
	movl	$.LC13, %edi
	movl	$0, %eax
	call	printf
	jmp	.L34
.L46:
	movq	-152(%rbp), %rax
	movq	8(%rax), %rax
	testq	%rax, %rax
	je	.L71
	movq	-152(%rbp), %rax
	movzwl	16(%rax), %eax
	testw	%ax, %ax
	je	.L71
	movq	-152(%rbp), %rax
	movzwl	16(%rax), %eax
	movzwl	%ax, %edx
	movq	-152(%rbp), %rax
	movq	8(%rax), %rcx
	leaq	-752(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	memcpy
.L71:
	movq	-152(%rbp), %rax
	movzwl	16(%rax), %eax
	movzwl	%ax, %eax
	cltq
	movb	$0, -752(%rbp,%rax)
	leaq	-752(%rbp), %rax
	movq	%rax, %rsi
	movl	$.LC31, %edi
	movl	$0, %eax
	call	printf
	jmp	.L34
.L35:
	movq	-152(%rbp), %rax
	movzwl	2(%rax), %eax
	movzwl	%ax, %eax
	movl	%eax, %esi
	movl	$.LC32, %edi
	movl	$0, %eax
	call	printf
.L34:
	cmpl	$0, -76(%rbp)
	setg	%al
	testb	%al, %al
	jne	.L72
	movl	$10, %edi
	call	putchar
	jmp	.L73
.L74:
	movq	-1680(%rbp), %rax
	movq	%rax, %rsi
	movl	$.LC33, %edi
	movl	$0, %eax
	call	printf
.L73:
	movq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	free
	movl	$0, %eax
.L5:
	addq	$1680, %rsp
	popq	%rbx
	popq	%r12
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE10:
	.size	_ZN5ModalL19print_scanning_infoEiPcPS0_i, .-_ZN5ModalL19print_scanning_infoEiPcPS0_i
.globl _ZN5Modal12sockets_openEv
	.type	_ZN5Modal12sockets_openEv, @function
_ZN5Modal12sockets_openEv:
.LFB11:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	movq	%rsp, %rbp
	.cfi_offset 6, -16
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	$0, %edx
	movl	$2, %esi
	movl	$10, %edi
	call	socket
	movl	%eax, -4(%rbp)
	cmpl	$0, -4(%rbp)
	js	.L77
	movl	-4(%rbp), %eax
	jmp	.L78
.L77:
	movl	$-1, %eax
.L78:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE11:
	.size	_ZN5Modal12sockets_openEv, .-_ZN5Modal12sockets_openEv
	.section	.rodata
	.align 16
	.type	_ZZN5ModalL19print_scanning_infoEiPcPS0_iE12__FUNCTION__, @object
	.size	_ZZN5ModalL19print_scanning_infoEiPcPS0_iE12__FUNCTION__, 20
_ZZN5ModalL19print_scanning_infoEiPcPS0_iE12__FUNCTION__:
	.string	"print_scanning_info"
	.ident	"GCC: (Gentoo 4.5.3-r2 p1.1, pie-0.4.7) 4.5.3"
	.section	.note.GNU-stack,"",@progbits
