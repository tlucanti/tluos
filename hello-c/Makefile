
all:
	riscv64-linux-gnu-gcc -O2 -c head.S
	riscv64-linux-gnu-gcc -O2 -c main.c
	riscv64-linux-gnu-ld -O2 -T link.lds -o kernel head.o main.o
	qemu-system-riscv64 -nographic -machine virt -bios none -kernel kernel

clean:
	rm head.o main.o kernel

