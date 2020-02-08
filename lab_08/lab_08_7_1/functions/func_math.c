/*
Math operations interface for dynamic arrays.
*/

#include <math.h>
#include <stdio.h>

#define OK 0
#define MEMORY_ALLOC_ERROR 1

#define GOT_ARG 1

#define EPS 1e-6

/*
Find cubic mean of array's elements.
More on cubic mean: https://en.wikipedia.org/wiki/Cubic_mean .

Input data:
* double *const array - pointer to array where need to find cubic mean.
* const double *const array_end_pointer - pointer to post array memory.
* double *const cubic_mean - cubic mean to be found.

Output data:
* Return code - OK or MEMORY_ALLOC_ERROR.
*/
int find_cubic_mean(double *const array,
                    const double *const array_end_pointer,
                    double *const cubic_mean)
{
    if (array && array_end_pointer)
    {
        double temp_sum = 0;

        for (double *el_ind = array; el_ind < array_end_pointer; el_ind++)
        {
            double temp_num = fabs(*el_ind);
            temp_sum += (temp_num * temp_num * temp_num) /
                        (array_end_pointer - array);
        }

        *cubic_mean = pow(temp_sum, (double)1 / 3);

        return OK;
    }

    return MEMORY_ALLOC_ERROR;
}

/*
Find minimum of array's elements.

Input data:
* double *const array - pointer to array where need to find cubic mean.
* const double *const array_end_pointer - pointer to post array memory.
* double *const min_el - minimum to be found.

Output data:
* Return code - OK or MEMORY_ALLOC_ERROR.
*/
int find_array_minimum(double *const array,
                       const double *const array_end_pointer,
                       double *const min_el)
{
    if (array && array_end_pointer)
    {
        double cur_min_el = *array;

        for (double *el_ind = array + 1; el_ind < array_end_pointer; el_ind++)
        {
            if (*el_ind + EPS < cur_min_el)
            {
                cur_min_el = *el_ind;
            }
        }

        *min_el = cur_min_el;

        return OK;
    }

    return MEMORY_ALLOC_ERROR;
}
