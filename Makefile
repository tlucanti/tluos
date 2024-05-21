
CC = riscv64-linux-gnu-gcc
LD = riscv64-linux-gnu-ld

CFLAGS = -Wall -Wextra
CFLAGS += -nostdlib
LDFLAGS =

CFLAGS += -I include

NAME = kernel.img

obj =

obj += kernel/entry.o
obj += kernel/start_kernel.o

$(NAME): $(obj)
	$(LD) $(LDFLAGS) -T link.lds -o $(NAME) $(obj)

qemu: $(NAME)
	qemu-system-riscv64 -nographic -machine virt -bios none -kernel $(NAME)

clean:
	rm -f $(obj)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.S
	$(CC) $(CFLAGS) -c $< -o $@

