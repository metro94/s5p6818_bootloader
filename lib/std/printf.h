#ifndef __PRINTF_H__
#define __PRINTF_H__

#include <stdarg.h>

struct __printf_params {
	char		leading_zero:	1;
	char		alter:		1;
	char		upper_case:	1;
	char		left_aligned:	1;
	char		prefix;
	unsigned int	width;
	unsigned int	base;
	char *		buf;
};

union __number_union {
	unsigned long long	ull;
	long long		sll;
};

int printf(const char *, ...) __attribute__ ((format(printf, 1, 2)));
int vsprintf(const char *, va_list);
void register_putchar_used_in_printf(int (*putchar)(int));

void __put_with_params(struct __printf_params *) __attribute__ ((noinline));
void __ull_to_str(struct __printf_params *, unsigned long long) __attribute__ ((noinline));

#endif

