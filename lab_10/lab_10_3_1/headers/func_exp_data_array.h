#ifndef __FUNC_EXP_DATA_ARRAY_H__
#define __FUNC_EXP_DATA_ARRAY_H__

/*
Experiment data array handling utilities' headers.
*/

#include "defines.h"
#include "typedefs.h"

int is_removable(const int day, const int month, const int year);

void swap(exp_t *first, exp_t *second);

int filter_data(exparr_t *const exparr);

int mean_data(exparr_t *const exparr);

void quick_sort(exparr_t *const exparr, int first, int last, int (*comparator)(cmp_data, cmp_data));

int key_sort(exparr_t *const exparr, char *key);

#endif
