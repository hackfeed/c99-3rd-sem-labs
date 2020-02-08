#include <stdio.h>

#include "headers/ds_dynamic_matrix.h"
#include "headers/func_matrix.h"
#include "headers/func_io.h"
#include "headers/defines.h"

#include "tests/unit_tests/headers/ds_dynamic_matrix_test.h"
#include "tests/unit_tests/headers/func_matrix_test.h"
#include "tests/unit_tests/headers/func_io_test.h"

int main()
{
    printf("%s", "\nDS_DYNAMIC_MATRIX TESTS:\n");
    test_create_matrix();
    test_delete_matrix();
    test_input_matrix();
    test_output_matrix();

    printf("%s", "\nFUNC_IO TESTS:\n");
    test_input_positive();
    test_input_nonnegative();

    printf("%s", "\nFUNC_MATRIX TESTS:\n");
    test_delete_decision();
    test_find_min();
    test_delete_row();
    test_delete_column();
    test_col_geommean();
    test_create_geommean_row();
    test_row_max();
    test_create_max_col();
    test_matrix_copy();
    test_matrix_mult();

    return OK;
}