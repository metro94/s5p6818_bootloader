#ifndef __STRING_H__
#define __STRING_H__

unsigned int strlen(const char *) __attribute__ ((noinline));
void * memcpy(void *, const void *, unsigned long long) __attribute__ ((noinline));
int strncmp(const char *, const char *, unsigned int) __attribute__ ((noinline));

#endif

