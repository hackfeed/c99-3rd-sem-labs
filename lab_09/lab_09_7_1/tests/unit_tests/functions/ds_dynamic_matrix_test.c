#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#include "../../../headers/ds_dynamic_matrix.h"
#include "../../../headers/defines.h"

void test_create_matrix_normal()
{
    int err_cnt = 0;

    /* Positive testing */

    matrix_t matrix;
    matrix.rows = 5;
    matrix.columns = 5;

    if (create_matrix(&matrix) != OK)
    {
        err_cnt++;
    }

    delete_matrix(&matrix);

    printf("%s: %s\n", __func__, err_cnt ? "FAILED" : "OK");
}

void test_create_matrix()
{
    test_create_matrix_normal();
}

void test_delete_matrix_nullp()
{
    int err_cnt = 0;

    /* Negative testing */

    matrix_t matrix;
    matrix.matrix = NULL;

    if (delete_matrix(&matrix) != MEMORY_ALLOC_ERROR)
    {
        err_cnt++;
    }

    printf("%s: %s\n", __func__, err_cnt ? "FAILED" : "OK");
}

void test_delete_matrix_normal()
{
    int err_cnt = 0;

    /* Positive testing */

    matrix_t matrix_1;
    matrix_1.rows = 2;
    matrix_1.columns = 2;
    create_matrix(&matrix_1);

    if (delete_matrix(&matrix_1) != OK)
    {
        err_cnt++;
    }

    printf("%s: %s\n", __func__, err_cnt ? "FAILED" : "OK");
}

void test_delete_matrix()
{
    test_delete_matrix_nullp();
    test_delete_matrix_normal();
}

void test_input_matrix_nullp()
{
    int err_cnt = 0;

    /* Negative testing */

    matrix_t matrix;
    matrix.rows = 3;
    matrix.columns = 3;
    matrix.matrix = NULL;

    if (input_matrix(&matrix) != MEMORY_ALLOC_ERROR)
    {
        err_cnt++;
    }

    printf("%s: %s\n", __func__, err_cnt ? "FAILED" : "OK");
}

void test_input_matrix_wrongin()
{
    int err_cnt = 0;

    /* Negative testing */

    matrix_t matrix_1;
    matrix_1.rows = 3;
    matrix_1.columns = 3;
    create_matrix(&matrix_1);

    freopen("tests/unit_tests/negative_input_01.txt", "r", stdin);
    if (input_matrix(&matrix_1) != MATRIX_INPUT_ERROR)
    {
        err_cnt++;
    }
    delete_matrix(&matrix_1);
}

void test_input_matrix_normal()
{
    int err_cnt = 0;

    /* Positive testing */

    matrix_t matrix_2;
    matrix_2.rows = 3;
    matrix_2.columns = 3;
    create_matrix(&matrix_2);

    freopen("./tests/unit_tests/positive_input_01.txt", "r", stdin);
    if (input_matrix(&matrix_2) != OK)
    {
        err_cnt++;
    }
    delete_matrix(&matrix_2);

    printf("%s: %s\n", __func__, err_cnt ? "FAILED" : "OK");
}

void test_input_matrix()
{
    test_input_matrix_nullp();
    test_input_matrix_wrongin();
    test_input_matrix_normal();
}

void test_output_matrix_nullp()
{
    int err_cnt = 0;

    /* Negative testing */

    matrix_t matrix;
    matrix.rows = 3;
    matrix.columns = 3;
    matrix.matrix = NULL;

    if (output_matrix(&matrix) != MEMORY_ALLOC_ERROR)
    {
        err_cnt++;
    }

    printf("%s: %s\n", __func__, err_cnt ? "FAILED" : "OK");
}

void test_output_matrix_normal()
{
    int err_cnt = 0;

    /* Positive testing */

    matrix_t matrix_1;
    matrix_1.rows = 3;
    matrix_1.columns = 3;
    create_matrix(&matrix_1);

    freopen("./tests/unit_tests/positive_input_01.txt", "r", stdin);
    input_matrix(&matrix_1);
    if (output_matrix(&matrix_1) != OK)
    {
        err_cnt++;
    }
    delete_matrix(&matrix_1);

    printf("%s: %s\n", __func__, err_cnt ? "FAILED" : "OK");
}

void test_output_matrix()
{
    test_output_matrix_nullp();
    test_output_matrix_normal();
}
