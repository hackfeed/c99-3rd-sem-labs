#ifndef __DEFINES_H__
#define __DEFINES_H__

/*
Return codes, integer constants and 
boolean constants definition.
*/

#define OK 0

/*
ds_experiment_data module's return codes.
*/
#define MEMORY_ALLOC_ERROR 1
#define ARRAY_INPUT_ERROR 2
#define NON_POSITIVE_NUMBER_ERROR 3

/*
func_validation module's return codes.
*/
#define DATE_LEN_ERROR 11
#define ALPHA_IN_DATE_ERROR 12
#define MISSED_DOT_ERROR 13
#define INVALID_MONTH_ERROR 14
#define INVALID_DAY_ERROR 15
#define WRONG_DAYS_COUNT 16
#define STRUCT_VALIDATION_ERROR 17
#define INVALID_CHAR_ERROR 18

/*
ds_experiment_data_array module's return codes.
*/
#define INPUT_STATIC_FIELDS_ERROR 21
#define INPUT_DYNAMIC_FIELDS_ERROR 22
#define RECORD_OUTPUT_ERROR 23
#define RECORD_CREATION_ERROR 24
#define ARRAY_EXPANSION_ERROR 25
#define FULL_WIPE_ERROR 26

/*
func_io module's return codes.
*/
#define NUM_INPUT_ERROR 31
#define NEGATIVE_INPUT_ERROR 32
#define STRING_INPUT_ERROR 33
#define STRING_LEN_EXCEED_ERROR 34
#define DATE_VALIDATION_ERROR 35

/*
func_experiment_data module's return codes.
*/
#define INVALID_KEY_ERROR 41

/*
main module's return codes.
*/
#define DATA_CREATION_ERROR 51
#define DATA_INPUT_ERROR 52
#define DATA_FILTER_ERROR 53
#define DATA_MEAN_ERROR 54
#define DATA_SORT_ERROR 55

/*
Macroreplacements.
*/
#define GOT_ARG 1
#define MAX_STRING_FIELD_LEN 256
#define MAX_KEY_SIZE 11
#define END_OF_INPUT 137
#define DATE_LEN 10
#define FALSE 0
#define TRUE 1
#define PASS 2
#define EPS 1e-6

#endif