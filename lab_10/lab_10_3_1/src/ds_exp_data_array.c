/*
CDIO utilities for exparr data array data structure.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "headers/defines.h"
#include "headers/typedefs.h"
#include "headers/ds_exp_data.h"
#include "headers/func_io.h"

/*
Create exparr data array.

Input data:
* exparr_t *const exparr - array to be created.

Output data:
* Return code: OK or MEMORY_ALLOC_ERROR.
*/
int create_array(exparr_t *const exparr)
{
    exparr->exparr = (exp_t *)malloc(sizeof(exp_t));

    if (!exparr->exparr)
    {
        return MEMORY_ALLOC_ERROR;
    }

    exparr->cursize = 0;
    exparr->allocsize = 1;

    return OK;
}

/*
Delete experimnt data array's records until record_till_delete record.

Input data:
* cexparr_t *const exparr - array to be deleted.
* const int to_rec - record until which deletion is processing.

Output data:
* Return code: OK or MEMORY_ALLOC_ERROR.
*/
int delete_array(exparr_t *const exparr, const int to_rec)
{
    for (int rec = 0; rec < to_rec; ++rec)
    {
        if (!(exparr->exparr + rec))
        {
            return MEMORY_ALLOC_ERROR;
        }

        delete_data(exparr->exparr + rec);
    }

    free(exparr->exparr);

    return OK;
}

/*
Expand exparr array when size limit exceeded.

Input data:
* exparr_t *exparr - exparr struct where array going to be expanded.
* const int curexp - number of current exparr.

Output data:
* Return code: OK or MEMORY_ALLOC_ERROR.
*/
int expand_array(exparr_t *exparr, const int curexp)
{
    if (curexp != exparr->allocsize - 1)
    {
        return OK;
    }

    exp_t *new_exparray = (exp_t *)realloc(exparr->exparr, exparr->allocsize * 2 * sizeof(exp_t));

    if (!new_exparray)
    {
        return MEMORY_ALLOC_ERROR;
    }

    exparr->exparr = new_exparray;
    new_exparray = NULL;
    exparr->allocsize *= 2;
    exparr->cursize = curexp;

    return OK;
}

/*
Input exparr data array.

Input data:
* exparr_t *const exparr - array to be inputted.
* FILE *const stream - stream.

Output data:
* Return code: OK, MEMORY_ALLOC_ERROR, INPUT_STATIC_FIELDS_ERROR or 
INPUT_DYNAMIC_FIELDS_ERROR.
*/
int input_array(exparr_t *const exparr, FILE *const stream)
{
    int rec = 0;

    while (TRUE)
    {
        if (!(exparr->exparr + rec))
        {
            return MEMORY_ALLOC_ERROR;
        }
        
        if (expand_array(exparr, rec))
        {
            return ARRAY_EXPANSION_ERROR;
        }

        bufexp_t raw_data = { "\0", "\0", 0 };
        (exparr->exparr + rec)->date = "\0";
        (exparr->exparr + rec)->technician = "\0";
        (exparr->exparr + rec)->count = 0;

        int input_res = input_static_fields(&raw_data, stream);

        if (input_res && input_res != END_OF_INPUT)
        {
            delete_array(exparr, rec);

            return INPUT_STATIC_FIELDS_ERROR;
        }

        if (input_res == END_OF_INPUT)
        {
            return OK;
        }

        if (create_data(exparr->exparr + rec, &raw_data))
        {
            return RECORD_CREATION_ERROR;
        }

        if (input_data(exparr->exparr + rec, &raw_data, stream))
        {
            delete_array(exparr, rec + 1);

            return INPUT_DYNAMIC_FIELDS_ERROR;
        }

        exparr->cursize++;
        rec++;
    }
}

/*
Output exparr data record.

Input data:
* const exparr_t *const exparr - array to be outputted.
* FILE *const stream - stream.

Output data:
* Return code: OK, RECORD_OUTPUT_ERROR or MEMORY_ALLOC_ERROR.
*/
int output_array(const exparr_t *const exparr, FILE *const stream)
{
    for (int rec = 0; rec < exparr->cursize; ++rec)
    {
        if (!(exparr->exparr + rec))
        {
            return MEMORY_ALLOC_ERROR;
        }

        if (output_data(exparr->exparr + rec, stream))
        {
            return RECORD_OUTPUT_ERROR;
        }
    }

    return OK;
}