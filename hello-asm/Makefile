
all:
	riscv64-linux-gnu-gcc -O2 -c hello.S
	riscv64-linux-gnu-ld -O2 -T link.lds -o hello hello.o
	qemu-system-riscv64 -nographic -machine virt -bios none -kernel hello

clean:
	rm hello.o hello

