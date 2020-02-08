/*
IO utilities.
*/

#include <stdio.h>
#include <inttypes.h>

#include "../headers/defines.h"
#include "../headers/ds_dynamic_matrix.h"

/*
Input positive int number.

Input data:
* cp_int64_t num_to_be_entered - pointer for entered num.

Output data:
* Return code - OK or NUM_INPUT_ERROR.
*/
int input_positive(cp_int64_t num_to_be_entered)
{
    if (scanf("%jd", num_to_be_entered) != GOT_ARG)
    {
        return NUM_INPUT_ERROR;
    }

    if (*num_to_be_entered <= 0)
    {
        return NEGATIVE_INPUT_ERROR;
    }

    return OK;
}

/*
Input non negative int number.

Input data:
* cp_int64_t num_to_be_entered - pointer for entered num.

Output data:
* Return code - OK or NUM_INPUT_ERROR.
*/
int input_nonnegative(cp_int64_t num_to_be_entered)
{
    if (scanf("%jd", num_to_be_entered) != GOT_ARG)
    {
        return NUM_INPUT_ERROR;
    }

    if (*num_to_be_entered < 0)
    {
        return NEGATIVE_INPUT_ERROR;
    }

    return OK;
}

/*
Input matrix parameters.

Input data:
* cp_matrix_t matrix - matrix to be created and inputted.

Output data:
* Return code - OK, PARAM_INPUT_ERROR, MEMORY_ALLOC_ERROR or 
MATRIX_INPUT_ERROR.
*/
int input_params(cp_matrix_t matrix)
{
    if (input_positive(&matrix->rows) != OK)
    {
        return PARAM_INPUT_ERROR;
    }

    if (input_positive(&matrix->columns) != OK)
    {
        return PARAM_INPUT_ERROR;
    }

    if (create_matrix(matrix) != OK)
    {
        return MEMORY_ALLOC_ERROR;
    }

    if (input_matrix(matrix) != OK)
    {
        delete_matrix(matrix);

        return MATRIX_INPUT_ERROR;
    }

    return OK;
}