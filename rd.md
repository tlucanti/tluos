# HELLO KERNEL

## 1. kernel intro

Write `while (true)` baremetal program
in RISCV assembly.
Write linker script to place start of program to 0x800… addresss
Cross-compile script to object file using riscv compiler.
Link object file to riscv elf using cross-linker.
Run qemu with rv64 virt machine and Load compiled elf as kernel image to qemu a

## 2. hello kernel

Rewrite assembly program, so it set up stack pointer for C code, and transfer control to C code by calling C function from assembly.
Write C program, that write sequential bytes to UART address.
Use Makefile to compile multiple source files and link them together to single elf file.

# CONSOLE

## 3. uart

Write UART driver, based on UART16650 specification.
Write following UART interface:
 - `void uart_unit(void)`
   Initialize uart registers
 - `void uart_putc(chat c)`
   Asynchronously write single character
   to uart RX
 - `char uart_getc(void)`
  Asynchronously read single character from uart TX
 - `void uart_write_barrier(void)`
   Wait to uart write queue to flush
 - `void uart_wait_for_data(void)`
   Wait for data in uart read queue to appear

## 4. console

Write console interface functions:
 - `void console_init(void)`
   Function initializes UART
 - `void console_putc(char c)`
   Function puts single character to UART and waits it to be printed
 - `void console_puts(const char *s)`
   Function puts whole string to UART and waits it to be printed
 - `char console_getc()`
   Function waits for data in UART and gets single character from UART

Write simple echo program, that reads input from console,
and prints it back

# SUPERVISOR

## 5. supervisor

Write C wrappers for RISCV CSR access and modifications.
Transfer execution to s-mode:
 - set previous privilege level to S-mode in mstatus
 - set mepc to function, that will be executed in S-mode (main)
 - configure PMP region to cover whole address space with RWX permissions
 - jump to main function in S-mode with mret instruction

## 6. traps

Delegate all traps and interrupts from M-mode to S-mode
 - configure medeleg and mideleg registers

Write kernel trap and exception handlers.
 - write context switch asm procedure

# TIME

//  ## 6. clint
//
//  Write CLINT driver with following interface
//   - `void clint_init(void)`
//     function initializes CLINT device
//   - `uint64 clint_time_get(void)`
//     function returns current CPU time
//   - `void clint_timer_set(uint64 time)`
//     function set timer to provided point in CPU time

## 7. ktime

Enable sstc extension by configuring menvcfg csr
Enable stimecmp register by configuring mcounteren csr

Write kernel time interface functions
 - `void ktime_init(void)`
   function initializes kernel time system
 - `uint64 ktime_get(void)`
   function returns total time in nanoseconds since CPU boot
 - `void ktime_set_timer(uint64 ktime)`
   function set timer in ktime nanoseconds,
   and rewrites previous timer, if was set
 - `uint64 KTIME_TO_S(uint64 ktime)`
   macro gets number of whole seconds in ktime_get return
 - `uint64 KTIME_TO_NS(uint64 ktime)`
   macro gets number of nanoseconds since last second in ktime_get return

## 8. timer

Rewrite trap handler to print trap type
Write program that will fire timer every second and print a message to console

# MEMORY MANAGEMENT

## 9. allocator

Write basic slab single physical page allocator.
Allocator is based on free list or page occupancy bitmap.
Allocator interface:
 - `void allocator_init(void)`
   function initialize allocator free list or bitmap
 - `void *alloc_physical_page(void)`
   returns address of allocated physical page or `NULL` if out of memory.
 - `void free_physical_page(void *page)`
   marks page with address `page` as free.

## 10. paging

Enable RISCV sv39 virtual memory paging (MMU).
Allocate page table and map kernel text to one-to-one
virtual to physical address.
Move kernel code to S-mode, except early boot code before enabling MMU.

# USERMODE

## 11. userspace

Move kernel mapping to top of virtual address space.
Add userspace (U-mode) / kernelspace (S-mode) separation.
Add transition between privilege levels:
 - U-mode
   Contains userspace function. using syscalls transfer to S-mode
 - S-mode
   Contains kernelspace code, that handles userspace syscalls
 - M-mode
   Contains early code, that configure CPU (M-mode CSRs),
   handles kernelspace syscalls

## 12. syscalls

Write U-mode to S-mode syscalls with `ecall` instruction.
Add context switch procedure.
Add syscalls:
 - `uint64 hartid(void)`
   returns current hart `mhardid` value using syscall interface.
 - `uint64 uptime(void)`
   returns number of nanoseconds since boot time.
 - `void log(const char *s)`
   writes string to kernel console

# MULTITASKING

## 13. multi-tasking

Add ability to start several tasks in single CPU which executes in turns.
All tasks has the same (single) U-mode address space.
Add kernel task struct, that contains process / task context:
programm counter, register values, task id.
Write simple scheduler which swaps task after some time,
using scheduling algorithm, like Round Robin.
Add syscalls:
 - `int fork(void)`
   Starts new task and starts executing it from current PC position.
   returns 0 on original task, and positive task id on created task, or error.
 - `void exit(void)`
   Syscall terminates current task.

Also write userspace function, to check scheduler swaps in real time.
 - `void sleep(uint64 ticks)`
   That waits for some time, depending on value of `ticks`.
   It can be just empty loop with `ticks` number of iterations.

## 14. multi-processing

Add separate address space for each created task.
Copy whole page table with all pages to new created task,
except read-only, use original physical pages for them.

## 15. Copy on write

Modify task creating procedure, so do not copy all writable pages.
Writable pages in original and created task marked read-only and
references original physical page.
On write from original or new process - a writable copy created,
and original page becomes no longer read-only

# CONCURRENCY

## 16. synchronization

Write synchronization primitives
Spinlock:
 - `void spin_init(struct spinlock *spin)`
 - `void spin_lock(struct spinlock *spin)`
 - `void spin_unlock(struct spinlock *spin)`

## 17. smp

Add support to run OS on multi-core CPU
Use synchronization on shared kernel objects
Modify userspace scheduler to run userspace tasks on different CPUs

# FILE SYSTEM

## 18. file system

Write basic RAM based file system. Limit max file name length.
Add syscalls:
 - `int fstat(const char *fname, struct fstat *fs)`
   Read file statistics from file name to struct
   (type, name, total file size in bytes, inode of file,
   number of blocks in file)
 - `int fread(const char *fname, char *dst, uint size)`
   read `size` bytes from file to dst, return number of red bytes, or error.
 - `int fwrite(const char *fname, char *buf, uint size)`
   write `size` bytes from buf to file,
   return number of written bytes, or error.

## 19. directories

Add tree-like directory structure to file system.
Each directory can contain regular files and other directories.
Add syscalls:
 - `int mkdir(const char *dname)`
   Create empty directory at location `dname`
 - `int funlink(const char *fname)`
   Remove empty directory or regular file at position `fname`

Add support to directories to previous syscalls, file paths now should be
split by `/` character to follow directory hierarchy.
 - `fstat`
   Add support if `fstat` called on directory. for the number of blocks use
   number of entries in directory.
 - `fread`
   Add support of directories, write directory entries names in a sequence at
   `dst` pointer, but no more than `size` bytes total.

# USERSPACE

## exec

add exec system to start new process with binary from file system
 - `int exec(const char *fname)`

## utilities

Make userspace utilities to run using shell
 - cat
 - echo
 - init
 - kill
 - ls
 - mkidir
 - rm

## binaries

insert utility binaries to kernel image filesystem at root directory

## mmap

write system calls:
`int mmap(uint64 addr, uint8_t flags)`
`int munmap(uint64 addr)`

## malloc

write userspace malloc function

## shell

Write userspace shell, that reads commands from UART

-------------------------------------------------------------------------------

## async uart
## kernel slab, buddy, memcache allocator
## file descriptors
## semaphores, atomics, condvars
## devices, disks
## journal file system
## graphics
## window system

## filesystem in userspace as read-only memory-mapped tree. which cab be updated with syscalls by kernel



