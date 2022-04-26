.text
.global _start
_start:
	mov $0x00,%bh
	mov $0x00,%bl
	mov $'x,%al
	mov $0x0e,%ah
	int $0x10
loop:
	jmp loop
msg:
	.string "Hello ASM!"
.org 0x200-2
	.byte 0x55,0xaa
	
