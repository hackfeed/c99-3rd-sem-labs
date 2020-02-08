#include <stdio.h>
#include <stdlib.h>

#include "../../../headers/func_io.h"

#define OK 0
#define NUM_INPUT_ERROR -5
#define NEGATIVE_INPUT_ERROR -6

void test_input_positive_int()
{
    int err_cnt = 0;

    /* Negative testing */

    int entered_num;

    freopen("../negative_input_02.txt", "r", stdin);
    if (input_positive_int(&entered_num) != NUM_INPUT_ERROR)
    {
        err_cnt++;
    }

    freopen("../negative_input_03.txt", "r", stdin);
    if (input_positive_int(&entered_num) != NEGATIVE_INPUT_ERROR)
    {
        err_cnt++;
    }

    freopen("../negative_input_04.txt", "r", stdin);
    if (input_positive_int(&entered_num) != NEGATIVE_INPUT_ERROR)
    {
        err_cnt++;
    }

    /* Positive testing */

    freopen("../positive_input_02.txt", "r", stdin);
    if (input_positive_int(&entered_num) != OK)
    {
        err_cnt++;
    }

    printf("%s: %s\n", __func__, err_cnt ? "FAILED" : "OK");
}

void test_input_non_negative_int()
{
    int err_cnt = 0;

    /* Negative testing */

    int entered_num;

    freopen("../negative_input_02.txt", "r", stdin);
    if (input_non_negative_int(&entered_num) != NUM_INPUT_ERROR)
    {
        err_cnt++;
    }

    freopen("../negative_input_03.txt", "r", stdin);
    if (input_non_negative_int(&entered_num) != NEGATIVE_INPUT_ERROR)
    {
        err_cnt++;
    }

    /* Positive testing */

    freopen("../positive_input_02.txt", "r", stdin);
    if (input_non_negative_int(&entered_num) != OK)
    {
        err_cnt++;
    }

    freopen("../negative_input_04.txt", "r", stdin);
    if (input_non_negative_int(&entered_num) != OK)
    {
        err_cnt++;
    }

    printf("%s: %s\n", __func__, err_cnt ? "FAILED" : "OK");
}
