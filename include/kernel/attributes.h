
#ifndef KERNEL_ATTRIBUTES_H
#define KERNEL_ATTRIBUTES_H

#ifndef __always_inline
# define __always_inline inline __attribute__((__always_inline__))
#endif

#ifndef __maybe_unused
# define __maybe_unused __attribute__((__unused__))
#endif

#ifndef __aligned
# define __aligned(x) __attribute__((__aligned__(x)))
#endif

#ifndef __noreturn
# define __noreturn __attribute__((__noreturn__))
#endif

#ifndef __printf
# define __printf(a, b) __attribute__((__format__(__printf__, a, b)))
#endif

#ifndef likely
# define likely(expr) __builtin_expect(!!(expr), 1)
#endif

#ifndef unlikely
# define unlikely(expr) __builtin_expect(!!(expr), 0)
#endif

#ifndef unreachable
# define unreachable() __builtin_unreachable()
#endif

typedef __builtin_va_list va_list;

#ifndef va_start
# define va_start(list, arg) __builtin_va_start(list, arg)
#endif

#ifndef va_end
# define va_end(list) __builtin_va_end(list)
#endif

#ifndef va_arg
# define va_arg(list, type) __builtin_va_arg(list, type)
#endif

#ifndef va_copy
#define va_copy(dst, src) __builtin_va_copy(dst, src)
#endif

#endif /* KERNEL_ATTRIBUTES_H */

