%macro	write_str 2
	push	eax
	push	ebx
	push	ecx
	push	edx
	mov	edx,%2
	mov	ecx,%1
	mov	ebx,1
	mov	eax,4
	int	0x80
	pop	edx
	pop	ecx
	pop	ebx
	pop	eax
%endmacro

section .data
   hex_char	db	'0123456789ABCDEF'
   binMem times 8 db 0x30	;Memory to store binary string
   cMem	times 80 db	0
section	.text
	global	write_hex
	global	space
	global	newline
	global  write_char
	global  write_bin
space:
	mov	byte[cMem],32
	write_str cMem,1
	ret
newline:
	mov	byte[cMem],10
	write_str cMem,1
	ret
write_char:
	;input al
	mov	byte[cMem],al
	write_str cMem,1
  	ret
write_hex_digit:
	;input al
	push	ebx
	mov		ebx,hex_char
	xlat
	call 	write_char 
	pop		ebx
	ret
write_hex:
	;input  al
	push	ecx
	push	edx
	mov		dl,al
	mov		cl,4
	shr		al,cl
	call	write_hex_digit
	mov		al,dl
	and 	al,0x0f
	call	write_hex_digit
	pop		edx
	pop		ecx
	ret
	
write_bin:
	;input al
        push    ecx
        push    esi
        push    edi
        push    edx

        push    eax
        ;reset binMem to '0'
        mov     al,0x30
        mov     ecx,8
        mov     edi,binMem
        cld
        rep     stosb
        pop     eax
_st_writebin:
	mov	ecx,7
	mov	esi,binMem
_bin_disp_loop:
	mov	dl,al
	shr	dl,cl
	test	dl,1
	jz	dl_zero
	inc	byte[esi]
dl_zero:
	inc	esi
	loop	_bin_disp_loop

	write_str  binMem,8
	pop	edx
	pop	esi
	pop	ecx
	ret
