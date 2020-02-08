/*
CDIO utilities for dynamic array data structure.
*/

#include <stdio.h>
#include <stdlib.h>

#define OK 0
#define MEMORY_ALLOC_ERROR 1
#define ARRAY_INPUT_ERROR 2

#define GOT_ARG 1

/*
Dynamic array creation.

Input data:
* double **array - pointer array to be created.
* const int *const elements_amount - amount of created array's elemets.
* double **array_end_pointer - pointer to post-array memory.

Output data:
* Return code - OK or MEMORY_ALLOC_ERROR.
*/
int create_dynamic_array(double **array,
                         const int *const elements_amount,
                         double **array_end_pointer)
{
    *array = (double *)malloc(*elements_amount * sizeof(double));
    *array_end_pointer = *array + *elements_amount;

    if (*array)
    {
        return OK;
    }

    return MEMORY_ALLOC_ERROR;
}

/*
Dynamic array deletion.

Input data:
* double *array - pointer to array to be deleted.

Output data:
* Return code - OK or MEMORY_ALLOC_ERROR.
*/
int delete_dynamic_array(double *array)
{
    if (array)
    {
        free(array);

        return OK;
    }

    return MEMORY_ALLOC_ERROR;
}

/*
Dynamic array input.

Input data:
* double *const array - pointer to array to be inputed.
* const double *const array_end_pointer - pointer to post array memory.

Output data:
* Return code - OK, MEMORY_ALLOC_ERROR or ARRAY_INPUT_ERROR.
*/
int input_dynamic_array(double *const array,
                        const double *const array_end_pointer)
{
    if (array && array_end_pointer)
    {
        for (double *el_ind = array; el_ind < array_end_pointer; el_ind++)
        {
            if (scanf("%lf", el_ind) != GOT_ARG)
            {
                return ARRAY_INPUT_ERROR;
            }
        }

        return OK;
    }

    return MEMORY_ALLOC_ERROR;
}

/*
Dynamic array input.

Input data:
* double *const array - pointer to array to be outputed.
* const double *const array_end_pointer - pointer to post array memory.

Output data:
* Return code - OK, MEMORY_ALLOC_ERROR or ARRAY_INPUT_ERROR.
*/
int output_dynamic_array(double *const array,
                         const double *const array_end_pointer)
{
    if (array && array_end_pointer)
    {
        for (double *el_ind = array; el_ind < array_end_pointer; el_ind++)
        {
            printf("%.6lf ", *el_ind);
        }
        printf("\n");

        return OK;
    }

    return MEMORY_ALLOC_ERROR;
}
