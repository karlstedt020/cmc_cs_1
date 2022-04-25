.PHONY: all clean

all: program

clean:
	rm -rf program *.o

functions.o: functions.asm
	nasm -f elf32 -o functions.o functions.asm
    
root.o: root.c
	gcc -std=c99 -c -o root.o root.c -m32

program: root.o functions.o
	gcc -o program root.o functions.o -m32
