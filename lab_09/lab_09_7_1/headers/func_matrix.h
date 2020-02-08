#ifndef __FUNC_MATRIX_H__
#define __FUNC_MATRIX_H__

/*
Matrix handling utilities' headers.
*/

#include "ds_dynamic_matrix.h"

int delete_decision(cvcp_matrix_t matrix);

int find_min(cvcp_matrix_t matrix, cp_int64_t row_min, cp_int64_t column_min);

int delete_row(cp_matrix_t matrix, cp_int64_t remove);

int delete_column(cp_matrix_t matrix, cp_int64_t remove);

int delete_square(cp_matrix_t matrix);

int64_t col_geommean(cvcp_matrix_t matrix, cv_int64_t col);

int create_geommean_row(cp_matrix_t matrix);

int64_t row_max(cvcp_matrix_t matrix, cv_int64_t row);

int create_max_col(cp_matrix_t matrix);

int expand_square(cp_matrix_t matrix_a, cp_matrix_t matrix_b);

int square_matrix(cp_matrix_t matrix_a, cp_matrix_t matrix_b);

int matrix_copy(cp_matrix_t from, cp_matrix_t to);

int matrix_mult(cp_matrix_t matrix_a, cp_matrix_t matrix_b, cp_matrix_t matrix_r);

int matrix_pow(cp_matrix_t matrix, cp_int64_t power);

#endif
