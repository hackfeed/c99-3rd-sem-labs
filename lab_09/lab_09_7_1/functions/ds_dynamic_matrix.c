/*
CDIO utilities for dynamic matrix data structure.
*/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#include "../headers/defines.h"
#include "../headers/ds_dynamic_matrix.h"

/*
Dynamic matrix creation.

Input data:
* cp_matrix_t matrix - matrix to be created.

Output data:
* Return code - OK or MEMORY_ALLOC_ERROR.
*/
int create_matrix(cp_matrix_t matrix)
{
    matrix->matrix = (int64_t **)malloc(matrix->rows * sizeof(int64_t *));

    if (!matrix->matrix)
    {
        return MEMORY_ALLOC_ERROR;
    }

    for (int64_t row = 0; row < matrix->rows; ++row)
    {
        *(matrix->matrix + row) = \
            (int64_t *)malloc(matrix->columns * sizeof(int64_t));

        if (!*(matrix->matrix + row))
        {
            for (int64_t clean = 0; clean < row; ++clean)
            {
                free(*(matrix->matrix + clean));
            }

            free(matrix->matrix);

            return MEMORY_ALLOC_ERROR;
        }
    }

    return OK;
}

/*
Dynamic matrix deletion.

Input data:
* cp_matrix_t matrix - mattrix to be deleted.

Output data:
* Return code - OK or MEMORY_ALLOC_ERROR.
*/
int delete_matrix(cp_matrix_t matrix)
{
    if (!matrix->matrix)
    {
        return MEMORY_ALLOC_ERROR;
    }

    for (int64_t clean = 0; clean < matrix->rows; ++clean)
    {
        if (*(matrix->matrix + clean))
        {
            free(*(matrix->matrix + clean));
        }
    }

    free(matrix->matrix);

    return OK;
}

/*
Dynamic matrix input.

Input data:
* cp_matrix_t matrix - matrix to be inputed.

Output data:
* Return code - OK, MEMORY_ALLOC_ERROR or MATRIX_INPUT_ERROR.
*/
int input_matrix(cp_matrix_t matrix)
{
    if (!matrix->matrix)
    {
        return MEMORY_ALLOC_ERROR;
    }

    for (int64_t row = 0; row < matrix->rows; ++row)
    {
        for (int64_t col = 0; col < matrix->columns; ++col)
        {
            if (scanf("%jd", *(matrix->matrix + row) + col) != GOT_ARG)
            {
                return MATRIX_INPUT_ERROR;
            }
        }
    }

    return OK;
}

/*
Dynamic matrix output.

Input data:
* cvcp_matrix_t matrix - matrix to be outputed.

Output data:
* Return code - OK or MEMORY_ALLOC_ERROR.
*/
int output_matrix(cvcp_matrix_t matrix)
{
    if (!matrix->matrix)
    {
        return MEMORY_ALLOC_ERROR;
    }

    for (int64_t row = 0; row < matrix->rows; ++row)
    {
        for (int64_t col = 0; col < matrix->columns; ++col)
        {
            printf("%5jd ", *(*(matrix->matrix + row) + col));
        }

        printf("%s", "\n");
    }

    return OK;
}