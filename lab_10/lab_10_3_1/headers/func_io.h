#ifndef __FUNC_IO_H__
#define __FUNC_IO_H__

/*
IO utilities' headers.
*/

#include "typedefs.h"

int input_positive(int *const num, FILE *const stream);

int input_string(char *string, FILE *const stream);

int input_static_fields(bufexp_t *const bufexp, FILE *const stream);

#endif
