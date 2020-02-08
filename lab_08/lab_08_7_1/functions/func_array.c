/*
Array changing interface.
*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define OK 0
#define MEMORY_ALLOC_ERROR 1
#define NEW_ALLOC_ERROR 3
#define POS_OUT_OF_RANGE_ERROR 4

#define EPS 1e-6
#define MAX_REMAPS 2
#define REDUCING_RANGE 3

/*
Find minimal difference between array element and array's cubic mean.

Input data:
* double *const array - pointer to array where need to find difference.
* const double *const array_end_pointer - pointer to post array memory.
* int *const pos - position of found difference's element.
* const double *const cubic_mean - cubic mean for comparison.

Output data:
* Return code - OK or MEMORY_ALLOC_ERROR.
*/
int find_min_diff(double *const array,
                  const double *const array_end_pointer,
                  double **pos,
                  const double *const cubic_mean)
{
    if (array && array_end_pointer)
    {
        double min_diff = fabs(fabs(*array) - *cubic_mean);
        *pos = array;

        for (double *el_ind = array + 1; el_ind < array_end_pointer; el_ind++)
        {
            double cur_diff = fabs(fabs(*el_ind) - *cubic_mean);

            if (cur_diff + EPS < min_diff)
            {
                min_diff = cur_diff;
                *pos = el_ind;
            }
        }

        return OK;
    }

    return MEMORY_ALLOC_ERROR;
}

/*
Helper swap function.

Input data:
* double *first, *second - pointers to numbers to be swapped.
*/
void swap(double *first, double *second)
{
    double temp = *first;
    *first = *second;
    *second = temp;
}

/*
Move array element to array's end.

Input data:
* double *const array - pointer to array where need to move elements.
* const double *const array_end_pointer - pointer to post array memory.
* const int *const pos - position from which need to move element.

Output data:
* Return code - OK or MEMORY_ALLOC_ERROR.
*/
int move_array_elements(double *const array,
                        const double *const array_end_pointer,
                        double *const pos)
{
    if (array && array_end_pointer)
    {
        for (double *el_ind = pos; el_ind < array_end_pointer - 1; el_ind++)
        {
            swap(el_ind, el_ind + 1);
        }

        return OK;
    }

    return MEMORY_ALLOC_ERROR;
}

/*
Composition of two previous functions. Complete remapping.

Input data:
* double *const array - pointer to array where need to find difference.
* const double *const array_end_pointer - pointer to post array memory.
* double **pos - position of found difference's element.
* const double *const cubic_mean - cubic mean for comparison.

Output data:
* Return code - OK or MEMORY_ALLOC_ERROR.
*/
int remap_array(double *const array,
                const double *const array_end_pointer,
                double **pos,
                const double *const cubic_mean)
{
    if (array && array_end_pointer)
    {
        for (int remap_count = 0; remap_count < MAX_REMAPS; ++remap_count)
        {
            find_min_diff(array, array_end_pointer - remap_count, pos, cubic_mean);
            move_array_elements(array, array_end_pointer, *pos);
        }

        return OK;
    }

    return MEMORY_ALLOC_ERROR;
}

/*
Change array's lenghth in case of remapping.

Input data:
* double **array - array to be changed.
* double **array_end_pointer - new pointer to post-array memory.
* const int *const start_size - initial size of array.
* const int change_size - changing size (- if reduce, + if expand).

Output data:
* Return code - OK or MEMORY_ALLOC_ERROR.
*/
int change_array_len(double **array,
                     double **array_end_pointer,
                     const int *const start_size,
                     const int change_size)
{
    if (*array && *array_end_pointer)
    {
        double *new_array = (double *)realloc(*array, sizeof(double) *
                                                          (*start_size + change_size));
        if (new_array)
        {
            *array = new_array;
            new_array = NULL;

            *array_end_pointer = *array + *start_size + change_size;

            return OK;
        }

        return NEW_ALLOC_ERROR;
    }

    return MEMORY_ALLOC_ERROR;
}

/*
Array insertion function.

Input data:
* double *const array - pointer to array where need to insert number.
* double *const array_end_pointer - pointer to post-array memory.
* const double *const insertion_num - number to be inserted.
* const int *const pos - position of insertion.

Output data:
* Return code - OK, POS_OUT_OF_RANGE_ERROR or MEMORY_ALLOC_ERROR.
*/
int insert_to_array(double *const array,
                    double *const array_end_pointer,
                    const double *const insertion_num,
                    const int *const insertion_pos)
{
    if (array && array_end_pointer)
    {
        for (double *el_ind = array_end_pointer - 1;
             el_ind > array + *insertion_pos; el_ind--)
        {
            swap(el_ind, el_ind - 1);
        }

        *(array + *insertion_pos) = *insertion_num;

        return OK;
    }

    return MEMORY_ALLOC_ERROR;
}

/*
Check insert position valid.

Input data:
* double *const array - pointer to array where need to insert number.
* double *const array_end_pointer - pointer to post-array memory.
* const int *const pos - position of insertion.

Output data:
* Return code - OK, POS_OUT_OF_RANGE_ERROR or MEMORY_ALLOC_ERROR.
*/
int check_pos_num(double *const array,
                  double *const array_end_pointer,
                  const int *const insertion_pos)
{
    if (array && array_end_pointer)
    {
        if (*insertion_pos >= array_end_pointer - array)
        {
            return POS_OUT_OF_RANGE_ERROR;
        }

        return OK;
    }

    return MEMORY_ALLOC_ERROR;
}
