#include <stdio.h>

#include "headers/defines.h"
#include "headers/typedefs.h"
#include "headers/ds_exp_data_array.h"
#include "headers/func_io.h"
#include "headers/func_exp_data_array.h"
#include "headers/func_comparators.h"

int main()
{
    exparr_t data;
    char key[MAX_KEY_SIZE];

    if (create_array(&data))
    {
        return DATA_CREATION_ERROR;
    }

    if (input_array(&data, stdin))
    {
        return DATA_INPUT_ERROR;
    }

    if (filter_data(&data))
    {
        delete_array(&data, data.cursize);

        return DATA_FILTER_ERROR;
    }

    if (mean_data(&data))
    {
        delete_array(&data, data.cursize);

        return DATA_MEAN_ERROR;
    }
    
    if (input_string(key, stdin))
    {
        delete_array(&data, data.cursize);

        return STRING_INPUT_ERROR;
    }

    if (key_sort(&data, key))
    {
        delete_array(&data, data.cursize);

        return DATA_SORT_ERROR;
    }

    FILE *out = fopen("results.txt", "w");
    output_array(&data, out);
    fclose(out);
    delete_array(&data, data.cursize);

    return OK;
}