
CC   ?= riscv64-unknown-elf-gcc
LD   ?= riscv64-unknown-elf-ld
QEMU ?= qemu-system-riscv64

CFLAGS  += -Wall -Wextra
CFLAGS  += -O0 -g3
CFLAGS  += -nostdlib
CFLAGS  += -I include
CFLAGS  += -mcmodel=medany

LDFLAGS +=

NAME = kernel.img

obj =

all:
	$(CC) $(CFLAGS) -c kernel/entry.S -o kernel/entry.o
	$(LD) $(LDFLAGS) -T link.ld -o $(NAME) kernel/entry.o

qemu: all
	$(QEMU) -nographic -machine virt -bios none -kernel $(NAME)

