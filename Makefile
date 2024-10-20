all: minios.bin

minios.bin: clean
	nasm -f bin src/boot/boot.asm -o minios.bin

clean:
	-rm minios.bin