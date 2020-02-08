/*
Matrix handling utilities.
*/

#include <inttypes.h>
#include <stdlib.h>
#include <math.h>

#include "../headers/ds_dynamic_matrix.h"
#include "../headers/defines.h"

/*
Decide by which parameter matrix will be reduced to
become square matrix.

Input data:
* cvcp_matrix_t matrix - matrix to be reduced.

Output data:
* BY_COLUMNS if reduced by columns, otherwise - BY_ROWS
*/
int delete_decision(cvcp_matrix_t matrix)
{
    return (matrix->rows < matrix->columns) ? BY_COLUMNS : BY_ROWS;
}

/*
Find matrix minimum element using columns search.

Input data:
* cvcp_matrix_t matrix - matrix where need to find minimum element.
* cp_int64_t row_min, cp_int64_t column_min - row and column indexes 
of found minimum element.

Output data:
* Return code - OK or MEMORY_ALLOC_ERROR.
*/
int find_min(cvcp_matrix_t matrix, cp_int64_t row_min, cp_int64_t column_min)
{
    if (!matrix->matrix)
    {
        return MEMORY_ALLOC_ERROR;
    }

    int64_t cur_min = **matrix->matrix;
    *row_min = 0;
    *column_min = 0;
    for (int64_t col = 0; col < matrix->columns; ++col)
    {
        for (int64_t row = 0; row < matrix->rows; ++row)
        {
            if (*(*(matrix->matrix + row) + col) < cur_min)
            {
                cur_min = *(*(matrix->matrix + row) + col);
                *row_min = row;
                *column_min = col;
            }
        }
    }

    return OK;
}

/*
Reduce matrix by row deletion.

Input data:
* cp_matrix_t matrix - matrix to be reduced.
* cp_int64_t remove - row to be deleted.

Output data:
* Return code - OK, NEW_ALLOC_ERROR or MEMORY_ALLOC_ERROR.
*/
int delete_row(cp_matrix_t matrix, cp_int64_t remove)
{
    if (!matrix->matrix)
    {
        return MEMORY_ALLOC_ERROR;
    }

    for (int64_t row = *remove; row < matrix->rows - 1; ++row)
    {
        for (int64_t col = 0; col < matrix->columns; ++col)
        {
            *(*(matrix->matrix + row) + col) = *(*(matrix->matrix + row + 1) + col);
        }
    }

    matrix->rows--;
    free(*(matrix->matrix + matrix->rows));

    matrix_t new_matrix;
    new_matrix.matrix = \
        (int64_t **)realloc(matrix->matrix, matrix->rows * sizeof(int64_t *));

    if (new_matrix.matrix)
    {
        matrix->matrix = new_matrix.matrix;
        new_matrix.matrix = NULL;

        return OK;
    }

    return NEW_ALLOC_ERROR;
}

/*
Reduce matrix by column deletion.

Input data:
* cp_matrix_t matrix - matrix to be reduced.
* cp_int64_t remove - column to be deleted.

Output data:
* Return code - OK, NEW_ALLOC_ERROR or MEMORY_ALLOC_ERROR.
*/
int delete_column(cp_matrix_t matrix, cp_int64_t remove)
{
    if (!matrix->matrix)
    {
        return MEMORY_ALLOC_ERROR;
    }

    for (int64_t row = 0; row < matrix->rows; ++row)
    {
        for (int64_t col = *remove; col < matrix->columns - 1; ++col)
        {
            *(*(matrix->matrix + row) + col) = *(*(matrix->matrix + row) + col + 1);
        }

        int64_t *new_row = \
            (int64_t *)realloc(*(matrix->matrix + row), (matrix->columns - 1) * sizeof(int64_t));

        if (new_row)
        {
            *(matrix->matrix + row) = new_row;
            new_row = NULL;
        }
        else
        {
            return NEW_ALLOC_ERROR;
        }
    }

    matrix->columns--;

    return OK;
}

/*
Make square matrix with K size from matrix N*M size, where K = min(N, M).

Input data:
* cp_matrix_t matrix matrix to be squared.

Output data:
* Return code - OK or MEMORY_ALLOC_ERROR.
*/
int delete_square(cp_matrix_t matrix)
{
    if (!matrix->matrix)
    {
        return MEMORY_ALLOC_ERROR;
    }

    while (matrix->rows != matrix->columns)
    {
        int key = delete_decision(matrix);
        int64_t min_col, min_row;

        if (find_min(matrix, &min_row, &min_col) != OK)
        {
            return MEMORY_ALLOC_ERROR;
        }

        if (key == BY_COLUMNS)
        {
            if (delete_column(matrix, &min_col) != OK)
            {
                return MEMORY_ALLOC_ERROR;
            }
        }
        else
        {
            if (delete_row(matrix, &min_row) != OK)
            {
                return MEMORY_ALLOC_ERROR;
            }
        }
    }

    return OK;
}

/*
Find matrix column's geometric mean's module.

Input data:
* cvcp_matrix_t matrix - matrix to be handled.
* cv_int64_t col - index of column to be handled.

Output data:
* Found geometric mean's module of column.
*/
int64_t col_geommean(cvcp_matrix_t matrix, cv_int64_t col)
{
    int64_t prod = 1;
    for (int64_t row = 0; row < matrix->rows; ++row)
    {
        prod *= *(*(matrix->matrix + row) + col);
    }

    return floor(pow(fabs(prod), (double)1 / matrix->rows));
}

/*
Create and add row with found geometric mean of each column.

Input data:
* cp_matrix_t matrix - matrix to be expanded.

Output data:
* Return code - OK, NEW_ALLOC_ERROR or MEMORY_ALLOC_ERROR.
*/
int create_geommean_row(cp_matrix_t matrix)
{
    if (!matrix->matrix)
    {
        return MEMORY_ALLOC_ERROR;
    }

    matrix_t new_matrix;
    new_matrix.matrix = \
        (int64_t **)realloc(matrix->matrix, (matrix->rows + 1) * sizeof(int64_t *));

    if (new_matrix.matrix)
    {
        matrix->matrix = new_matrix.matrix;
        new_matrix.matrix = NULL;
        *(matrix->matrix + matrix->rows) = \
            (int64_t *)malloc(matrix->columns * sizeof(int64_t));
    }
    else
    {
        return NEW_ALLOC_ERROR;
    }

    for (int64_t col = 0; col < matrix->columns; ++col)
    {
        *(*(matrix->matrix + matrix->rows) + col) = col_geommean(matrix, col);
    }

    matrix->rows++;

    return OK;
}

/*
Find matrix row's maximum element.

Input data:
* cvcp_matrix_t matrix - matrix to be handled.
* cv_int64_t row - index of row to be handled.

Output data:
* Found maximum element of row.
*/
int64_t row_max(cvcp_matrix_t matrix, cv_int64_t row)
{
    int64_t max = *(*(matrix->matrix + row));
    for (int64_t col = 1; col < matrix->columns; ++col)
    {
        if (*(*(matrix->matrix + row) + col) > max)
        {
            max = *(*(matrix->matrix + row) + col);
        }
    }

    return max;
}

/*
Create and add row with found geometric mean of each column.

Input data:
* cp_matrix_t matrix - matrix to be expanded.

Output data:
* Return code - OK, NEW_ALLOC_ERROR or MEMORY_ALLOC_ERROR.
*/
int create_max_col(cp_matrix_t matrix)
{
    if (!matrix->matrix)
    {
        return MEMORY_ALLOC_ERROR;
    }

    for (int64_t row = 0; row < matrix->rows; ++row)
    {
        int64_t *new_row = \
            (int64_t *)realloc(*(matrix->matrix + row), (matrix->columns + 1) * sizeof(int64_t));

        if (new_row)
        {
            *(matrix->matrix + row) = new_row;
            new_row = NULL;
        }
        else
        {
            return NEW_ALLOC_ERROR;
        }

        *(*(matrix->matrix + row) + matrix->columns) = row_max(matrix, row);
    }

    matrix->columns++;

    return OK;
}

/*
Expand two matrices with N*N and M*M size to K*K size, where K - max(N, M).

Input data:
* cp_matrix_t matrix_a, matrix_b - matrices to be expanded.

Output data:
* Return code: OK, NEW_ROW_CREATION_ERROR, NEW_COLUMN_CREATION_ERROR or 
MEMORY_ALLOC_ERROR.
*/
int expand_square(cp_matrix_t matrix_a, cp_matrix_t matrix_b)
{
    if (!matrix_a->matrix || !matrix_b->matrix)
    {
        return MEMORY_ALLOC_ERROR;
    }

    if (matrix_a->rows < matrix_b->rows)
    {
        while (matrix_a->rows != matrix_b->rows)
        {
            if (create_geommean_row(matrix_a) != OK)
            {
                return NEW_ROW_CREATION_ERROR;
            }
        }
    }
    else
    {
        if (matrix_b->rows < matrix_a->rows)
        {
            while (matrix_a->rows != matrix_b->rows)
            {
                if (create_geommean_row(matrix_b) != OK)
                {
                    return NEW_ROW_CREATION_ERROR;
                }
            }
        }
    }

    if (matrix_a->columns < matrix_b->columns)
    {
        while (matrix_a->columns != matrix_b->columns)
        {
            if (create_max_col(matrix_a) != OK)
            {
                return NEW_COLUMN_CREATION_ERROR;
            }
        }
    }
    else
    {
        if (matrix_b->columns < matrix_a->columns)
        {
            while (matrix_a->columns != matrix_b->columns)
            {
                if (create_max_col(matrix_b) != OK)
                {
                    return NEW_COLUMN_CREATION_ERROR;
                }
            }
        }
    }

    return OK;
}

/*
Combination of square_matrix_delete and square_matrix_expand functions.

Input data:
* cp_matrix_t matrix_a, matrix_b - matrices to be squared.

Output data:
* Return code: OK, SQUARING_BY_DELETION_ERROR, SQUARING_BY_EXPANSION_ERROR or 
MEMORY_ALLOC_ERROR.
*/
int square_matrix(cp_matrix_t matrix_a, cp_matrix_t matrix_b)
{
    if (!matrix_a->matrix || !matrix_b->matrix)
    {
        return MEMORY_ALLOC_ERROR;
    }

    if (delete_square(matrix_a) != OK)
    {
        return SQUARING_BY_DELETION_ERROR;
    }

    if (delete_square(matrix_b) != OK)
    {
        return SQUARING_BY_DELETION_ERROR;
    }

    if (expand_square(matrix_a, matrix_b) != OK)
    {
        return SQUARING_BY_EXPANSION_ERROR;
    }

    return OK;
}

/*
Copy matrix to another matrix.

Input data:
* cp_matrix_t from - matrix to be copied.
* cp_matrix_t to - copied matrix.

Output data:
* Return code: OK or MEMORY_ALLOC_ERROR.
*/
int matrix_copy(cp_matrix_t from, cp_matrix_t to)
{
    if (!from->matrix || !to->matrix)
    {
        return MEMORY_ALLOC_ERROR;
    }

    for (int64_t row = 0; row < from->rows; ++row)
    {
        for (int64_t col = 0; col < from->columns; ++col)
        {
            *(*(to->matrix + row) + col) = *(*(from->matrix + row) + col);
        }
    }

    return OK;
}

/*
Multiply two square matrices.

Input data:
* cp_matrix_t matrix_a, matrix_b - matrices to be multiplied.
* cp_matrix_t matrix_r - result of multiplication.

Output data:
* Return code: OK or MEMORY_ALLOC_ERRROR.
*/
int matrix_mult(cp_matrix_t matrix_a, cp_matrix_t matrix_b, cp_matrix_t matrix_r)
{
    if (!matrix_a->matrix || !matrix_b->matrix || !matrix_r->matrix)
    {
        return MEMORY_ALLOC_ERROR;
    }

    for (int64_t main_row = 0; main_row < matrix_a->rows; ++main_row)
    {
        for (int64_t row = 0; row < matrix_a->rows; ++row)
        {
            int64_t cur_element = 0;

            for (int64_t col = 0; col < matrix_a->columns; ++col)
            {
                cur_element += *(*(matrix_a->matrix + main_row) + col) * *(*(matrix_b->matrix + col) + row);
            }

            *(*(matrix_r->matrix + main_row) + row) = cur_element;
        }
    }

    return OK;
}

/*
Matrix exponentiation.

Input data:
* cp_matrix_t matrix - matrix to be exponentiated.
* cp_int64_t power - exponent.

Output data:
* Return code: OK or MEMORY_ALLOC_ERROR.
*/
int matrix_pow(cp_matrix_t matrix, cp_int64_t power)
{
    if (!matrix->matrix)
    {
        return MEMORY_ALLOC_ERROR;
    }

    if (*power == 0)
    {
        for (int64_t row = 0; row < matrix->rows; ++row)
        {
            for (int64_t col = 0; col < matrix->columns; ++col)
            {
                *(*(matrix->matrix + row) + col) = (row == col);
            }
        }

        return OK;
    }

    matrix_t tmp, res;

    res.rows = matrix->rows;
    res.columns = matrix->columns;
    
    tmp.rows = matrix->rows;
    tmp.columns = matrix->columns;

    if (create_matrix(&res) != OK)
    {
        return MEMORY_ALLOC_ERROR;
    }

    if (create_matrix(&tmp) != OK)
    {
        delete_matrix(&res);

        return MEMORY_ALLOC_ERROR;
    }

    if (matrix_copy(matrix, &tmp) != OK)
    {
        delete_matrix(&tmp);
        delete_matrix(&res);

        return MEMORY_ALLOC_ERROR;
    }

    for (int64_t pwr = 1; pwr < *power; ++pwr)
    {
        matrix_mult(matrix, &tmp, &res);
        matrix_copy(&res, matrix);
    }

    delete_matrix(&res);
    delete_matrix(&tmp);

    return OK;
}