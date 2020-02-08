#ifndef __LIST_H__
#define __LIST_H__

#include <stdio.h>
#include <stdlib.h>

#include "rc.h"
#include "macro.h"

typedef struct node
{
    char data;
    struct node *next;
} node_t;

node_t *lcreate(const char data);

void linsert(node_t **root, node_t **temp, const char data);

void linsert_front(node_t **root, const char data);

int linput(FILE *const stream, node_t **root);

void ltrace(FILE *const stream, node_t *const root);

void ldelete(node_t **root);

#endif