
#include <kernel/kprint.h>
#include <kernel/ktime.h>
#include <kernel/types.h>
#include <sys/console.h>

enum print_state {
	PRINT_NORMAL,
	PRINT_SPECIFIER,
	PRINT_8,
	PRINT_16,
	PRINT_64,
};

__printf(1, 0)
void klog(const char *format, ...)
{
	va_list args;
	uint64 t = ktime();

	kprint("[%lu.%lu]: ", t / (uint64)1e7, t % (uint64)1e7);

	va_start(args, format);
	kprintv(format, args);
	va_end(args);
	console_putc('\n');
}

__printf(1, 2)
uint kprint(const char *format, ...)
{
	va_list args;
	uint ret;

	va_start(args, format);
	ret = kprintv(format, args);
	va_end(args);
	return ret;
}

__printf(1, 0)
uint kprintv(const char *format, va_list args)
{
	uint printed = 0;
	enum print_state state = PRINT_NORMAL;

	while (*format != '\0') {
		if (*format == '%') {
			if (format[1] == '%') {
				/*
				 * if we want to print actual % we need to use
				 * %% in format string
				 */
				console_putc('%');
				format += 2;
				continue;
			}
			format++;
			state = PRINT_SPECIFIER;
		}

		if (state == PRINT_NORMAL) {
			console_putc(*format);
			printed++;
			format++;
			continue;
		}

		switch (*format) {
		case 'l':
			state = PRINT_64;
			break;
		case 'h':
			if (state == PRINT_SPECIFIER)
				state = PRINT_16;
			else if (state == PRINT_16)
				state = PRINT_8;
			break;
		case 'i':
		case 'd':
			if (state == PRINT_SPECIFIER)
				printed += console_putint(va_arg(args, int32));
			else if (state == PRINT_8)
				printed += console_putint((int8)va_arg(args, int32));
			else if (state == PRINT_16)
				printed += console_putint((int16)va_arg(args, int32));
			else if (state == PRINT_64)
				printed += console_putint(va_arg(args, int64));
			state = PRINT_NORMAL;
			break;

		case 'u':
			if (state == PRINT_SPECIFIER)
				printed += console_putuint(va_arg(args, uint32));
			else if (state == PRINT_8)
				printed += console_putuint((uint8)va_arg(args, uint32));
			else if (state == PRINT_16)
				printed += console_putuint((uint16)va_arg(args, uint32));
			else if (state == PRINT_64)
				printed += console_putuint(va_arg(args, uint64));
			state = PRINT_NORMAL;
			break;

		case 's':
			printed += console_puts(va_arg(args, const char *));
			break;
		case 'c':
			printed += console_putc((char)va_arg(args, int32));
			break;
		}

		format++;
	}

	return printed;
}
