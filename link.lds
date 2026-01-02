
SECTIONS {

	. = 0x80000000;

	.text : {
		*(.text)

		. = ALIGN(8);
		PROVIDE(END_OF_KERNEL_TEXT = .);
	}
}

