
SECTIONS {

	. = 0x80000000;

	.all : {
		*(.text.init)
		*(.*)
	}
}

