/*
CDIO utilities for exp data data structure.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "headers/defines.h"
#include "headers/typedefs.h"

/*
Create exp data record based on validated buffer data.

Input data:
* exp_t *const exp - record to be created.
* const bufexp_t *const buf - validate buffer base for exp record creation.

Output data:
* Return code: OK or MEMORY_ALLOC_ERROR.
*/
int create_data(exp_t *const exp, const bufexp_t *const buf)
{
    exp->date = (char *)malloc((strlen(buf->date) + 1) * sizeof(char));
    if (!exp->date)
    {
        return MEMORY_ALLOC_ERROR;
    }

    exp->technician = (char *)malloc((strlen(buf->technician) + 1) * sizeof(char));
    if (!exp->technician)
    {
        free(exp->date);

        return MEMORY_ALLOC_ERROR;
    }

    exp->data = (double *)malloc(buf->count * sizeof(double));
    if (!exp->data)
    {
        free(exp->date);
        free(exp->technician);

        return MEMORY_ALLOC_ERROR;
    }

    return OK;
}

/*
Delete exp data record.

Input data:
* exp_t *const exp - record to be deleted.

Output data:
* Return code: OK or MEMORY_ALLOC_ERROR.
*/
int delete_data(exp_t *const exp)
{
    if (!exp->date || !exp->technician || !exp->data)
    {
        return MEMORY_ALLOC_ERROR;
    }

    free(exp->date);
    free(exp->technician);
    free(exp->data);

    return OK;
}

/*
Input exp data record.

Input data:
* exp_t *const exp - record to be inputted.
* const bufexp_t *const buf - validated data to be copied to exp record.
* FILE *const stream - strean.

Output data:
* Return code: OK, MEMORY_ALLOC_ERROR, NON_POSITIVE_NUMBER_ERROR or 
ARRAY_INPUT_ERROR.
*/
int input_data(exp_t *const exp, const bufexp_t *const buf, FILE *const stream)
{
    if (!buf->date || !buf->technician || !exp->data)
    {
        return MEMORY_ALLOC_ERROR;
    }
    strcpy(exp->date, buf->date);
    strcpy(exp->technician, buf->technician);

    if (buf->count <= 0)
    {
        return NON_POSITIVE_NUMBER_ERROR;
    }
    exp->count = buf->count;

    for (int measure = 0; measure < exp->count; ++measure)
    {
        if (fscanf(stream, "%lf", exp->data + measure) != GOT_ARG)
        {
            return ARRAY_INPUT_ERROR;
        }
    }

    return OK;
}

/*
Output exp data record.

Input data:
* const exp_t *const exp - record to be outputted.
* FILE *const stream - strean.

Output data:
* Return code: OK, MEMORY_ALLOC_ERROR or NON_POSITIVE_NUMBER_ERROR.
*/
int output_data(const exp_t *const exp, FILE *const stream)
{
    if (!exp->date || !exp->technician || !exp->data)
    {
        return MEMORY_ALLOC_ERROR;
    }

    if (exp->count <= 0)
    {
        return NON_POSITIVE_NUMBER_ERROR;
    }

    fprintf(stream, "%s\n", exp->date);
    fprintf(stream, "%s\n", exp->technician);
    fprintf(stream, "%d ", exp->count);
    for (int measure = 0; measure < exp->count; ++measure)
    {
        fprintf(stream, "%lf ", *(exp->data + measure));
    }
    fprintf(stream, "\n");

    return OK;
}