#include <stdio.h>
#include <stdlib.h>

#include "headers/ds_exp_data.h"
#include "headers/typedefs.h"
#include "headers/defines.h"

void test_create_data_ok()
{
    int err_cnt = 0;

    bufexp_t buf = { .date = "04.03.2000", .technician = "Kononenko", .count = 4 };
    exp_t exp;

    if (create_data(&exp, &buf) != OK)
    {
        err_cnt++;
    }
    delete_data(&exp);

    printf("%s: %s\n", __func__, err_cnt ? "FAILED" : "OK");
}

void test_create_data()
{
    test_create_data_ok();
}

void test_delete_data_nullp()
{
    int err_cnt = 0;

    double arr[] = { 1, 2, 3, 4 };

    exp_t exp = { .date = NULL, .technician = "Kononenko", .count = 4, .data = arr };

    if (delete_data(&exp) != MEMORY_ALLOC_ERROR)
    {
        err_cnt++;
    }

    exp_t exp_1 = { .date = "04.03.2000", .technician = NULL, .count = 4, .data = arr };

    if (delete_data(&exp_1) != MEMORY_ALLOC_ERROR)
    {
        err_cnt++;
    }

    exp_t exp_2 = { .date = "04.03.2000", .technician = "Kononenko", .count = 4, .data = NULL };

    if (delete_data(&exp_2) != MEMORY_ALLOC_ERROR)
    {
        err_cnt++;
    }

    printf("%s: %s\n", __func__, err_cnt ? "FAILED" : "OK");
}

void test_delete_data_ok()
{
    int err_cnt = 0;

    char *date = (char *)malloc(11 * sizeof(char));
    char *technician = (char *)malloc(10 * sizeof(char));
    double *data = (double *)malloc(4 * sizeof(double));

    exp_t exp = { .date = date, .technician = technician, .count = 4, .data = data };

    if (delete_data(&exp) != OK)
    {
        err_cnt++;
    }

    printf("%s: %s\n", __func__, err_cnt ? "FAILED" : "OK");
}

void test_delete_data()
{
    test_delete_data_nullp();
    test_delete_data_ok();
}

void test_input_data_nullp()
{
    int err_cnt = 0;

    bufexp_t buf = { .date = "04.03.2000", .technician = "Kononenko", .count = 4 };
    exp_t exp;

    create_data(&exp, &buf);
    free(exp.data);

    exp.data = NULL;

    if (input_data(&exp, &buf, stdin) != MEMORY_ALLOC_ERROR)
    {
        err_cnt++;
    }

    double *data = (double *)malloc(4 * sizeof(double));
    exp.data = data;

    delete_data(&exp);

    printf("%s: %s\n", __func__, err_cnt ? "FAILED" : "OK");
}

void test_input_data_spoiled()
{
    int err_cnt = 0;

    bufexp_t buf = { .date = "04.03.2000", .technician = "Kononenko", .count = 4 };
    exp_t exp;

    create_data(&exp, &buf);

    buf.count = -3;

    if (input_data(&exp, &buf, stdin) != NON_POSITIVE_NUMBER_ERROR)
    {
        err_cnt++;
    }
    delete_data(&exp);

    printf("%s: %s\n", __func__, err_cnt ? "FAILED" : "OK");
}

void test_input_data_wrongin()
{
    int err_cnt = 0;

    bufexp_t buf = { .date = "04.03.2000", .technician = "Kononenko", .count = 4 };
    exp_t exp;

    create_data(&exp, &buf);

    freopen("./tests/unit_tests/negative_input_01.txt", "r", stdin);
    if (input_data(&exp, &buf, stdin) != ARRAY_INPUT_ERROR)
    {
        err_cnt++;
    }
    delete_data(&exp);

    printf("%s: %s\n", __func__, err_cnt ? "FAILED" : "OK");
}

void test_input_data_ok()
{
    int err_cnt = 0;

    bufexp_t buf = { .date = "04.03.2000", .technician = "Kononenko", .count = 4 };
    exp_t exp;

    create_data(&exp, &buf);

    freopen("./tests/unit_tests/positive_input_01.txt", "r", stdin);
    if (input_data(&exp, &buf, stdin) != OK)
    {
        err_cnt++;
    }
    delete_data(&exp);

    printf("%s: %s\n", __func__, err_cnt ? "FAILED" : "OK");
}

void test_input_data()
{
    test_input_data_nullp();
    test_input_data_spoiled();
    test_input_data_wrongin();
    test_input_data_ok();
}

void test_output_data_nullp()
{
    int err_cnt = 0;

    double arr[] = { 1, 2, 3, 4 };

    exp_t exp = { .date = NULL, .technician = "Kononenko", .count = 4, .data = arr };

    if (output_data(&exp, stdin) != MEMORY_ALLOC_ERROR)
    {
        err_cnt++;
    }

    exp_t exp_1 = { .date = "04.03.2000", .technician = NULL, .count = 4, .data = arr };

    if (output_data(&exp_1, stdin) != MEMORY_ALLOC_ERROR)
    {
        err_cnt++;
    }

    exp_t exp_2 = { .date = "04.03.2000", .technician = "Kononenko", \
        .count = 4, .data = NULL };

    if (output_data(&exp_2, stdin) != MEMORY_ALLOC_ERROR)
    {
        err_cnt++;
    }

    printf("%s: %s\n", __func__, err_cnt ? "FAILED" : "OK");
}

void test_output_data_spoiled()
{
    int err_cnt = 0;

    bufexp_t buf = { .date = "04.03.2000", .technician = "Kononenko", .count = 4 };
    exp_t exp;

    create_data(&exp, &buf);

    exp.count = -3;

    if (output_data(&exp, stdin) != NON_POSITIVE_NUMBER_ERROR)
    {
        err_cnt++;
    }
    delete_data(&exp);

    printf("%s: %s\n", __func__, err_cnt ? "FAILED" : "OK");
}

void test_output_data_ok()
{
    int err_cnt = 0;

    double arr[] = { 1, 2, 3, 4 };

    exp_t exp = { .date = "04.03.2000", .technician = "Kononenko", .count = 4, .data = arr };

    if (output_data(&exp, stdin) != OK)
    {
        err_cnt++;
    }

    printf("%s: %s\n", __func__, err_cnt ? "FAILED" : "OK");
}

void test_output_data()
{
    test_output_data_nullp();
    test_output_data_spoiled();
    test_output_data_ok();
}