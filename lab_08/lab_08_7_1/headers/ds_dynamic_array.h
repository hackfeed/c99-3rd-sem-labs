/*
CDIO headers.
*/

int create_dynamic_array(double **array, const int *const elements_amount, double **array_end_pointer);

int delete_dynamic_array(double *array);

int input_dynamic_array(double *const array, const double *const array_end_pointer);

int output_dynamic_array(double *const array, const double *const array_end_pointer);