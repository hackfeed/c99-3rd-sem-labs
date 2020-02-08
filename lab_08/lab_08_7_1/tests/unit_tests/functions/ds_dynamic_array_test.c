#include <stdio.h>
#include <stdlib.h>

#include "../../../headers/ds_dynamic_array.h"

#define OK 0
#define MEMORY_ALLOC_ERROR 1
#define ARRAY_INPUT_ERROR 2

void test_create_dynamic_array()
{
    int err_cnt = 0;

    double *array;
    int elements_amount = 5;
    double *array_end_pointer;

    /* Positive testing */

    if (create_dynamic_array(&array,
                             &elements_amount,
                             &array_end_pointer) != OK)
    {
        err_cnt++;
    }

    free(array);

    printf("%s: %s\n", __func__, err_cnt ? "FAILED" : "OK");
}

void test_delete_dynamic_array()
{
    int err_cnt = 0;

    double *array = NULL;

    /* Negative testing */

    if (delete_dynamic_array(array) != MEMORY_ALLOC_ERROR)
    {
        err_cnt++;
    }

    /* Positive testing */

    double *array_new = (double *)calloc(5, sizeof(double));

    if (delete_dynamic_array(array_new) != OK)
    {
        err_cnt++;
    }

    printf("%s: %s\n", __func__, err_cnt ? "FAILED" : "OK");
}

void test_input_dynamic_array()
{
    int err_cnt = 0;

    double *array = NULL;
    double arp = 0xDEADBEEF;
    double *array_end_pointer = &arp;

    /* Negative testing */

    if (input_dynamic_array(array, array_end_pointer) != MEMORY_ALLOC_ERROR)
    {
        err_cnt++;
    }

    double *array_new = &arp;
    double *array_end_pointer_new = NULL;

    if (input_dynamic_array(array_new, array_end_pointer_new) != MEMORY_ALLOC_ERROR)
    {
        err_cnt++;
    }

    double *array_new_1 = (double *)calloc(5, sizeof(double));
    double *array_end_pointer_new_1 = array_new_1 + 5;

    freopen("../negative_input_01.txt", "r", stdin);
    if (input_dynamic_array(array_new_1, array_end_pointer_new_1) != ARRAY_INPUT_ERROR)
    {
        err_cnt++;
    }
    free(array_new_1);

    /* Positive testing */

    double *array_new_2 = (double *)calloc(4, sizeof(double));
    double *array_end_pointer_new_2 = array_new_2 + 4;

    freopen("../positive_input_01.txt", "r", stdin);
    if (input_dynamic_array(array_new_2, array_end_pointer_new_2) != OK)
    {
        err_cnt++;
    }
    free(array_new_2);

    printf("%s: %s\n", __func__, err_cnt ? "FAILED" : "OK");
}

void test_output_dynamic_array()
{
    int err_cnt = 0;

    double *array = NULL;
    double arp = 0xFEEDCAFE;
    double *array_end_pointer = &arp;

    /* Negative testing */

    if (output_dynamic_array(array, array_end_pointer) != MEMORY_ALLOC_ERROR)
    {
        err_cnt++;
    }

    double *array_new = &arp;
    double *array_end_pointer_new = NULL;

    if (output_dynamic_array(array_new, array_end_pointer_new) != MEMORY_ALLOC_ERROR)
    {
        err_cnt++;
    }

    /* Positive testing */

    double array_new_2[] = {1, 2, 3, 4};
    double *array_end_pointer_new_2 = array_new_2 + 4;

    if (output_dynamic_array(array_new_2, array_end_pointer_new_2) != OK)
    {
        err_cnt++;
    }

    printf("%s: %s\n", __func__, err_cnt ? "FAILED" : "OK");
}
