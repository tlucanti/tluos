
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

#ifndef likely
# define likely(expr) __builtin_expect(!!(expr), 1)
#endif

#ifndef unlikely
# define unlikely(expr) __builtin_expect(!!(expr), 0)
#endif

#ifndef unreachable
# define unreachable() __builtin_unreachable()
#endif

#endif /* KERNEL_ATTRIBUTES_H */

