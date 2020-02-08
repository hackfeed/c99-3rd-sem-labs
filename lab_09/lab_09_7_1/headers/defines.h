#ifndef __DEFINES_H__
#define __DEFINES_H__

/*
Return codes, integer constants and 
boolean constants definition.
*/

#define OK 0

/*
ds_dynamic_matrix module's return codes.
*/
#define MEMORY_ALLOC_ERROR 1
#define MATRIX_INPUT_ERROR 2

/*
func_io module's return codes.
*/
#define NUM_INPUT_ERROR -5
#define NEGATIVE_INPUT_ERROR -6
#define PARAM_INPUT_ERROR -7

/*
func_matrix module's return codes.
*/
#define NEW_ALLOC_ERROR 3
#define NEW_ROW_CREATION_ERROR 4
#define NEW_COLUMN_CREATION_ERROR 5
#define SQUARING_BY_DELETION_ERROR 6
#define SQUARING_BY_EXPANSION_ERROR 7

/*
main module's return codes.
*/
#define MATRIX_CREATION_ERROR 8
#define MATRIX_SQUARING_ERROR 9
#define POWER_INPUT_ERROR 10
#define MATRIX_POW_ERROR 11
#define MATRIX_MULTIPLICATION_ERROR 12

/*
Macroreplacements.
*/
#define GOT_ARG 1

#define BY_ROWS 0
#define BY_COLUMNS 1

/*
Colored printf ouptut.
*/
#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_RESET "\x1b[0m"

#endif