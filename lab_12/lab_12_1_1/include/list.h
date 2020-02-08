#ifndef __LIST_H__
#define __LIST_H__

#include <stdio.h>
#include <stdlib.h>

#include "rc.h"
#include "macro.h"

typedef struct
{
    int num;
    int power;
} pcoef_t;

typedef struct node
{
    pcoef_t data;
    struct node *next;
} node_t;

node_t *lcreate(const pcoef_t data);

void linsert(node_t **root, node_t **temp, const pcoef_t data);

int linput(FILE *const stream, node_t **root);

void ltrace(FILE *const stream, node_t *const root);

void ldelete(node_t **root);

#endif