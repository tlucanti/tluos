
CC   ?= riscv64-unknown-elf-gcc
LD   ?= riscv64-unknown-elf-ld
GDB  ?= riscv64-unknown-elf-gdb
QEMU ?= qemu-system-riscv64

CFLAGS  += -Wall -Wextra
CFLAGS  += -O0 -g3
CFLAGS  += -nostdlib
CFLAGS  += -I include
CFLAGS  += -mcmodel=medany

LDFLAGS +=

NAME = kernel.img

obj =

obj += kernel/entry.o
obj += kernel/start_kernel.o
obj += kernel/uart.o
obj += kernel/kconsole.o

$(NAME): $(obj)
	$(LD) $(LDFLAGS) -T link.ld -o $(NAME) $(obj)

qemu: $(NAME)
	$(QEMU) -nographic -machine virt -bios none -kernel $(NAME) -d guest_errors

qemu-gdb: $(NAME)
	$(QEMU) -nographic -machine virt -bios none -kernel $(NAME) -d int,guest_errors -s -S

gdb:
	$(GDB)

clean:
	rm -f $(obj) $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.S
	$(CC) $(CFLAGS) -c $< -o $@

