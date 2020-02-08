#ifndef __DS_EXP_DATA_H__
#define __DS_EXP_DATA_H__

/*
CDIO headers.
*/

#include <stdio.h>

#include "defines.h"
#include "typedefs.h"

int create_data(exp_t *const exp, const bufexp_t *const buf);

int delete_data(exp_t *const exp);

int input_data(exp_t *const exp, const bufexp_t *const buf, FILE *const stream);

int output_data(const exp_t *const exp, FILE *const stream);

#endif