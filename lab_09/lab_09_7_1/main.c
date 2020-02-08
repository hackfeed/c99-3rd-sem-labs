#include <stdio.h>
#include <inttypes.h>

#include "headers/defines.h"
#include "headers/ds_dynamic_matrix.h"
#include "headers/func_io.h"
#include "headers/func_matrix.h"

int main()
{
    matrix_t matrix_a, matrix_b, matrix_r;
    int64_t power_a, power_b;

    if (input_params(&matrix_a) != OK)
    {
        return MATRIX_CREATION_ERROR;
    }

    if (input_params(&matrix_b) != OK)
    {
        delete_matrix(&matrix_a);

        return MATRIX_CREATION_ERROR;
    }

    if (input_nonnegative(&power_a) != OK)
    {
        delete_matrix(&matrix_a);
        delete_matrix(&matrix_b);

        return POWER_INPUT_ERROR;
    }

    if (input_nonnegative(&power_b) != OK)
    {
        delete_matrix(&matrix_a);
        delete_matrix(&matrix_b);

        return POWER_INPUT_ERROR;
    }

    if (square_matrix(&matrix_a, &matrix_b) != OK)
    {
        delete_matrix(&matrix_a);
        delete_matrix(&matrix_b);

        return MATRIX_SQUARING_ERROR;
    }

    if (matrix_pow(&matrix_a, &power_a) != OK)
    {
        delete_matrix(&matrix_a);
        delete_matrix(&matrix_b);

        return MATRIX_POW_ERROR;
    }

    if (matrix_pow(&matrix_b, &power_b) != OK)
    {
        delete_matrix(&matrix_a);
        delete_matrix(&matrix_b);

        return MATRIX_POW_ERROR;
    }

    matrix_r.rows = matrix_a.rows;
    matrix_r.columns = matrix_a.columns;

    if (create_matrix(&matrix_r) != OK)
    {
        delete_matrix(&matrix_a);
        delete_matrix(&matrix_b);

        return MEMORY_ALLOC_ERROR;
    }

    if (matrix_mult(&matrix_a, &matrix_b, &matrix_r) != OK)
    {
        delete_matrix(&matrix_a);
        delete_matrix(&matrix_b);
        delete_matrix(&matrix_r);

        return MATRIX_MULTIPLICATION_ERROR;
    }

    output_matrix(&matrix_r);

    delete_matrix(&matrix_a);
    delete_matrix(&matrix_b);
    delete_matrix(&matrix_r);

    return OK;
}