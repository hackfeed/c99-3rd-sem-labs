/*
exparr data array handling utilities.
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "headers/defines.h"
#include "headers/typedefs.h"
#include "headers/func_validation.h"
#include "headers/ds_exp_data.h"
#include "headers/func_comparators.h"

/*
Check if record is going to be removed.

Input data:
* const int day, const int month, const int year - date components.

Output data:
* Sign: TRUE or FALSE.
*/
int is_removable(const int day, const int month, const int year)
{
    if (year < 1993)
    {
        return TRUE;
    }
    else
    {
        if (year == 1993 && day + 31 * (month - 1) <= 32)
        {
            return TRUE;
        }
    }

    return FALSE;
}

/*
Helper swap function.

Input data:
* exp_t *first, exp_t *second - data to be swapped.
*/
void swap(exp_t *first, exp_t *second)
{
    exp_t tmp = *first; 
    *first = *second;
    *second = tmp;
}

/*
Filter data with record deletions which are earlier than February 2nd 1993.

Input data:
* exparr_t *const exparr - exparr to be filtered.

Output data:
* Return code: OK, FULL_WIPE_ERROR or MEMORY_ALLOC_ERROR.
*/
int filter_data(exparr_t *const exparr)
{
    int deletions = 0;
    int iter = exparr->cursize;

    for (int rec = 0; rec < iter; ++rec)
    {
        if (!(exparr->exparr + rec))
        {
            return MEMORY_ALLOC_ERROR;
        }

        char *rec_date = (exparr->exparr + rec)->date;
        int day, month, year;

        parse_nums(rec_date, &day, &month, &year);
        
        if (is_removable(day, month, year))
        {
            for (int swp = rec; swp < iter - 1; ++swp)
            { 
                swap(exparr->exparr + swp, exparr->exparr + swp + 1);
            }
            delete_data(exparr->exparr + iter - 1);

            iter--; 
            rec--;
            deletions++;
            exparr->cursize--;
        }
    }

    if (!exparr->cursize)
    {
        return FULL_WIPE_ERROR;
    }

    exp_t *new_experiment = (exp_t *)realloc(exparr->exparr, exparr->cursize * sizeof(exp_t));
    
    if (!new_experiment)
    {
       return MEMORY_ALLOC_ERROR;
    }

    exparr->exparr = new_experiment;
    new_experiment = NULL;
    exparr->allocsize = exparr->cursize;
    
    return OK;
}

/*
Replace all data with mean value.

Input data:
* exparr_t *const exparr - exparr array.

Output data:
* Return code: OK or MEMORY_ALLOC_ERROR.
*/
int mean_data(exparr_t *const exparr)
{
    for (int rec = 0; rec < exparr->cursize; ++rec)
    {
        if (!(exparr->exparr + rec))
        {
            return MEMORY_ALLOC_ERROR;
        }
        
        double measure_sum = 0;

        for (int measure = 0; measure < (exparr->exparr + rec)->count; ++measure)
        {
            measure_sum += *((exparr->exparr + rec)->data + measure);
        }

        *((exparr->exparr + rec)->data) = measure_sum / (exparr->exparr + rec)->count;

        double *new_data = (double *)realloc((exparr->exparr + rec)->data, sizeof(double));

        if (!new_data)
        {
            return MEMORY_ALLOC_ERROR;
        }
        else
        {
            (exparr->exparr + rec)->data = new_data;
            new_data = NULL;

            (exparr->exparr + rec)->count = 1;
        }
    }

    return OK;
}

/*
Sort exparr using comparator.

Input data:
* exparr_t *const exparr - exparr to be sorted.
* int first, int last - sort range.
* int (*comparator)(const exp_t *const, const exp_t *const) - comparator.
*/
void quick_sort(exparr_t *const exparr, int first, int last, 
int (*comparator)(cmp_data, cmp_data))
{
    int i, j;
    exp_t pivot;

    if (first < last)
    {
        pivot = *(exparr->exparr + (first + last) / 2);
        i = first;
        j = last;

        while (i <= j)
        {
            while (comparator(exparr->exparr + i, &pivot) == FALSE)
            {
                i++;
            }

            while (comparator(exparr->exparr + j, &pivot) == TRUE)
            {
                j--;
            }

            if (i <= j)
            {
                if (comparator(exparr->exparr + i, exparr->exparr + j) == TRUE)
                {
                    swap(exparr->exparr + i, exparr->exparr + j);
                }

                i++;
                j--;
            }
        } 

        quick_sort(exparr, first, j, comparator);
        quick_sort(exparr, i, last, comparator);
    }
}

/*
Sort elements with comparator depends on key.

Input data:
* exparr_t *const exparr - exparr to be sorted.
* char *key - sort key.

Output data:
* Return code: OK or INVALID_KEY_ERROR.
*/
int key_sort(exparr_t *const exparr, char *key)
{
    if (!exparr->exparr)
    {
        return MEMORY_ALLOC_ERROR;
    }

    if (!strcmp(key, "DATE"))
    {
        quick_sort(exparr, 0, exparr->cursize - 1, compare_date);

        return OK;
    }

    if (!strcmp(key, "TECHNICIAN"))
    {
        quick_sort(exparr, 0, exparr->cursize - 1, compare_technician);

        return OK;
    }

    if (!strcmp(key, "DATA"))
    {
        quick_sort(exparr, 0, exparr->cursize - 1, compare_measure);

        return OK;
    }

    return INVALID_KEY_ERROR;
}