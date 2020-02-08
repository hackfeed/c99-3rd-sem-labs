#include <stdio.h>

#include "headers/func_comparators.h"
#include "headers/defines.h"

void test_compare_date_ok()
{
    int err_cnt = 0;

    exp_t exp_0 = { .date = "04.03.2000" };
    exp_t exp_1 = { .date = "06.11.2000" };

    if (compare_date(&exp_0, &exp_1) == TRUE)
    {
        err_cnt++;
    }

    printf("%s: %s\n", __func__, err_cnt ? "FAILED" : "OK");
}

void test_compare_date()
{
    test_compare_date_ok();
}

void test_compare_technician_ok()
{
    int err_cnt = 0;

    exp_t exp_0 = { .technician = "Kononenko" };
    exp_t exp_1 = { .technician = "Romanov" };

    if (compare_technician(&exp_0, &exp_1) == TRUE)
    {
        err_cnt++;
    }

    printf("%s: %s\n", __func__, err_cnt ? "FAILED" : "OK");
}

void test_compare_technician()
{
    test_compare_technician_ok();
}

void test_compare_measure_ok()
{
    int err_cnt = 0;

    double data_0[] = { 3 };
    double data_1[] = { 4 };

    exp_t exp_0 = { .data = data_0 };
    exp_t exp_1 = { .data = data_1 };

    if (compare_measure(&exp_0, &exp_1) == TRUE)
    {
        err_cnt++;
    }

    printf("%s: %s\n", __func__, err_cnt ? "FAILED" : "OK");
}

void test_compare_measure()
{
    test_compare_measure_ok();
}