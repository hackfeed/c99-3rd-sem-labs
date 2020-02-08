#ifndef __DS_EXP_DATA_ARRAY_H__
#define __DS_EXP_DATA_ARRAY_H__

/*
CDIO headers.
*/

#include <stdio.h>

#include "defines.h"
#include "typedefs.h"

int create_array(exparr_t *const exparr);

int delete_array(exparr_t *const exparr, const int to_rec);

int expand_array(exparr_t *exparr, const int curexp);

int input_array(exparr_t *const exparr, FILE *const stream);

int output_array(const exparr_t *const exparr, FILE *const stream);

#endif