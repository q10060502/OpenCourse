	.file	"demo.c"
	.text
.Ltext0:
	.section	.rodata
.LC0:
	.string	"%d,%d\n"
.LC1:
	.string	"%d\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB2:
	.file 1 "demo.c"
	.loc 1 14 0
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	.loc 1 15 0
	movl	$28, %edx
	movl	$16, %esi
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	.loc 1 16 0
	movl	$12, %esi
	leaq	.LC1(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	.loc 1 17 0
	movl	$0, %eax
	.loc 1 18 0
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	main, .-main
.Letext0:
	.file 2 "/usr/lib/gcc/x86_64-linux-gnu/6/include/stddef.h"
	.file 3 "/usr/include/x86_64-linux-gnu/bits/types.h"
	.file 4 "/usr/include/libio.h"
	.file 5 "/usr/include/stdio.h"
	.file 6 "/usr/include/x86_64-linux-gnu/bits/sys_errlist.h"
	.file 7 "/usr/include/unistd.h"
	.file 8 "/usr/include/getopt.h"
	.file 9 "/usr/include/stdint.h"
	.file 10 "/usr/include/netinet/in.h"
	.file 11 "/usr/include/signal.h"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.long	0x445
	.value	0x4
	.long	.Ldebug_abbrev0
	.byte	0x8
	.uleb128 0x1
	.long	.LASF73
	.byte	0xc
	.long	.LASF74
	.long	.LASF75
	.quad	.Ltext0
	.quad	.Letext0-.Ltext0
	.long	.Ldebug_line0
	.uleb128 0x2
	.long	.LASF7
	.byte	0x2
	.byte	0xd8
	.long	0x38
	.uleb128 0x3
	.byte	0x8
	.byte	0x7
	.long	.LASF0
	.uleb128 0x3
	.byte	0x1
	.byte	0x8
	.long	.LASF1
	.uleb128 0x3
	.byte	0x2
	.byte	0x7
	.long	.LASF2
	.uleb128 0x3
	.byte	0x4
	.byte	0x7
	.long	.LASF3
	.uleb128 0x3
	.byte	0x1
	.byte	0x6
	.long	.LASF4
	.uleb128 0x3
	.byte	0x2
	.byte	0x5
	.long	.LASF5
	.uleb128 0x4
	.byte	0x4
	.byte	0x5
	.string	"int"
	.uleb128 0x3
	.byte	0x8
	.byte	0x5
	.long	.LASF6
	.uleb128 0x2
	.long	.LASF8
	.byte	0x3
	.byte	0x83
	.long	0x69
	.uleb128 0x2
	.long	.LASF9
	.byte	0x3
	.byte	0x84
	.long	0x69
	.uleb128 0x3
	.byte	0x8
	.byte	0x7
	.long	.LASF10
	.uleb128 0x5
	.byte	0x8
	.uleb128 0x6
	.byte	0x8
	.long	0x95
	.uleb128 0x3
	.byte	0x1
	.byte	0x6
	.long	.LASF11
	.uleb128 0x7
	.long	0x95
	.uleb128 0x8
	.long	.LASF41
	.byte	0xd8
	.byte	0x4
	.byte	0xf1
	.long	0x21e
	.uleb128 0x9
	.long	.LASF12
	.byte	0x4
	.byte	0xf2
	.long	0x62
	.byte	0
	.uleb128 0x9
	.long	.LASF13
	.byte	0x4
	.byte	0xf7
	.long	0x8f
	.byte	0x8
	.uleb128 0x9
	.long	.LASF14
	.byte	0x4
	.byte	0xf8
	.long	0x8f
	.byte	0x10
	.uleb128 0x9
	.long	.LASF15
	.byte	0x4
	.byte	0xf9
	.long	0x8f
	.byte	0x18
	.uleb128 0x9
	.long	.LASF16
	.byte	0x4
	.byte	0xfa
	.long	0x8f
	.byte	0x20
	.uleb128 0x9
	.long	.LASF17
	.byte	0x4
	.byte	0xfb
	.long	0x8f
	.byte	0x28
	.uleb128 0x9
	.long	.LASF18
	.byte	0x4
	.byte	0xfc
	.long	0x8f
	.byte	0x30
	.uleb128 0x9
	.long	.LASF19
	.byte	0x4
	.byte	0xfd
	.long	0x8f
	.byte	0x38
	.uleb128 0x9
	.long	.LASF20
	.byte	0x4
	.byte	0xfe
	.long	0x8f
	.byte	0x40
	.uleb128 0xa
	.long	.LASF21
	.byte	0x4
	.value	0x100
	.long	0x8f
	.byte	0x48
	.uleb128 0xa
	.long	.LASF22
	.byte	0x4
	.value	0x101
	.long	0x8f
	.byte	0x50
	.uleb128 0xa
	.long	.LASF23
	.byte	0x4
	.value	0x102
	.long	0x8f
	.byte	0x58
	.uleb128 0xa
	.long	.LASF24
	.byte	0x4
	.value	0x104
	.long	0x256
	.byte	0x60
	.uleb128 0xa
	.long	.LASF25
	.byte	0x4
	.value	0x106
	.long	0x25c
	.byte	0x68
	.uleb128 0xa
	.long	.LASF26
	.byte	0x4
	.value	0x108
	.long	0x62
	.byte	0x70
	.uleb128 0xa
	.long	.LASF27
	.byte	0x4
	.value	0x10c
	.long	0x62
	.byte	0x74
	.uleb128 0xa
	.long	.LASF28
	.byte	0x4
	.value	0x10e
	.long	0x70
	.byte	0x78
	.uleb128 0xa
	.long	.LASF29
	.byte	0x4
	.value	0x112
	.long	0x46
	.byte	0x80
	.uleb128 0xa
	.long	.LASF30
	.byte	0x4
	.value	0x113
	.long	0x54
	.byte	0x82
	.uleb128 0xa
	.long	.LASF31
	.byte	0x4
	.value	0x114
	.long	0x262
	.byte	0x83
	.uleb128 0xa
	.long	.LASF32
	.byte	0x4
	.value	0x118
	.long	0x272
	.byte	0x88
	.uleb128 0xa
	.long	.LASF33
	.byte	0x4
	.value	0x121
	.long	0x7b
	.byte	0x90
	.uleb128 0xa
	.long	.LASF34
	.byte	0x4
	.value	0x129
	.long	0x8d
	.byte	0x98
	.uleb128 0xa
	.long	.LASF35
	.byte	0x4
	.value	0x12a
	.long	0x8d
	.byte	0xa0
	.uleb128 0xa
	.long	.LASF36
	.byte	0x4
	.value	0x12b
	.long	0x8d
	.byte	0xa8
	.uleb128 0xa
	.long	.LASF37
	.byte	0x4
	.value	0x12c
	.long	0x8d
	.byte	0xb0
	.uleb128 0xa
	.long	.LASF38
	.byte	0x4
	.value	0x12e
	.long	0x2d
	.byte	0xb8
	.uleb128 0xa
	.long	.LASF39
	.byte	0x4
	.value	0x12f
	.long	0x62
	.byte	0xc0
	.uleb128 0xa
	.long	.LASF40
	.byte	0x4
	.value	0x131
	.long	0x278
	.byte	0xc4
	.byte	0
	.uleb128 0xb
	.long	.LASF76
	.byte	0x4
	.byte	0x96
	.uleb128 0x8
	.long	.LASF42
	.byte	0x18
	.byte	0x4
	.byte	0x9c
	.long	0x256
	.uleb128 0x9
	.long	.LASF43
	.byte	0x4
	.byte	0x9d
	.long	0x256
	.byte	0
	.uleb128 0x9
	.long	.LASF44
	.byte	0x4
	.byte	0x9e
	.long	0x25c
	.byte	0x8
	.uleb128 0x9
	.long	.LASF45
	.byte	0x4
	.byte	0xa2
	.long	0x62
	.byte	0x10
	.byte	0
	.uleb128 0x6
	.byte	0x8
	.long	0x225
	.uleb128 0x6
	.byte	0x8
	.long	0xa1
	.uleb128 0xc
	.long	0x95
	.long	0x272
	.uleb128 0xd
	.long	0x86
	.byte	0
	.byte	0
	.uleb128 0x6
	.byte	0x8
	.long	0x21e
	.uleb128 0xc
	.long	0x95
	.long	0x288
	.uleb128 0xd
	.long	0x86
	.byte	0x13
	.byte	0
	.uleb128 0xe
	.long	.LASF77
	.uleb128 0xf
	.long	.LASF46
	.byte	0x4
	.value	0x13b
	.long	0x288
	.uleb128 0xf
	.long	.LASF47
	.byte	0x4
	.value	0x13c
	.long	0x288
	.uleb128 0xf
	.long	.LASF48
	.byte	0x4
	.value	0x13d
	.long	0x288
	.uleb128 0x6
	.byte	0x8
	.long	0x9c
	.uleb128 0x7
	.long	0x2b1
	.uleb128 0x10
	.long	.LASF49
	.byte	0x5
	.byte	0xaa
	.long	0x25c
	.uleb128 0x10
	.long	.LASF50
	.byte	0x5
	.byte	0xab
	.long	0x25c
	.uleb128 0x10
	.long	.LASF51
	.byte	0x5
	.byte	0xac
	.long	0x25c
	.uleb128 0x10
	.long	.LASF52
	.byte	0x6
	.byte	0x1a
	.long	0x62
	.uleb128 0xc
	.long	0x2b7
	.long	0x2f3
	.uleb128 0x11
	.byte	0
	.uleb128 0x7
	.long	0x2e8
	.uleb128 0x10
	.long	.LASF53
	.byte	0x6
	.byte	0x1b
	.long	0x2f3
	.uleb128 0xf
	.long	.LASF54
	.byte	0x7
	.value	0x222
	.long	0x30f
	.uleb128 0x6
	.byte	0x8
	.long	0x8f
	.uleb128 0x10
	.long	.LASF55
	.byte	0x8
	.byte	0x39
	.long	0x8f
	.uleb128 0x10
	.long	.LASF56
	.byte	0x8
	.byte	0x47
	.long	0x62
	.uleb128 0x10
	.long	.LASF57
	.byte	0x8
	.byte	0x4c
	.long	0x62
	.uleb128 0x10
	.long	.LASF58
	.byte	0x8
	.byte	0x50
	.long	0x62
	.uleb128 0x2
	.long	.LASF59
	.byte	0x9
	.byte	0x30
	.long	0x3f
	.uleb128 0x2
	.long	.LASF60
	.byte	0x9
	.byte	0x31
	.long	0x46
	.uleb128 0x2
	.long	.LASF61
	.byte	0x9
	.byte	0x33
	.long	0x4d
	.uleb128 0x3
	.byte	0x8
	.byte	0x7
	.long	.LASF62
	.uleb128 0x3
	.byte	0x8
	.byte	0x5
	.long	.LASF63
	.uleb128 0x12
	.byte	0x10
	.byte	0xa
	.byte	0xd5
	.long	0x39a
	.uleb128 0x13
	.long	.LASF64
	.byte	0xa
	.byte	0xd7
	.long	0x39a
	.uleb128 0x13
	.long	.LASF65
	.byte	0xa
	.byte	0xd9
	.long	0x3aa
	.uleb128 0x13
	.long	.LASF66
	.byte	0xa
	.byte	0xda
	.long	0x3ba
	.byte	0
	.uleb128 0xc
	.long	0x341
	.long	0x3aa
	.uleb128 0xd
	.long	0x86
	.byte	0xf
	.byte	0
	.uleb128 0xc
	.long	0x34c
	.long	0x3ba
	.uleb128 0xd
	.long	0x86
	.byte	0x7
	.byte	0
	.uleb128 0xc
	.long	0x357
	.long	0x3ca
	.uleb128 0xd
	.long	0x86
	.byte	0x3
	.byte	0
	.uleb128 0x8
	.long	.LASF67
	.byte	0x10
	.byte	0xa
	.byte	0xd3
	.long	0x3e3
	.uleb128 0x9
	.long	.LASF68
	.byte	0xa
	.byte	0xdc
	.long	0x370
	.byte	0
	.byte	0
	.uleb128 0x7
	.long	0x3ca
	.uleb128 0x10
	.long	.LASF69
	.byte	0xa
	.byte	0xe5
	.long	0x3e3
	.uleb128 0x10
	.long	.LASF70
	.byte	0xa
	.byte	0xe6
	.long	0x3e3
	.uleb128 0xc
	.long	0x2b7
	.long	0x40e
	.uleb128 0xd
	.long	0x86
	.byte	0x40
	.byte	0
	.uleb128 0x7
	.long	0x3fe
	.uleb128 0xf
	.long	.LASF71
	.byte	0xb
	.value	0x12d
	.long	0x40e
	.uleb128 0xf
	.long	.LASF72
	.byte	0xb
	.value	0x12e
	.long	0x40e
	.uleb128 0x14
	.long	.LASF78
	.byte	0x1
	.byte	0xd
	.long	0x62
	.quad	.LFB2
	.quad	.LFE2-.LFB2
	.uleb128 0x1
	.byte	0x9c
	.byte	0
	.section	.debug_abbrev,"",@progbits
.Ldebug_abbrev0:
	.uleb128 0x1
	.uleb128 0x11
	.byte	0x1
	.uleb128 0x25
	.uleb128 0xe
	.uleb128 0x13
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1b
	.uleb128 0xe
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x7
	.uleb128 0x10
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x2
	.uleb128 0x16
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x3
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.byte	0
	.byte	0
	.uleb128 0x4
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0x8
	.byte	0
	.byte	0
	.uleb128 0x5
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x6
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x7
	.uleb128 0x26
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x8
	.uleb128 0x13
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x9
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xa
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xb
	.uleb128 0x16
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xc
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xd
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xe
	.uleb128 0x13
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3c
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0xf
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3c
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0x10
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3c
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0x11
	.uleb128 0x21
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x12
	.uleb128 0x17
	.byte	0x1
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x13
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x14
	.uleb128 0x2e
	.byte	0
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x7
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x2116
	.uleb128 0x19
	.byte	0
	.byte	0
	.byte	0
	.section	.debug_aranges,"",@progbits
	.long	0x2c
	.value	0x2
	.long	.Ldebug_info0
	.byte	0x8
	.byte	0
	.value	0
	.value	0
	.quad	.Ltext0
	.quad	.Letext0-.Ltext0
	.quad	0
	.quad	0
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.section	.debug_str,"MS",@progbits,1
.LASF56:
	.string	"optind"
.LASF55:
	.string	"optarg"
.LASF28:
	.string	"_old_offset"
.LASF52:
	.string	"sys_nerr"
.LASF23:
	.string	"_IO_save_end"
.LASF18:
	.string	"_IO_write_end"
.LASF5:
	.string	"short int"
.LASF7:
	.string	"size_t"
.LASF67:
	.string	"in6_addr"
.LASF10:
	.string	"sizetype"
.LASF33:
	.string	"_offset"
.LASF74:
	.string	"demo.c"
.LASF17:
	.string	"_IO_write_ptr"
.LASF78:
	.string	"main"
.LASF64:
	.string	"__u6_addr8"
.LASF54:
	.string	"__environ"
.LASF24:
	.string	"_markers"
.LASF72:
	.string	"sys_siglist"
.LASF59:
	.string	"uint8_t"
.LASF57:
	.string	"opterr"
.LASF68:
	.string	"__in6_u"
.LASF51:
	.string	"stderr"
.LASF63:
	.string	"long long int"
.LASF65:
	.string	"__u6_addr16"
.LASF32:
	.string	"_lock"
.LASF6:
	.string	"long int"
.LASF29:
	.string	"_cur_column"
.LASF48:
	.string	"_IO_2_1_stderr_"
.LASF77:
	.string	"_IO_FILE_plus"
.LASF45:
	.string	"_pos"
.LASF44:
	.string	"_sbuf"
.LASF70:
	.string	"in6addr_loopback"
.LASF41:
	.string	"_IO_FILE"
.LASF1:
	.string	"unsigned char"
.LASF4:
	.string	"signed char"
.LASF62:
	.string	"long long unsigned int"
.LASF61:
	.string	"uint32_t"
.LASF31:
	.string	"_shortbuf"
.LASF3:
	.string	"unsigned int"
.LASF42:
	.string	"_IO_marker"
.LASF46:
	.string	"_IO_2_1_stdin_"
.LASF14:
	.string	"_IO_read_end"
.LASF16:
	.string	"_IO_write_base"
.LASF40:
	.string	"_unused2"
.LASF75:
	.string	"/home/tx/program/web/web/tang.chat/www/lesson_asm/src/src"
.LASF71:
	.string	"_sys_siglist"
.LASF20:
	.string	"_IO_buf_end"
.LASF11:
	.string	"char"
.LASF60:
	.string	"uint16_t"
.LASF43:
	.string	"_next"
.LASF34:
	.string	"__pad1"
.LASF35:
	.string	"__pad2"
.LASF36:
	.string	"__pad3"
.LASF37:
	.string	"__pad4"
.LASF38:
	.string	"__pad5"
.LASF2:
	.string	"short unsigned int"
.LASF0:
	.string	"long unsigned int"
.LASF69:
	.string	"in6addr_any"
.LASF73:
	.string	"GNU C11 6.3.0 20170516 -m64 -mtune=generic -march=x86-64 -g"
.LASF9:
	.string	"__off64_t"
.LASF8:
	.string	"__off_t"
.LASF25:
	.string	"_chain"
.LASF22:
	.string	"_IO_backup_base"
.LASF49:
	.string	"stdin"
.LASF19:
	.string	"_IO_buf_base"
.LASF27:
	.string	"_flags2"
.LASF39:
	.string	"_mode"
.LASF15:
	.string	"_IO_read_base"
.LASF66:
	.string	"__u6_addr32"
.LASF30:
	.string	"_vtable_offset"
.LASF21:
	.string	"_IO_save_base"
.LASF53:
	.string	"sys_errlist"
.LASF58:
	.string	"optopt"
.LASF26:
	.string	"_fileno"
.LASF13:
	.string	"_IO_read_ptr"
.LASF12:
	.string	"_flags"
.LASF50:
	.string	"stdout"
.LASF47:
	.string	"_IO_2_1_stdout_"
.LASF76:
	.string	"_IO_lock_t"
	.ident	"GCC: (Debian 6.3.0-18+deb9u1) 6.3.0 20170516"
	.section	.note.GNU-stack,"",@progbits
