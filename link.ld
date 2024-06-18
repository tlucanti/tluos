
SECTIONS {

	. = 0x80000000;

	.text : {
		*(.text)
	}

	. = ALIGN(4096);
	heap_start = .;
}

