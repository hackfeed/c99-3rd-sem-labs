#include <stdio.h>

#include "../../../headers/func_math.h"

#define OK 0
#define MEMORY_ALLOC_ERROR 1

#define EPS 1e-6

void test_find_cubic_mean()
{
    int err_cnt = 0;

    double *array = NULL;
    double arp = 0xFEEDDEAD;
    double *array_end_pointer = &arp;
    double *cubic_mean = &arp;

    /* Negative testing */

    if (find_cubic_mean(array, array_end_pointer, cubic_mean) != MEMORY_ALLOC_ERROR)
    {
        err_cnt++;
    }

    double *array_new = &arp;
    double *array_end_pointer_new = NULL;
    double *cubic_mean_new = &arp;

    if (find_cubic_mean(array_new, array_end_pointer_new, cubic_mean_new) != MEMORY_ALLOC_ERROR)
    {
        err_cnt++;
    }

    /* Positive testing */

    double array_new_2[] = {1, 2, 3, 4};
    double *array_end_pointer_new_2 = array_new_2 + 4;
    double cubic_mean_new_2, excellent_cubic_mean = 2.924017;

    find_cubic_mean(array_new_2, array_end_pointer_new_2, &cubic_mean_new_2);

    if (cubic_mean_new_2 - excellent_cubic_mean > EPS)
    {
        err_cnt++;
    }

    printf("%s: %s\n", __func__, err_cnt ? "FAILED" : "OK");
}

void test_find_array_minimum()
{
    int err_cnt = 0;

    double *array = NULL;
    double arp = 0xBEEFCAFE;
    double *array_end_pointer = &arp;
    double min_el;

    /* Negative testing */

    if (find_array_minimum(array, array_end_pointer, &min_el) != MEMORY_ALLOC_ERROR)
    {
        err_cnt++;
    }

    double *array_new = &arp;
    double *array_end_pointer_new = NULL;
    double min_el_new;

    if (find_array_minimum(array_new, array_end_pointer_new, &min_el_new) != MEMORY_ALLOC_ERROR)
    {
        err_cnt++;
    }

    /* Positive testing */

    double array_new_2[] = {1, 2, 3, 4};
    double *array_end_pointer_new_2 = array_new_2 + 4;
    double min_el_new_2;

    find_array_minimum(array_new_2, array_end_pointer_new_2, &min_el_new_2);

    if (min_el_new_2 != 1)
    {
        err_cnt++;
    }

    double array_new_3[] = {1, 2, 3, -1};
    double *array_end_pointer_new_3 = array_new_3 + 4;
    double min_el_new_3;

    find_array_minimum(array_new_3, array_end_pointer_new_3, &min_el_new_3);

    if (min_el_new_3 != -1)
    {
        err_cnt++;
    }

    double array_new_4[] = {1, 1, 1, 1};
    double *array_end_pointer_new_4 = array_new_4 + 4;
    double min_el_new_4;

    find_array_minimum(array_new_4, array_end_pointer_new_4, &min_el_new_4);

    if (min_el_new_4 != 1)
    {
        err_cnt++;
    }

    printf("%s: %s\n", __func__, err_cnt ? "FAILED" : "OK");
}
