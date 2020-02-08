/*
Date validator for bufexperiment_t.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "../headers/defines.h"
#include "../headers/typedefs.h"

/*
Check if year is leap.

Inout data:
* const int year - year to be checked.

Output data:
* TRUE if year is leap, FALSE - otherwise.
*/
int is_leap(const int year)
{
    if (year % 4)
    {
        return FALSE;
    }

    if (!(year % 100) && year % 400)
    {
        return FALSE;
    }

    return TRUE;
}

/*
Validate string struct (8 symbols, dot positions).

Input data:
* char *date - string to be checked.

Output data:
* Return code: DATE_LEN_ERROR, ALPHA_IN_DATE_ERROR, MISSED_DOT_ERROR or OK.
*/
int validate_struct(char *date)
{
    int date_len = strlen(date);

    if (date_len != DATE_LEN)
    {
        return DATE_LEN_ERROR;
    }

    for (int sym = 0; sym < date_len; ++sym)
    {
        if (sym != 2 && sym != 5 && !isdigit(date[sym]))
        {
            return ALPHA_IN_DATE_ERROR;
        }

        if ((sym == 2 || sym == 5) && date[sym] != '.')
        {
            return MISSED_DOT_ERROR;
        }
    }

    return OK;
}

/*
Parse date components: day, month, year.

Input data:
* char *date - string to be parsed.
* int *const day, int *const month, int *const year - date components.
*/
void parse_nums(char *date, int *const day, int *const month, int *const year)
{
    char c_day[3];
    char c_month[3];
    char c_year[5];
    int date_len = strlen(date);

    int sym = 0;
    for (; sym < 2; ++sym)
    {
        c_day[sym] = date[sym];
    }
    c_day[sym] = '\0';
    sym++;

    for (; sym < 5; ++sym)
    {
        c_month[sym - 3] = date[sym];
    }
    c_month[sym - 3] = '\0';
    sym++;

    for (; sym < date_len; ++sym)
    {
        c_year[sym - 6] = date[sym];
    }
    c_year[sym - 6] = '\0';

    *day = atoi(c_day);
    *month = atoi(c_month);
    *year = atoi(c_year);
}

/*
Validate parsed date components.

Input data:
* const int day, const int month, const int year - components to be validated.

Output data:
* Return code: INVALID_MONTH_ERROR, INVALID_DAY_ERROR, WRONG_DAYS_COUNT or OK.
*/
int validate_nums(const int day, const int month, const int year)
{
    if (month < january || month > december)
    {
        return INVALID_MONTH_ERROR;
    }

    if (day < 1 || day > 31)
    {
        return INVALID_DAY_ERROR;
    }

    int day_30[] = { april, june, september, november };
    int day_30_len = 4;

    for (int mon = 0; mon < day_30_len; ++mon)
    {
        if (month == day_30[mon] && day > 30)
        {
            return WRONG_DAYS_COUNT;
        }
    }

    if (month == february)
    {
        if ((day > 28 && !is_leap(year)) || \
            (day > 29 && is_leap(year)))
        {
            return WRONG_DAYS_COUNT;
        }
    }

    return OK;
}

/*
AIO validation module.

Input data:
* char *date - date to be validated.

Output data:
* Return code: STRUCT_VALIDATION_ERROR, DATE_VALIDATION_ERROR or OK.
*/
int validate(char *date)
{
    if (validate_struct(date))
    {
        return STRUCT_VALIDATION_ERROR;
    }

    int day, month, year;
    parse_nums(date, &day, &month, &year);

    if (validate_nums(day, month, year))
    {
        return DATE_VALIDATION_ERROR;
    }

    return OK;
}

/*
Validate string to be alpha-containing only.

Input data:
* char *string - string to be checked.

Output data:
* Return code: OK or INVALID_CHAR_ERROR.
*/
int is_alphas(char *string)
{
    int len = strlen(string);

    for (int ch = 0; ch < len; ++ch)
    {
        if (!isalpha(string[ch]))
        {
            return INVALID_CHAR_ERROR;
        }
    }

    return OK;
}