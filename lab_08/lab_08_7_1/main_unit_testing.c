#include <stdio.h>

#include "headers/ds_dynamic_array.h"
#include "headers/func_array.h"
#include "headers/func_io.h"
#include "headers/func_math.h"

#include "tests/unit_tests/headers/ds_dynamic_array_test.h"
#include "tests/unit_tests/headers/func_array_test.h"
#include "tests/unit_tests/headers/func_io_test.h"
#include "tests/unit_tests/headers/func_math_test.h"

#define OK 0

int main()
{
    printf("%s", "ds_dynamic_array tests:\n");
    test_create_dynamic_array();
    test_delete_dynamic_array();
    test_input_dynamic_array();
    test_output_dynamic_array();

    printf("%s", "func_io tests:\n");
    test_input_positive_int();
    test_input_non_negative_int();

    printf("%s", "func_math tests:\n");
    test_find_cubic_mean();
    test_find_array_minimum();

    printf("%s", "func_array tests:\n");
    test_find_min_diff();
    test_move_array_elements();
    test_remap_array();
    test_change_array_len();
    test_insert_to_array();
    test_check_pos_num();

    return OK;
}