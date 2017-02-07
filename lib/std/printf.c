#include <ctype.h>
#include <string.h>
#include <stdarg.h>
#include <printf.h>

static int (*__putchar_used_in_printf)(int);

int printf(const char *format, ...)
{
	int ret;
	va_list va;
	
	va_start(va, format);
	ret = vsprintf(format, va);
	va_end(va);
	
	return ret;
}

int vsprintf(const char *format, va_list va)
{
	int			ret = 0;
	int			num_width;
	char			ch;
	union __number_union	num;
	char			buf[20];
	struct __printf_params	params;
	
	while ((ch = *format++)) {
		if (ch == '%') {
			params.leading_zero	= 0;
			params.alter		= 0;
			params.upper_case	= 0;
			params.left_aligned	= 0;
			params.prefix		= '\0';
			params.width		= 0;
			params.base		= 0;
			params.buf		= buf;
			num_width		= 0;
			
			while ((ch = *format++)) {
				switch (ch) {
				case '0':
					params.leading_zero = 1;
					continue;
				case '#':
					params.alter = 1;
					continue;
				case '+':
					// Uses default '+' sign
					params.prefix = '+';
					continue;
				case '-':
					params.left_aligned = 1;
					continue;
				default:
					break;
				}
				break;
			}
			
			if (!ch)
				break;
			
			while (isdigit(ch)) {
				params.width = params.width * 10 + (ch - '0');
				ch = *format++;
			}
			
			if (!ch)
				break;
			
			if (ch == 'l') {
				++num_width;
				ch = *format++;
				if (ch == 'l') {
					++num_width;
					ch = *format++;
				}
			}
			
			if (!ch)
				break;
			
			switch (ch) {
			case 'd':
			case 'i':
			case 'u':
				if (ch == 'u') {
					switch (num_width) {
					case 0:
						num.ull = va_arg(va, unsigned int);
						break;
					case 1:
						num.ull = va_arg(va, unsigned long);
						break;
					case 2:
						num.ull = va_arg(va, unsigned long long);
						break;
					default:
						break;
					}
				} else {
					switch (num_width) {
					case 0:
						num.sll = va_arg(va, int);
						break;
					case 1:
						num.sll = va_arg(va, long);
						break;
					case 2:
						num.sll = va_arg(va, long long);
					default:
						break;
					}
					if (num.sll < 0) {
						num.ull = -num.sll;
						params.prefix = '-';
					}
				}
				params.base = 10;
				__ull_to_str(&params, num.ull);
				__put_with_params(&params);
				++ret;
				break;
			
			case 'p':
				params.alter = 1;
				params.leading_zero = 1;
				params.width = 18;
				num_width = 2;
			case 'x':
			case 'X':
				switch (num_width) {
				case 0:
					num.ull = va_arg(va, unsigned int);
					break;
				case 1:
					num.ull = va_arg(va, unsigned long);
					break;
				case 2:
					num.ull = va_arg(va, unsigned long long);
					break;
				default:
					break;
				}
				params.upper_case = (ch == 'X') ? 1 : 0;
				params.base = 16;
				if (params.alter)
					params.prefix = (params.upper_case) ? 'X' : 'x';
				__ull_to_str(&params, num.ull);
				__put_with_params(&params);
				++ret;
				break;
			
			case 'c':
				buf[0] = va_arg(va, int);
				buf[1] = '\0';
				__put_with_params(&params);
				++ret;
				break;
			case 's':
				params.buf = va_arg(va, char *);
				__put_with_params(&params);
				++ret;
				break;
			case '%':
				__putchar_used_in_printf('%');
			default:
				break;
			}
		} else {
			if (ch == '\n')
				__putchar_used_in_printf('\r');
			__putchar_used_in_printf(ch);
		}
	}
	
	return ret;
}

void register_putchar_used_in_printf(int (*putchar)(int))
{
	__putchar_used_in_printf = putchar;
}

void __put_with_params(struct __printf_params *params)
{
	int rest, i;
	unsigned int str_len;
	
	str_len = strlen(params->buf);
	rest = (params->width > str_len) ? (params->width - str_len) : 0;
	
	if (params->alter)
		rest = rest ? (rest - 1) : 0;
	
	if (params->prefix)
		rest = rest ? (rest - 1) : 0;
	
	if (rest && !params->left_aligned && !params->leading_zero)
		for (i = rest; i > 0; --i)
			__putchar_used_in_printf(' ');
	
	if (params->alter)
		__putchar_used_in_printf('0');
	
	if (params->prefix)
		__putchar_used_in_printf(params->prefix);
	
	if (rest && !params->left_aligned && params->leading_zero)
		for (i = rest; i > 0; --i)
			__putchar_used_in_printf('0');
	
	while (*params->buf)
		__putchar_used_in_printf(*params->buf++);
		
	if (rest && params->left_aligned) {
		for (i = rest; i > 0; --i)
			__putchar_used_in_printf(' ');
	}
}

void __ull_to_str(struct __printf_params *params, unsigned long long num)
{
	unsigned long long tmp;
	int digit;
	char *cur_pos;
	
	cur_pos = params->buf;
	tmp = num;
	do {
		tmp /= params->base;
		++cur_pos;
	} while (tmp > 0);
	
	tmp = num;
	*cur_pos = '\0';
	do {
		--cur_pos;
		digit = tmp % params->base;
		if (digit < 10)
			*cur_pos = '0' + digit;
		else
			*cur_pos = (params->upper_case ? 'A' : 'a') + digit - 10;
		tmp /= params->base;
	} while (tmp > 0);
}

