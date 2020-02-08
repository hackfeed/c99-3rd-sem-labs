#include "include/io.h"

/*
Input double num and check input correctness.

Input data:
* FILE *const stream - stream to read from.
* double *const num - pointer to write to.

Output data:
* Return code - EOK or EINPUTERROR.
*/
int dinput(FILE *const stream, double *const num)
{
    if (fscanf(stream, "%lf", num) != GOT_ARG)
    {
        return EINPUTERROR;
    }

    return EOK;
}

/*
Input string and check input correctness.

Input data:
* FILE *const stream - stream to read from.
* char *str - pointer to write to.

Output data:
* Return code - EOK or EINPUTERROR.
*/
int sinput(FILE *const stream, char *str)
{
    if (fscanf(stream, "%s", str) != GOT_ARG)
    {
        return EINPUTERROR;
    }

    return EOK;
}
