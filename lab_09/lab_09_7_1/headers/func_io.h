#ifndef __FUNC_IO_H__
#define __FUNC_IO_H__

/*
IO utilities' headers.
*/

#include <inttypes.h>

int input_positive(cp_int64_t num_to_be_entered);

int input_nonnegative(cp_int64_t num_to_be_entered);

int input_params(cp_matrix_t matrix);

#endif
