
CC = riscv64-linux-gnu-gcc
LD = riscv64-linux-gnu-ld
QEMU = qemu-system-riscv64

CFLAGS = -Wall -Wextra
CFLAGS += -O0 -ggdb3
CFLAGS += -nostdlib -mcmodel=medany
CFLAGS += -I include

LDFLAGS = -T link.ld

NAME = kernel.img

obj =

obj += kernel/entry.o
obj += kernel/clint.o
obj += kernel/riscv.o
obj += kernel/start_kernel.o

obj += kernel/uart.o
obj += kernel/console.o

obj += kernel/kernelvec.o
obj += kernel/trap.o
obj += kernel/syscall.o
obj += kernel/task.o

obj += user/usys.o
obj += user/init.o

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
