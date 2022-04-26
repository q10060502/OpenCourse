.text
.global _start
_start:
	mov $0x00,%bh
	mov $0x03,%ah
	int $0x10
	#xor %dx,%dx
	#mov $0x00,%bh
	mov $0x02,%bl
	mov $msg, %ebp
	add $0x7c00,%ebp
	mov $0x0a, %cx
	mov $0x01, %al
	mov $0x13, %ah
	int $0x10
loop:
	jmp loop
msg:
	.string "Hello ASM!"
.org 0x200-2
	.byte 0x55,0xaa
	
