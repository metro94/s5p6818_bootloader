#ifndef __DEBUG_H__
#define __DEBUG_H__

#ifdef DEBUG
extern int printf(const char *format, ...);
#define debug(level, format, ...)	printf(level format, ##__VA_ARGS__)
#else
#define debug(level, format, ...)
#endif /* DEBUG */

#define DEBUG_LEVEL_INFO	"[INFO]"
#define DEBUG_LEVEL_WARN	"[WARN]"
#define DEBUG_LEVEL_ERR		"[ERR ]"

#endif /* __DEBUG_H__ */

