/*
IO utilities.
*/

#include <stdio.h>
#include <string.h>

#include "headers/defines.h"
#include "headers/typedefs.h"
#include "headers/func_validation.h"

/*
Input positive int number.

Input data:
* int *const num - pointer for entered num.
* FILE *const stream - stream.

Output data:
* Return code - OK or NUM_INPUT_ERROR.
*/
int input_positive(int *const num, FILE *const stream)
{
    if (fscanf(stream, "%d", num) != GOT_ARG)
    {
        return NUM_INPUT_ERROR;
    }

    if (*num <= 0)
    {
        return NEGATIVE_INPUT_ERROR;
    }

    return OK;
}

/*
Input string.

Input data:
* char *string - pointer for entered string.
* FILE *const stream - stream.

Output data:
* Return code - OK or STRING_INPUT_ERROR.
*/
int input_string(char *string, FILE *const stream)
{
    if (fscanf(stream, "%s", string) != GOT_ARG)
    {
        return STRING_INPUT_ERROR;
    }

    return OK;
}

/*
Input fields of exp_t in bufexp_t static structure for further validation.

Input data:
* bufexp_t *const bufexp - buffer structure to be filled.

Output data:
* Return code: OK, STRING_INPUT_ERROR, STRING_LEN_EXCEED_ERROR, NUM_INPUT_ERROR
DATE_VALIDATION_ERROR or END_OF_INPUT.
*/
int input_static_fields(bufexp_t *const bufexp, FILE *const stream)
{
    if (input_string(bufexp->date, stream))
    {
        return STRING_INPUT_ERROR;
    }

    if (!strcmp(bufexp->date, "00.00.0000"))
    {
        return END_OF_INPUT;
    }

    if (bufexp->date[MAX_STRING_FIELD_LEN - 1])
    {
        return STRING_LEN_EXCEED_ERROR;
    }

    if (validate(bufexp->date))
    {
        return DATE_VALIDATION_ERROR;
    }

    if (input_string(bufexp->technician, stream) || is_alphas(bufexp->technician))
    {
        return STRING_INPUT_ERROR;
    }

    if (bufexp->technician[MAX_STRING_FIELD_LEN - 1])
    {
        return STRING_LEN_EXCEED_ERROR;
    }

    if (input_positive(&(bufexp->count), stream))
    {
        return NUM_INPUT_ERROR;
    }

    return OK;
}