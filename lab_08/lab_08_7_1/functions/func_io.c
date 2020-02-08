/*
IO interface.
*/

#include <stdio.h>

#define OK 0
#define NUM_INPUT_ERROR -5
#define NEGATIVE_INPUT_ERROR -6

#define GOT_ARG 1

/*
Input positive int number.

Input data:
* int *const num_to_be_entered - pointer for entered num.

Output data:
* Return code - OK or NUM_INPUT_ERROR.
*/
int input_positive_int(int *const num_to_be_entered)
{
    if (scanf("%d", num_to_be_entered) != GOT_ARG)
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
* int *const num_to_be_entered - pointer for entered num.

Output data:
* Return code - OK or NUM_INPUT_ERROR.
*/
int input_non_negative_int(int *const num_to_be_entered)
{
    if (scanf("%d", num_to_be_entered) != GOT_ARG)
    {
        return NUM_INPUT_ERROR;
    }

    if (*num_to_be_entered < 0)
    {
        return NEGATIVE_INPUT_ERROR;
    }

    return OK;
}