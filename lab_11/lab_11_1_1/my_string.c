#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <inttypes.h>

#include "my_string.h"

/*
Transform decimal number to hexadecimal number.

Input data:
* uint64_t num - number to be transformed.

Output data:
* char *hex - string representing transformed number in hexadecimal.
*/
char *dtox(uint64_t num)
{
    char *alphabet = "0123456789abcdef";
    char *hex = (char *)malloc(BUFSIZE * sizeof(char));
    int hex_len = 0;

    if (num == 0)
    {
        hex[hex_len++] = alphabet[0];
        hex[hex_len] = '\0';

        return hex;    
    }

    while (num > 0)
    {
        hex[hex_len] = alphabet[num % 16];
        num /= 16;
        hex_len++;
    }
    hex[hex_len] = '\0';

    int i = 0, len = hex_len / 2;
    while (len)
    {
        char tmp = hex[i];
        hex[i] = hex[hex_len - 1];
        hex[hex_len - 1] = tmp;

        hex_len--;
        len--;
        i++;
    }

    return hex;
}

/*
snprintf function realization for s, c, x, lx, llx specifiers.

Read more here: https://linux.die.net/man/3/snprintf
*/
int my_snprintf(char *str, size_t size, const char *format, ...)
{
    va_list args;
    va_start(args, format);
    size_t cur_size = 0;

    while (*format)
    {
        if (*format != '%')
        {
            if (str && size && cur_size < size)
            {
                str[cur_size] = *format++;
            }
            else
            {
                format++;
            }
            cur_size++;
        }
        else
        {
            if (*(format + 1) == 's')
            {
                char *s = va_arg(args, char *);
                
                while (*s)
                {
                    if (str && size && cur_size < size)
                    {
                        str[cur_size] = *s;
                    }
                    cur_size++;
                    s++;
                }
                format += 2;
                continue;
            }

            if (*(format + 1) == 'c')
            {
                char c = va_arg(args, int);

                if (str && size && cur_size < size)
                {
                    str[cur_size] = c;
                }
                cur_size++;
                format += 2;
                continue;
            }
            
            if (*(format + 1) == 'l' && *(format + 2) == 'l' && *(format + 3) == 'x')
            {
                uint64_t x = va_arg(args, uint64_t);
                char *hex = dtox(x);

                int i = 0;
                while (hex[i])
                {
                    if (str && size && cur_size < size)
                    {
                        str[cur_size] = hex[i];
                    }
                    cur_size++;
                    i++;
                }
                free(hex);
                format += 4;
                continue;
            }
            
            if (*(format + 1) == 'l' && *(format + 2) == 'x')
            {
                uint64_t x = va_arg(args, uint64_t);
                char *hex = dtox(x);

                int i = 0;
                while (hex[i])
                {
                    if (str && size && cur_size < size)
                    {
                        str[cur_size] = hex[i];
                    }
                    cur_size++;
                    i++;
                }
                free(hex);
                format += 3;
                continue;
            }
            
            if (*(format + 1) == 'x')
            {
                uint32_t x = va_arg(args, uint32_t);
                char *hex = dtox(x);

                int i = 0;
                while (hex[i])
                {
                    if (str && size && cur_size < size)
                    {
                        str[cur_size] = hex[i];
                    }
                    cur_size++;
                    i++;
                }
                free(hex);
                format += 2;
                continue;
            }
        }
    }

    va_end(args);

    if (str && size)
    {
        if (cur_size < size)
        {
            str[cur_size] = '\0';
        }
        else
        {
            str[size - 1] = '\0';
        }
    }

    return cur_size;
}
