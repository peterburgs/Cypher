section .bss

extern write_char
extern write_hex
section .text

global hex_mem_line


hex_mem_line: 

	push	ebp
	mov 	ebp, esp
	mov 	esi, [ebp + 8]
	mov		ecx, [ebp + 12]
print_out_line:
	mov 	al, byte[esi]
	call	write_hex
	inc		esi
	loop	print_out_line
	
_exit:
	mov	eax,1
	int 	0x80
