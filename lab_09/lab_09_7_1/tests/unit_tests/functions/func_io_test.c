#include <stdio.h>
#include <inttypes.h>

#include "../../../headers/ds_dynamic_matrix.h"
#include "../../../headers/func_io.h"
#include "../../../headers/defines.h"

void test_input_positive_alphain()
{
    int err_cnt = 0;

    /* Negative testing */

    int64_t entered_num;

    freopen("./tests/unit_tests/negative_input_02.txt", "r", stdin);
    if (input_positive(&entered_num) != NUM_INPUT_ERROR)
    {
        err_cnt++;
    }

    printf("%s: %s\n", __func__, err_cnt ? "FAILED" : "OK");
}

void test_input_positive_nonposin()
{
    int err_cnt = 0;

    /* Negative testing */

    int64_t entered_num;

    freopen("./tests/unit_tests/negative_input_03.txt", "r", stdin);
    if (input_positive(&entered_num) != NEGATIVE_INPUT_ERROR)
    {
        err_cnt++;
    }

    freopen("./tests/unit_tests/negative_input_04.txt", "r", stdin);
    if (input_positive(&entered_num) != NEGATIVE_INPUT_ERROR)
    {
        err_cnt++;
    }

    printf("%s: %s\n", __func__, err_cnt ? "FAILED" : "OK");
}

void test_input_positive_normal()
{
    int err_cnt = 0;

    /* Positive testing */

    int64_t entered_num;

    freopen("./tests/unit_tests/positive_input_02.txt", "r", stdin);
    if (input_positive(&entered_num) != OK)
    {
        err_cnt++;
    }

    printf("%s: %s\n", __func__, err_cnt ? "FAILED" : "OK");
}

void test_input_positive()
{
    test_input_positive_alphain();
    test_input_positive_nonposin();
    test_input_positive_normal();
}

void test_input_nonnegative_alphain()
{
    int err_cnt = 0;

    /* Negative testing */

    int64_t entered_num;

    freopen("./tests/unit_tests/negative_input_02.txt", "r", stdin);
    if (input_nonnegative(&entered_num) != NUM_INPUT_ERROR)
    {
        err_cnt++;
    }

    printf("%s: %s\n", __func__, err_cnt ? "FAILED" : "OK");
}

void test_input_nonnegative_negin()
{
    int err_cnt = 0;

    /* Negative testing */

    int64_t entered_num;

    freopen("./tests/unit_tests/negative_input_03.txt", "r", stdin);
    if (input_nonnegative(&entered_num) != NEGATIVE_INPUT_ERROR)
    {
        err_cnt++;
    }

    printf("%s: %s\n", __func__, err_cnt ? "FAILED" : "OK");
}

void test_input_nonnegative_norml()
{
    int err_cnt = 0;

    int64_t entered_num;

    /* Positive testing */

    freopen("./tests/unit_tests/positive_input_02.txt", "r", stdin);
    if (input_nonnegative(&entered_num) != OK)
    {
        err_cnt++;
    }

    freopen("./tests/unit_tests/negative_input_04.txt", "r", stdin);
    if (input_nonnegative(&entered_num) != OK)
    {
        err_cnt++;
    }

    printf("%s: %s\n", __func__, err_cnt ? "FAILED" : "OK");
}

void test_input_nonnegative()
{
    test_input_nonnegative_alphain();
    test_input_nonnegative_negin();
    test_input_nonnegative_norml();
}
