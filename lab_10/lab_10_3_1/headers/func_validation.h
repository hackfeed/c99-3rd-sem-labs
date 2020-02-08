#ifndef __FUNC_VALIDATION_H__
#define __FUNC_VALIDATION_H__

#include "typedefs.h"

int is_leap(const int year);

int validate_struct(char *date);

void parse_nums(char *date, int *const day, int *const month, int *const year);

int validate_nums(const int day, const int month, const int year);

int validate(char *date);

int is_alphas(char *string);

#endif