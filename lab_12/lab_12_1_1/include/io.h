#ifndef __IO_H__
#define __IO_H__

#include <stdio.h>
#include <string.h>

#include "rc.h"
#include "macro.h"

int dinput(FILE *const stream, double *const num);

int sinput(FILE *const stream, char *str);

#endif