.text
.intel_syntax noprefix
.global _start
_start:
	mov bh,0x00
	mov ah,0x03
	int 0x10
	#xor dx,dx
	#mov bh,0x00
	mov bl,0x02
	mov ebp,offset msg
	add ebp,0x00007c00
	mov cx,0x0a
	mov al,0x01
	mov ah,0x13
	int 0x10
loop:
	jmp loop
msg:
	.string "Hello ASM!"
.org 0x200-2
	.byte 0x55,0xaa
	
