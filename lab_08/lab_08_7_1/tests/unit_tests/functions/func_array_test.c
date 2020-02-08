#include <stdio.h>
#include <stdlib.h>

#include "../../../headers/func_array.h"

#define OK 0
#define MEMORY_ALLOC_ERROR 1
#define NEW_ALLOC_ERROR 3
#define POS_OUT_OF_RANGE_ERROR 4

#define EPS 1e-6

void test_find_min_diff()
{
    int err_cnt = 0;

    double *array = NULL;
    double arp = 0xDEADBEEF;
    double *array_end_pointer = &arp;
    double *pos = &arp, *cubic_mean = &arp;

    /* Negative testing */

    if (find_min_diff(array, array_end_pointer, &pos, cubic_mean) != MEMORY_ALLOC_ERROR)
    {
        err_cnt++;
    }

    double *array_new = &arp;
    double *array_end_pointer_new = NULL;

    if (find_min_diff(array_new, array_end_pointer_new, &pos, cubic_mean) != MEMORY_ALLOC_ERROR)
    {
        err_cnt++;
    }

    /* Positive testing */

    double array_new_2[] = {1, 2, 3, 4};
    double *array_end_pointer_new_2 = array_new_2 + 4;
    double *pos_new, cubic_mean_new = 2.924017;

    find_min_diff(array_new_2, array_end_pointer_new_2, &pos_new, &cubic_mean_new);

    if (*pos_new != 3)
    {
        err_cnt++;
    }

    printf("%s: %s\n", __func__, err_cnt ? "FAILED" : "OK");
}

void test_move_array_elements()
{
    int err_cnt = 0;

    double *array = NULL;
    double arp = 0xBADBDCAB;
    double *array_end_pointer = &arp;
    double *pos = &arp;

    /* Negative testing */

    if (move_array_elements(array, array_end_pointer, pos) != MEMORY_ALLOC_ERROR)
    {
        err_cnt++;
    }

    double *array_new = &arp;
    double *array_end_pointer_new = NULL;

    if (move_array_elements(array_new, array_end_pointer_new, pos) != MEMORY_ALLOC_ERROR)
    {
        err_cnt++;
    }

    /* Positive testing */

    double array_new_2[] = {1, 2, 3, 4};
    double *array_end_pointer_new_2 = array_new_2 + 4;
    double pos_new = 3;

    move_array_elements(array_new_2, array_end_pointer_new_2, &pos_new);

    if (*(array_new_2 + 3) != 3)
    {
        err_cnt++;
    }

    double array_new_3[] = {1, 1, 1, 1};
    double *array_end_pointer_new_3 = array_new_3 + 4;
    pos_new = 1;

    move_array_elements(array_new_3, array_end_pointer_new_3, &pos_new);

    if (*(array_new_3 + 3) != 1)
    {
        err_cnt++;
    }

    printf("%s: %s\n", __func__, err_cnt ? "FAILED" : "OK");
}

void test_remap_array()
{
    int err_cnt = 0;

    double *array = NULL;
    double arp = 0xCAFEFACE;
    double *array_end_pointer = &arp;
    double *pos = &arp, *cubic_mean = &arp;

    /* Negative testing */

    if (remap_array(array, array_end_pointer, &pos, cubic_mean) != MEMORY_ALLOC_ERROR)
    {
        err_cnt++;
    }

    double *array_new = &arp;
    double *array_end_pointer_new = NULL;
    double *pos_new = &arp;

    if (remap_array(array_new, array_end_pointer_new, &pos_new, cubic_mean) != MEMORY_ALLOC_ERROR)
    {
        err_cnt++;
    }

    /* Positive testing */

    double array_new_2[] = {1, 2, 3, 4};
    double *array_end_pointer_new_2 = array_new_2 + 4;
    double *pos_new_2 = &arp, cubic_mean_new = 2.924017;

    remap_array(array_new_2, array_end_pointer_new_2, &pos_new_2, &cubic_mean_new);

    if (*pos_new_2 != *(array_new_2 + 1))
    {
        err_cnt++;
    }

    double array_new_3[] = {1, 1, 1, 1};
    double *array_end_pointer_new_3 = array_new_3 + 4;
    double *pos_new_3 = &arp;

    remap_array(array_new_3, array_end_pointer_new_3, &pos_new_3, &cubic_mean_new);

    if (*(pos_new_3) != *(array_new_3 + 3))
    {
        err_cnt++;
    }

    printf("%s: %s\n", __func__, err_cnt ? "FAILED" : "OK");
}

void test_change_array_len()
{
    int err_cnt = 0;

    double *array = NULL;
    double arp = 0xDABDABDB;
    double *array_end_pointer = &arp;
    int start_size = 5, change_size = 2;

    /* Negative testing */

    if (change_array_len(&array, &array_end_pointer, &start_size, change_size) != MEMORY_ALLOC_ERROR)
    {
        err_cnt++;
    }

    double *array_new = &arp;
    double *array_end_pointer_new = NULL;

    if (change_array_len(&array_new, &array_end_pointer_new, &start_size, change_size) != MEMORY_ALLOC_ERROR)
    {
        err_cnt++;
    }

    /* Positive testing */

    change_size = 2;

    double *array_new_2 = (double *)calloc(start_size, sizeof(double));
    double *array_end_pointer_new_2 = array_new_2 + start_size;

    change_array_len(&array_new_2, &array_end_pointer_new_2, &start_size, change_size);

    if (array_end_pointer_new_2 - array_new_2 != start_size + change_size)
    {
        err_cnt++;
    }
    free(array_new_2);

    start_size = 6;
    change_size = -3;

    double *array_new_3 = (double *)calloc(start_size, sizeof(double));
    double *array_end_pointer_new_3 = array_new_3 + start_size;

    change_array_len(&array_new_3, &array_end_pointer_new_3, &start_size, change_size);

    if (array_end_pointer_new_3 - array_new_3 != start_size + change_size)
    {
        err_cnt++;
    }
    free(array_new_3);

    printf("%s: %s\n", __func__, err_cnt ? "FAILED" : "OK");
}

void test_insert_to_array()
{
    int err_cnt = 0;

    double *array = NULL;
    double arp = 0xACABACAB;
    double *array_end_pointer = &arp;
    double insertion_num = 5.0;
    int insertion_pos = 1;

    /* Negative testing */

    if (insert_to_array(array, array_end_pointer, &insertion_num, &insertion_pos) != MEMORY_ALLOC_ERROR)
    {
        err_cnt++;
    }

    double *array_new = &arp;
    double *array_end_pointer_new = NULL;

    if (insert_to_array(array_new, array_end_pointer_new, &insertion_num, &insertion_pos) != MEMORY_ALLOC_ERROR)
    {
        err_cnt++;
    }

    /* Positive testing */

    double *array_new_2 = (double *)calloc(5, sizeof(double));
    double *array_end_pointer_new_2 = array_new_2 + 5;

    insert_to_array(array_new_2, array_end_pointer_new_2, &insertion_num, &insertion_pos);

    if (*(array_new_2 + 1) != insertion_num)
    {
        err_cnt++;
    }
    free(array_new_2);

    printf("%s: %s\n", __func__, err_cnt ? "FAILED" : "OK");
}

void test_check_pos_num()
{
    int err_cnt = 0;

    double *array = NULL;
    double arp = 0xBABADADA;
    double *array_end_pointer = &arp;
    int insertion_pos = 12;

    /* Negative testing */

    if (check_pos_num(array, array_end_pointer, &insertion_pos) != MEMORY_ALLOC_ERROR)
    {
        err_cnt++;
    }

    double *array_new = &arp;
    double *array_end_pointer_new = NULL;

    if (check_pos_num(array_new, array_end_pointer_new, &insertion_pos) != MEMORY_ALLOC_ERROR)
    {
        err_cnt++;
    }

    double *array_new_1 = (double *)calloc(5, sizeof(double));
    double *array_end_pointer_new_1 = array_new_1 + 5;

    if (check_pos_num(array_new_1, array_end_pointer_new_1, &insertion_pos) != POS_OUT_OF_RANGE_ERROR)
    {
        err_cnt++;
    }
    free(array_new_1);

    /* Positive testing */

    insertion_pos = 2;

    double *array_new_2 = (double *)calloc(5, sizeof(double));
    double *array_end_pointer_new_2 = array_new_2 + 5;

    if (check_pos_num(array_new_2, array_end_pointer_new_2, &insertion_pos) != OK)
    {
        err_cnt++;
    }
    free(array_new_2);

    printf("%s: %s\n", __func__, err_cnt ? "FAILED" : "OK");
}
