section .data
	length		db	0
	keyIndex	db	0
	rotatingCount	db	0
section .bss
	resultArr	resb	255
section .text
	global decode
decode:
	push ebp
	mov ebp, esp
	; Note: avoid using ebx
	; ref: https://stackoverflow.com/questions/55773868/returning-a-value-in-x86-assembly-language

	; Get the length of the plain text
	mov eax, [ebp + 12]
	mov byte[length], al
	; word index
	xor esi, esi
	; key index
	xor edi, edi
_loop:
	; Get key value
	mov eax, [ebp + 16]
	mov cl, byte[eax + edi]
	; Modulo key value to 16
	xor eax, eax
	mov al, cl
	mov cl, 16
	div cl
	mov cl, ah
	; Get 16-bit plain text
_temp:
	mov eax, [ebp + 8] 
	mov dx, word[eax + esi]
	; Rotate left
	rol dx, cl
	; Copy value to new string
	mov byte[resultArr + esi], dh
	mov byte[resultArr + esi + 1], dl

	inc edi
	; Reset key index to 0 if it > 7
	cmp edi, 8
	jl _skip_the_reset
	xor edi, edi
_skip_the_reset:
	add esi, 2
	cmp esi, [length]
	jle _loop

	; Copy address of resultArr to eax
	mov eax, resultArr
_exit_func:
	leave
	ret


	
