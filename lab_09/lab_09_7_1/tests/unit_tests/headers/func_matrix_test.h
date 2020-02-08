#ifndef __FUNC_MATRIX_TEST_H__
#define __FUNC_MATRIX_TEST_H__

/*
Matrix handling utilities tests headers.
*/

#include "../../../headers/ds_dynamic_matrix.h"

void fill_matrix(cp_matrix_t matrix, const int ascending);

void fill_unit_matrix(cp_matrix_t matrix);

void test_delete_decision();

void test_find_min();

void test_delete_row();

void test_delete_column();

void test_col_geommean();

void test_create_geommean_row();

void test_row_max();

void test_create_max_col();

void test_matrix_copy();

void test_matrix_mult();

#endif
