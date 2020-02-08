#ifndef __DS_DYNAMIC_MATRIX_H__
#define __DS_DYNAMIC_MATRIX_H__

/*
CDIO headers and matrix_t definition.
*/

#include <inttypes.h>

typedef struct
{
    int64_t **matrix;
    int64_t rows;
    int64_t columns;
} matrix_t;

typedef matrix_t *const cp_matrix_t;
typedef const matrix_t *const cvcp_matrix_t;

typedef const int64_t *const cvcp_int64_t;
typedef int64_t *const cp_int64_t;
typedef const int64_t cv_int64_t;

int create_matrix(cp_matrix_t matrix);

int delete_matrix(cp_matrix_t matrix);

int input_matrix(cp_matrix_t matrix);

int output_matrix(cvcp_matrix_t matrix);

#endif