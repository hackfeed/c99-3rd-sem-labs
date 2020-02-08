#include <stdio.h>

#include "../../../headers/func_validation.h"
#include "../../../headers/defines.h"

void test_validate_struct_wrongin()
{
    int err_cnt = 0;

    char *date = "04.02.200";

    if (validate_struct(date) != DATE_LEN_ERROR)
    {
        err_cnt++;
    }

    char *date_1 = "a4.03.2000";

    if (validate_struct(date_1) != ALPHA_IN_DATE_ERROR)
    {
        err_cnt++;
    }

    char *date_2 = "040.3.2000";

    if (validate_struct(date_2) != MISSED_DOT_ERROR)
    {
        err_cnt++;
    }

    printf("%s: %s\n", __func__, err_cnt ? "FAILED" : "OK");
}

void test_validate_struct_ok()
{
    int err_cnt = 0;

    char *date = "04.03.2000";

    if (validate_struct(date) != OK)
    {
        err_cnt++;
    }

    printf("%s: %s\n", __func__, err_cnt ? "FAILED" : "OK");
}

void test_validate_struct()
{
    test_validate_struct_wrongin();
    test_validate_struct_ok();
}

void test_parse_nums_ok()
{
    int err_cnt = 0;

    char *date = "04.03.2000";
    int day, month, year;

    parse_nums(date, &day, &month, &year);

    if (day != 4 || month != 3 || year != 2000)
    {
        err_cnt++;
    }

    printf("%s: %s\n", __func__, err_cnt ? "FAILED" : "OK");
}

void test_parse_nums()
{
    test_parse_nums_ok();
}

void test_validate_nums_logicerrs()
{
    int err_cnt = 0;

    int day, month, year;

    day = -1;
    month = 0;
    year = 2000;

    if (validate_nums(day, month, year) != INVALID_MONTH_ERROR)
    {
        err_cnt++;
    }

    month = february;

    if (validate_nums(day, month, year) != INVALID_DAY_ERROR)
    {
        err_cnt++;
    }

    day = 31;
    month = april;

    if (validate_nums(day, month, year) != WRONG_DAYS_COUNT)
    {
        err_cnt++;
    }

    day = 30;
    month = february;

    if (validate_nums(day, month, year) != WRONG_DAYS_COUNT)
    {
        err_cnt++;
    }

    day = 29;
    month = february;
    year = 2001;

    if (validate_nums(day, month, year) != WRONG_DAYS_COUNT)
    {
        err_cnt++;
    }

    day = 29;
    month = february;
    year = 2000;

    if (validate_nums(day, month, year) != OK)
    {
        err_cnt++;
    }

    day = 26;
    month = october;
    year = 2019;

    if (validate_nums(day, month, year) != OK)
    {
        err_cnt++;
    }

    printf("%s: %s\n", __func__, err_cnt ? "FAILED" : "OK");
}

void test_validate_nums_ok()
{
    int err_cnt = 0;

    int day, month, year;

    day = 29;
    month = february;
    year = 2000;

    if (validate_nums(day, month, year) != OK)
    {
        err_cnt++;
    }

    day = 26;
    month = october;
    year = 2019;

    if (validate_nums(day, month, year) != OK)
    {
        err_cnt++;
    }

    printf("%s: %s\n", __func__, err_cnt ? "FAILED" : "OK");
}

void test_validate_nums()
{
    test_validate_nums_logicerrs();
    test_validate_nums_ok();
}

void test_is_alphas_logicerrs()
{
    int err_cnt = 0;

    char *string = "Kononenko1";

    if (is_alphas(string) != INVALID_CHAR_ERROR)
    {
        err_cnt++;
    }

    printf("%s: %s\n", __func__, err_cnt ? "FAILED" : "OK");
}

void test_is_alphas_ok()
{
    int err_cnt = 0;

    char *string = "Kononenko";

    if (is_alphas(string) != OK)
    {
        err_cnt++;
    }

    printf("%s: %s\n", __func__, err_cnt ? "FAILED" : "OK");
}

void test_is_alphas()
{
    test_is_alphas_logicerrs();
    test_is_alphas_ok();
}
