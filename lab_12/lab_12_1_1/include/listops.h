#ifndef __LISTOPS_H__
#define __LISTOPS_H__

#include <math.h>

#include "list.h"
#include "io.h"

int val(FILE *const stream_in, FILE *const stream_out);

int ddx(FILE *const stream_in, FILE *const stream_out);

int sum(FILE *const stream_in, FILE *const stream_out);

int dvd(FILE *const stream_in, FILE *const stream_out);

int run_cmd(FILE *const stream_in, FILE *const stream_out);

#endif