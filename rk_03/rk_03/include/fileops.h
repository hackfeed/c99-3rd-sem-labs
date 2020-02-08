#ifndef __FILEOPS_H__
#define __FILEOPS_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "include/rc.h"
#include "include/macro.h"

typedef struct
{
    char **arr;
    int size;
} text_t;

typedef struct
{
    char **arr;
    int size;
    int unsize;
    int *bin;
} sntc_t;

typedef struct
{
    sntc_t *sntcs;
    int size;
} sntcs_t;

text_t *fillfile(FILE *stream);

void tunique(text_t *text);

void tsort(text_t *text);

sntcs_t *fillsntcs(FILE *stream, text_t text);

void rmatches(sntcs_t *sentences, text_t *text);

void outfile(FILE *stream, text_t text);

void outsntcs(FILE *stream, sntcs_t sentences);

#endif