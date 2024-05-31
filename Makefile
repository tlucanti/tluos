
CC = riscv64-linux-gnu-gcc
LD = riscv64-linux-gnu-ld
QEMU = qemu-system-riscv64

CFLAGS = -Wall -Wextra
CFLAGS += -O0 -ggdb
CFLAGS += -nostdlib
CFLAGS += -I include

LDFLAGS = -T link.ld

NAME = kernel.img

obj =

obj += kernel/entry.o
obj += kernel/riscv.o
obj += kernel/start_kernel.o

obj += kernel/uart.o
obj += kernel/console.o

$(NAME): $(obj)
	$(LD) $(LDFLAGS) -o $(NAME) $(obj)

qemu: $(NAME)
	$(QEMU) -nographic -machine virt -bios none -kernel $(NAME)

qemu-gdb: $(NAME)
	$(QEMU) -nographic -machine virt -bios none -kernel $(NAME) -S -gdb tcp::27000

.PHONY: qemu

clean:
	rm -f $(obj)
.PHONY: clean

%.o: %.c Makefile
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.S Makefile
	$(CC) $(CFLAGS) -c $< -o $@

