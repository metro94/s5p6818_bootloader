#include <string.h>

void * memcpy(void *desc, const void *src, unsigned long long size)
{
	void *ret;
	
	ret = desc;
	while (size--)
		*((unsigned char *)desc++) = *((unsigned char *)src++);
	
	return ret;
}

unsigned int strlen(const char *str)
{
	unsigned int str_len = 0;
	
	while (*str++)
		++str_len;
	
	return str_len;
}

int strncmp(const char *x, const char *y, unsigned int len) {
	while (len--) {
		if (*x < *y)
			return -1;
		else if (*x > *y)
			return 1;
		else if (*x == 0 && *y == 0)
			return 0;
		++x;
		++y;
	}
	
	return 0;
}

