/*
Comparators for experiment_t data structure.
*/

#include <string.h>

#include "headers/defines.h"
#include "headers/typedefs.h"
#include "headers/func_validation.h"

int compare_date(const exp_t *const first, const exp_t *const second)
{
    int dayf, monthf, yearf;
    int days, months, years;

    parse_nums(first->date, &dayf, &monthf, &yearf);
    parse_nums(second->date, &days, &months, &years);

    int dayf_overall = yearf * 400 + (monthf - 1) * 32 + dayf;
    int days_overall = years * 400 + (months - 1) * 32 + days;

    if (dayf_overall > days_overall)
    {
        return TRUE;
    }
    else
    {
        if (dayf_overall < days_overall)
        {
            return FALSE;
        }
    }

    return PASS;
}

int compare_technician(const exp_t *const first, const exp_t *const second)
{
    int compare_rate = strcmp(first->technician, second->technician);
    
    if (compare_rate > 0)
    {
        return TRUE;
    }
    else
    {
        if (compare_rate < 0)
        {
            return FALSE;
        }
    }

    return PASS;
}

int compare_measure(const exp_t *const first, const exp_t *const second)
{
    if (*first->data - *second->data > EPS)
    {
        return TRUE;
    }
    else
    {
        if (*second->data - *first->data > EPS)
        {
            return FALSE;
        }
    }

    return PASS;
}