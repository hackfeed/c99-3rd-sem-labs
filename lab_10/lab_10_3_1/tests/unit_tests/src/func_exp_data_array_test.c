#include <stdio.h>

#include "headers/ds_exp_data_array.h"
#include "headers/func_exp_data_array.h"
#include "headers/defines.h"

void test_filter_data_fullwipe()
{
    int err_cnt = 0;

    exparr_t exps;
    create_array(&exps);

    if (filter_data(&exps) != FULL_WIPE_ERROR)
    {
        err_cnt++;
    }
    delete_array(&exps, exps.cursize);

    printf("%s: %s\n", __func__, err_cnt ? "FAILED" : "OK");
}

void test_filter_data_ok()
{
    int err_cnt = 0;

    exparr_t exps;
    create_array(&exps);

    freopen("./tests/unit_tests/positive_input_02.txt", "r", stdin);
    input_array(&exps, stdin);

    if (filter_data(&exps) != OK)
    {
        err_cnt++;
    }
    
    if (exps.cursize != 5)
    {
        err_cnt++;
    }
    delete_array(&exps, exps.cursize);

    printf("%s: %s\n", __func__, err_cnt ? "FAILED" : "OK");
}

void test_filter_data()
{
    test_filter_data_fullwipe();
    test_filter_data_ok();
}

void test_mean_data_ok()
{
    int err_cnt = 0;

    exparr_t exps;
    create_array(&exps);

    freopen("./tests/unit_tests/positive_input_03.txt", "r", stdin);
    input_array(&exps, stdin);

    if (mean_data(&exps) != OK)
    {
        err_cnt++;
    }
    
    if (exps.exparr->count != 1 && *(exps.exparr)->data - 3 < EPS)
    {
        err_cnt++;
    }
    delete_array(&exps, exps.cursize);

    printf("%s: %s\n", __func__, err_cnt ? "FAILED" : "OK");
}

void test_mean_data()
{
    test_mean_data_ok();
}