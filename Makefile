
CC = riscv64-linux-gnu-gcc
LD = riscv64-linux-gnu-ld

CFLAGS = -Wall -Wextra
CFLAGS += -nostdlib
LDFLAGS =

CFLAGS += -I include

NAME = kernel.img

obj =

all:
	$(CC) $(CFLAGS) -c kernel/entry.S -o kernel/entry.o
	$(LD) $(LDFLAGS) -T link.lds -o $(NAME) kernel/entry.o

qemu: all
	qemu-system-riscv64 -nographic -machine virt -bios none -kernel $(NAME)

