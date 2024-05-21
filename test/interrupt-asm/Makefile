
all:
	riscv64-linux-gnu-gcc -O2 -c int.S
	riscv64-linux-gnu-ld -O2 -T link.lds -o kernel int.o
	qemu-system-riscv64 -nographic -machine virt -bios none -kernel kernel

clean:
	rm int.o kernel

