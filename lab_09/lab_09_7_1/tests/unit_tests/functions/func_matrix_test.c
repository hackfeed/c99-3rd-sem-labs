#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#include "../../../headers/ds_dynamic_matrix.h"
#include "../../../headers/func_matrix.h"
#include "../../../headers/defines.h"

void fill_matrix(cp_matrix_t matrix, const int ascending)
{
    int64_t cur_filler;

    if (ascending)
    {
        cur_filler = 1;
    }
    else
    {
        cur_filler = matrix->rows * matrix->columns;
    }

    for (int64_t row = 0; row < matrix->rows; ++row)
    {
        for (int64_t col = 0; col < matrix->columns; ++col)
        {
            *(*(matrix->matrix + row) + col) = cur_filler;
            if (ascending)
            {
                cur_filler++;
            }
            else
            {
                cur_filler--;
            }
        }
    }
}

void fill_unit_matrix(cp_matrix_t matrix)
{
    for (int64_t row = 0; row < matrix->rows; ++row)
    {
        for (int64_t col = 0; col < matrix->columns; ++col)
        {
            *(*(matrix->matrix + row) + col) = (row == col);
        }
    }
}

void test_delete_decision_normal()
{
    int err_cnt = 0;

    /* Positive testing */

    matrix_t matrix;
    matrix.rows = 5;
    matrix.columns = 3;

    if (delete_decision(&matrix) != BY_ROWS)
    {
        err_cnt++;
    }

    matrix.rows = 2;
    matrix.columns = 3;

    if (delete_decision(&matrix) != BY_COLUMNS)
    {
        err_cnt++;
    }

    matrix.rows = 3;
    matrix.columns = 3;

    if (delete_decision(&matrix) != BY_ROWS)
    {
        err_cnt++;
    }

    printf("%s: %s\n", __func__, err_cnt ? "FAILED" : "OK");
}

void test_delete_decision()
{
    test_delete_decision_normal();
}

void test_find_min_nullp()
{
    int err_cnt = 0;

    /* Negative testing */

    matrix_t matrix;
    matrix.matrix = NULL;
    int64_t row_min, column_min;

    if (find_min(&matrix, &row_min, &column_min) !=
        MEMORY_ALLOC_ERROR)
    {
        err_cnt++;
    }

    printf("%s: %s\n", __func__, err_cnt ? "FAILED" : "OK");
}

void test_find_min_normal()
{
    int err_cnt = 0;

    /* Positive testing */

    matrix_t matrix_1;
    matrix_1.rows = 3;
    matrix_1.columns = 3;
    int64_t row_min_1, column_min_1;
    create_matrix(&matrix_1);
    fill_matrix(&matrix_1, 1);
    find_min(&matrix_1, &row_min_1, &column_min_1);

    if (row_min_1 != 0 && column_min_1 != 0)
    {
        err_cnt++;
    }
    delete_matrix(&matrix_1);

    matrix_t matrix_2;
    matrix_2.rows = 3;
    matrix_2.columns = 3;
    int64_t row_min_2, column_min_2;
    create_matrix(&matrix_2);
    fill_matrix(&matrix_2, 0);
    find_min(&matrix_2, &row_min_2, &column_min_2);

    if (row_min_2 != 2 && column_min_2 != 2)
    {
        err_cnt++;
    }
    delete_matrix(&matrix_2);

    printf("%s: %s\n", __func__, err_cnt ? "FAILED" : "OK");
}

void test_find_min()
{
    test_find_min_nullp();
    test_find_min_normal();
}

void test_delete_row_nullp()
{
    int err_cnt = 0;

    /* Negative testing */

    matrix_t matrix;
    matrix.matrix = NULL;
    int64_t remove = 1;

    if (delete_row(&matrix, &remove) != MEMORY_ALLOC_ERROR)
    {
        err_cnt++;
    }

    printf("%s: %s\n", __func__, err_cnt ? "FAILED" : "OK");
}

void test_delete_row_normal()
{
    int err_cnt = 0;

    /* Positive testing */

    matrix_t matrix_1;
    matrix_1.rows = 3;
    matrix_1.columns = 3;
    int64_t remove_1 = 1;
    create_matrix(&matrix_1);
    fill_matrix(&matrix_1, 1);
    delete_row(&matrix_1, &remove_1);
    int64_t expected_row[] = { 7, 8, 9 };

    if (matrix_1.rows != 2)
    {
        err_cnt++;
    }

    for (int64_t col = 0; col < matrix_1.columns; ++col)
    {
        if (*(expected_row + col) != *(*(matrix_1.matrix + remove_1) + col))
        {
            err_cnt++;
        }
    }
    delete_matrix(&matrix_1);

    printf("%s: %s\n", __func__, err_cnt ? "FAILED" : "OK");
}

void test_delete_row()
{
    test_delete_row_nullp();
    test_delete_row_normal();
}

void test_delete_column_nullp()
{
    int err_cnt = 0;

    /* Negative testing */

    matrix_t matrix;
    matrix.matrix = NULL;
    int64_t remove = 1;

    if (delete_column(&matrix, &remove) != MEMORY_ALLOC_ERROR)
    {
        err_cnt++;
    }

    printf("%s: %s\n", __func__, err_cnt ? "FAILED" : "OK");
}

void test_delete_column_normal()
{
    int err_cnt = 0;

    /* Positive testing */

    matrix_t matrix_1;
    matrix_1.rows = 3;
    matrix_1.columns = 3;
    int64_t remove_1 = 1;
    create_matrix(&matrix_1);
    fill_matrix(&matrix_1, 1);
    delete_column(&matrix_1, &remove_1);
    int64_t expected_col[] = { 3, 6, 9 };

    if (matrix_1.columns != 2)
    {
        err_cnt++;
    }

    for (int64_t row = 0; row < matrix_1.rows; ++row)
    {
        if (*(expected_col + row) != *(*(matrix_1.matrix + row) + remove_1))
        {
            err_cnt++;
        }
    }
    delete_matrix(&matrix_1);

    printf("%s: %s\n", __func__, err_cnt ? "FAILED" : "OK");
}

void test_delete_column()
{
    test_delete_column_nullp();
    test_delete_column_normal();
}

void test_col_geommean_normal()
{
    int err_cnt = 0;

    /* Positive testing */

    matrix_t matrix;
    matrix.rows = 3;
    matrix.columns = 3;
    int64_t col = 1;
    create_matrix(&matrix);
    fill_matrix(&matrix, 1);

    if (col_geommean(&matrix, col) != 4)
    {
        err_cnt++;
    }
    delete_matrix(&matrix);

    printf("%s: %s\n", __func__, err_cnt ? "FAILED" : "OK");
}

void test_col_geommean()
{
    test_col_geommean_normal();
}

void test_create_geommean_row_nullp()
{
    int err_cnt = 0;

    /* Negative testing */

    matrix_t matrix;
    matrix.matrix = NULL;

    if (create_geommean_row(&matrix) != MEMORY_ALLOC_ERROR)
    {
        err_cnt++;
    }

    printf("%s: %s\n", __func__, err_cnt ? "FAILED" : "OK");
}

void test_create_geommean_row_norml()
{
    int err_cnt = 0;

    /* Positive testing */

    matrix_t matrix_1;
    matrix_1.rows = 3;
    matrix_1.columns = 3;
    create_matrix(&matrix_1);
    fill_matrix(&matrix_1, 1);
    create_geommean_row(&matrix_1);
    int64_t expected_row[] = { 3, 4, 5 };

    if (matrix_1.rows != 4)
    {
        err_cnt++;
    }

    for (int64_t col = 0; col < matrix_1.columns; ++col)
    {
        if (*(expected_row + col) != *(*(matrix_1.matrix + matrix_1.rows - 1) + col))
        {
            err_cnt++;
        }
    }
    delete_matrix(&matrix_1);

    printf("%s: %s\n", __func__, err_cnt ? "FAILED" : "OK");
}

void test_create_geommean_row()
{
    test_create_geommean_row_nullp();
    test_create_geommean_row_norml();
}

void test_row_max_normal()
{
    int err_cnt = 0;

    /* Positive testing */

    matrix_t matrix;
    matrix.rows = 3;
    matrix.columns = 3;
    int64_t row = 1;
    create_matrix(&matrix);
    fill_matrix(&matrix, 1);

    if (row_max(&matrix, row) != 6)
    {
        err_cnt++;
    }
    delete_matrix(&matrix);

    printf("%s: %s\n", __func__, err_cnt ? "FAILED" : "OK");
}

void test_row_max()
{
    test_row_max_normal();
}

void test_create_max_col_nullp()
{
    int err_cnt = 0;

    /* Negative testing */

    matrix_t matrix;
    matrix.matrix = NULL;

    if (create_max_col(&matrix) != MEMORY_ALLOC_ERROR)
    {
        err_cnt++;
    }

    printf("%s: %s\n", __func__, err_cnt ? "FAILED" : "OK");
}

void test_create_max_col_normal()
{
    int err_cnt = 0;

    /* Positive testing */

    matrix_t matrix_1;
    matrix_1.rows = 3;
    matrix_1.columns = 3;
    create_matrix(&matrix_1);
    fill_matrix(&matrix_1, 0);
    create_max_col(&matrix_1);
    int64_t expected_col[] = { 9, 6, 3 };

    if (matrix_1.columns != 4)
    {
        err_cnt++;
    }

    for (int64_t row = 0; row < matrix_1.rows; ++row)
    {
        if (*(expected_col + row) != *(*(matrix_1.matrix + row) + matrix_1.columns - 1))
        {
            err_cnt++;
        }
    }
    delete_matrix(&matrix_1);

    printf("%s: %s\n", __func__, err_cnt ? "FAILED" : "OK");
}

void test_create_max_col()
{
    test_create_max_col_nullp();
    test_create_max_col_normal();
}

void test_matrix_copy_nullp()
{
    int err_cnt = 0;

    /* Negative testing */

    matrix_t from, to;
    from.matrix = NULL;

    if (matrix_copy(&from, &to) != MEMORY_ALLOC_ERROR)
    {
        err_cnt++;
    }

    matrix_t from_1, to_1;
    from_1.rows = 3;
    from_1.columns = 3;
    create_matrix(&from_1);
    to_1.matrix = NULL;

    if (matrix_copy(&from_1, &to_1) != MEMORY_ALLOC_ERROR)
    {
        err_cnt++;
    }
    delete_matrix(&from_1);

    printf("%s: %s\n", __func__, err_cnt ? "FAILED" : "OK");
}

void test_matrix_copy_normal()
{
    int err_cnt = 0;

    /* Positive testing */

    matrix_t from_2, to_2;
    from_2.rows = 3;
    from_2.columns = 3;
    to_2.rows = 3;
    to_2.columns = 3;
    create_matrix(&from_2);
    create_matrix(&to_2);
    fill_matrix(&from_2, 0);
    matrix_copy(&from_2, &to_2);

    for (int64_t row = 0; row < from_2.rows; ++row)
    {
        for (int64_t col = 0; col < from_2.columns; ++col)
        {
            if (*(*(to_2.matrix + row) + col) != *(*(from_2.matrix + row) + col))
            {
                err_cnt++;
            }
        }
    }
    delete_matrix(&from_2);
    delete_matrix(&to_2);

    printf("%s: %s\n", __func__, err_cnt ? "FAILED" : "OK");
}

void test_matrix_copy()
{
    test_matrix_copy_nullp();
    test_matrix_copy_normal();
}

void test_matrix_mult_nullp()
{
    int err_cnt = 0;

    /* Negative testing */

    matrix_t matrix_a, matrix_b, matrix_res;
    matrix_a.matrix = NULL;

    if (matrix_mult(&matrix_a, &matrix_b, &matrix_res) !=
        MEMORY_ALLOC_ERROR)
    {
        err_cnt++;
    }

    matrix_t matrix_a_1, matrix_b_1, matrix_res_1;
    matrix_a_1.rows = 3;
    matrix_a_1.columns = 3;
    create_matrix(&matrix_a_1);
    matrix_b_1.matrix = NULL;

    if (matrix_mult(&matrix_a_1, &matrix_b_1, &matrix_res_1) !=
        MEMORY_ALLOC_ERROR)
    {
        err_cnt++;
    }
    delete_matrix(&matrix_a_1);

    matrix_t matrix_a_2, matrix_b_2, matrix_res_2;
    matrix_a_2.rows = 3;
    matrix_a_2.columns = 3;
    matrix_b_2.rows = 3;
    matrix_b_2.columns = 3;
    create_matrix(&matrix_a_2);
    create_matrix(&matrix_b_2);
    matrix_res_2.matrix = NULL;

    if (matrix_mult(&matrix_a_2, &matrix_b_2, &matrix_res_2) !=
        MEMORY_ALLOC_ERROR)
    {
        err_cnt++;
    }
    delete_matrix(&matrix_a_2);
    delete_matrix(&matrix_b_2);

    printf("%s: %s\n", __func__, err_cnt ? "FAILED" : "OK");
}

void test_matrix_mult_normal()
{
    int err_cnt = 0;

    /* Positive testing */

    matrix_t matrix_a_3, matrix_b_3, matrix_res_3;
    matrix_a_3.rows = 3;
    matrix_a_3.columns = 3;
    matrix_b_3.rows = 3;
    matrix_b_3.columns = 3;
    matrix_res_3.rows = 3;
    matrix_res_3.columns = 3;
    create_matrix(&matrix_a_3);
    create_matrix(&matrix_b_3);
    create_matrix(&matrix_res_3);
    fill_matrix(&matrix_a_3, 1);
    fill_unit_matrix(&matrix_b_3);
    matrix_mult(&matrix_a_3, &matrix_b_3, &matrix_res_3);
    for (int64_t row = 0; row < matrix_a_3.rows; ++row)
    {
        for (int64_t col = 0; col < matrix_a_3.columns; ++col)
        {
            if (*(*(matrix_a_3.matrix + row) + col) != *(*(matrix_res_3.matrix + row) + col))
            {
                err_cnt++;
            }
        }
    }
    delete_matrix(&matrix_a_3);
    delete_matrix(&matrix_b_3);
    delete_matrix(&matrix_res_3);

    printf("%s: %s\n", __func__, err_cnt ? "FAILED" : "OK");
}

void test_matrix_mult()
{
    test_matrix_mult_nullp();
    test_matrix_mult_normal();
}
