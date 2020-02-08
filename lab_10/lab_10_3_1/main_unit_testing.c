#include <stdio.h>

#include "headers/defines.h"

#include "tests/unit_tests/headers/ds_exp_data_test.h"
#include "tests/unit_tests/headers/func_exp_data_array_test.h"
#include "tests/unit_tests/headers/func_validation_test.h"
#include "tests/unit_tests/headers/func_comparators_test.h"

int main()
{
    printf("%s", "\nDS_EXPERIMENT_DATA TESTS:\n");
    test_create_data();
    test_delete_data();
    test_input_data();
    test_output_data();

    printf("%s", "\nFUNC_EXPERIMENT_DATA_ARRAY TESTS:\n");
    test_filter_data();
    test_mean_data();

    printf("%s", "\nFUNC_VALIDATION TESTS:\n");
    test_validate_struct();
    test_parse_nums();
    test_validate_nums();
    test_is_alphas();

    printf("%s", "\nFUNC_COMPARATORS TESTS:\n");
    test_compare_date();
    test_compare_technician();
    test_compare_measure();

    return OK;
}