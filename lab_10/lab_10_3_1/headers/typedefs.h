#ifndef __TYPEDEFS_H__
#define __TYPEDEFS_H__

#include "defines.h"

typedef enum months
{
    january = 1,
    february,
    march,
    april,
    may,
    june,
    july,
    august,
    september,
    october,
    november,
    december
} months_t;

typedef struct
{
    char *date;
    char *technician;
    int count;
    double *data;
} exp_t;

typedef struct
{
    exp_t *exparr;
    int cursize;
    int allocsize;
} exparr_t;

typedef struct
{
    char date[MAX_STRING_FIELD_LEN];
    char technician[MAX_STRING_FIELD_LEN];
    int count;
} bufexp_t;

typedef const exp_t *const cmp_data;

#endif