.text
.global _start
_start:
	B vt_init
	B vt_default
	B vt_default
	B vt_default
	B vt_default
	B vt_default
	B vt_default
vt_init:
	ldr %r1,='x'
loop:
	nop
	B loop
vt_default:
	B .
