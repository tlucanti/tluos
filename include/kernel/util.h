
#ifndef KERNEL_UTIL_H
#define KERNEL_UTIL_H

#define __cmp_once(op, a, b)           \
	({                             \
		typeof(a) __a = (a);   \
		typeof(b) __b = (b);   \
		__a op __b ? __a : __b;\
	})

#define is_same(a, b) __builtin_types_compatible_p(typeof(a), typeof(b))

#define min(a, b) __cmp_once(>, a, b)
#define max(a, b) __cmp_once(<, a, b)

#define container_of(ptr, type, member)                                 \
	({                                                              \
		static_assert(is_same(*ptr, ((type *)0UL)->member) ||   \
			      is_same(*ptr, void),                      \
			      "pointer type mismatch in container_of"); \
		(type *)((void *)ptr - offsetof(type, member))          \
	})

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

#ifndef static_assert
# define static_assert _Static_assert
#endif


#endif /* KERNEL_UTIL_H */

