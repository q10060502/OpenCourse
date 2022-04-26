all: 
	as --64 -g -o 101.o 101.s
	ld -m elf_x86_64 -o 101.out 101.o
	as --32 -g -o 101_i386.o 101_i386.s
	ld -m elf_i386 -o 101_i386.out 101_i386.o

clean:
	rm -rf *.out
	rm -rf *.o


