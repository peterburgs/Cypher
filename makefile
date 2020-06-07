compile:
	nasm -g -f elf encode.asm
	nasm -g -f elf decode.asm
	gcc -m32 cipher.c encode.o -o cipher.o
	gcc -m32 decipher.c decode.o -o decipher.o

