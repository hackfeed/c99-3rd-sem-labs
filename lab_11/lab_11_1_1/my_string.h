#ifndef __MY_STRING_H__
#define __MY_STRING_H__

#define BUFSIZE 255

#include <inttypes.h>

char *dtox(uint64_t num);

int my_snprintf(char *str, size_t size, const char *format, ...);

#endif