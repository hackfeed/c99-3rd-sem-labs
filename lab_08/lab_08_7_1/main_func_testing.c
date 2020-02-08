#include <stdio.h>

#include "headers/ds_dynamic_array.h"
#include "headers/func_array.h"
#include "headers/func_io.h"
#include "headers/func_math.h"

#define OK 0
#define AMOUNT_INPUT_ERROR -1
#define MEMORY_ALLOC_ERROR 1
#define ARRAY_INPUT_ERROR 2
#define POS_INPUT_ERROR -2
#define CUBIC_MEAN_ERROR -3
#define REMAP_ERROR -4
#define REALLOC_ERROR -5
#define MINIMUM_FIND_ERROR -6
#define INSERTION_ERROR -7
#define OUTPUT_ERROR -8
#define MAX_DELETION_ERROR -9

#define REDUCE_BY_TWO -2
#define EXPAND_BY_THREE 3

int main()
{
    double *array, *array_end_pointer;
    double cubic_mean, min_el, *pos;
    int elements_amount, insert_pos;

    if (input_positive_int(&elements_amount) != OK)
    {
        return AMOUNT_INPUT_ERROR;
    }

    if (elements_amount <= 2)
    {
        return MAX_DELETION_ERROR;
    }

    if (create_dynamic_array(&array, &elements_amount, &array_end_pointer) != OK)
    {
        return MEMORY_ALLOC_ERROR;
    }

    if (input_dynamic_array(array, array_end_pointer) != OK)
    {
        delete_dynamic_array(array);

        return ARRAY_INPUT_ERROR;
    }

    if (input_non_negative_int(&insert_pos) != OK)
    {
        delete_dynamic_array(array);

        return POS_INPUT_ERROR;
    }

    if (find_cubic_mean(array, array_end_pointer, &cubic_mean) != OK)
    {
        delete_dynamic_array(array);

        return CUBIC_MEAN_ERROR;
    }

    if (remap_array(array, array_end_pointer, &pos, &cubic_mean) != OK)
    {
        delete_dynamic_array(array);

        return REMAP_ERROR;
    }

    if (change_array_len(&array, &array_end_pointer, &elements_amount, REDUCE_BY_TWO) != OK)
    {
        delete_dynamic_array(array);

        return REALLOC_ERROR;
    }

    elements_amount += REDUCE_BY_TWO;

    if (find_array_minimum(array, array_end_pointer, &min_el) != OK)
    {
        delete_dynamic_array(array);

        return MINIMUM_FIND_ERROR;
    }

    if (check_pos_num(array, array_end_pointer, &insert_pos) != OK)
    {
        delete_dynamic_array(array);

        return INSERTION_ERROR;
    }

    if (change_array_len(&array, &array_end_pointer, &elements_amount, EXPAND_BY_THREE) != OK)
    {
        delete_dynamic_array(array);

        return REALLOC_ERROR;
    }

    if (insert_to_array(array, array_end_pointer, &min_el, &insert_pos) != OK)
    {
        delete_dynamic_array(array);

        return INSERTION_ERROR;
    }

    insert_pos = 0;
    if (insert_to_array(array, array_end_pointer, &min_el, &insert_pos) != OK)
    {
        delete_dynamic_array(array);

        return INSERTION_ERROR;
    }

    insert_pos = array_end_pointer - array - 1;
    if (insert_to_array(array, array_end_pointer, &min_el, &insert_pos) != OK)
    {
        delete_dynamic_array(array);

        return INSERTION_ERROR;
    }

    if (output_dynamic_array(array, array_end_pointer) != OK)
    {
        delete_dynamic_array(array);

        return OUTPUT_ERROR;
    }

    if (delete_dynamic_array(array) != OK)
    {
        return MEMORY_ALLOC_ERROR;
    }

    return OK;
}