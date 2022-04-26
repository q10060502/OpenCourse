.macro disp
	ldr r2,=msg_size
	ldr r1,=msg
	mov r0,#1
	mov r7,#4
	swi #0
.endm
.global _start
.data
	b32: .long 0x676e6154		/*gnaT*/
	msg: .ascii "Hello, "
	name: .fill 20,1,0x20
	.byte '$,'\n
	.equ msg_size,.-msg
.text
_start:
immtoreg32:
	ldr r0,=0x676e6154
	ldr r1,=name
reg32tomem:
	str r0,[r1]
	disp
	ldr r0,=b32
	ldr r1,=name
memtoreg32:
	ldr r2,[r0]
	str r2,[r1]
	disp
exit:
	mov r0,#0
	mov r7,#1
	swi #0
