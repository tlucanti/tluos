
SECTIONS {

	. = 0x80000000;
	_image_start = .;

	.all : {
		*(.text.init)
		*(.text)
		*(.rodata)
		*(.data)
		*(.bss)
	}

	_image_end = .;
}

