#set confirm off
#set architecture riscv:rv64
#target remote :1234
#symbol-file kernel.img
#set disassemble-next-line auto
#set riscv use-compressed-breakpoints yes
