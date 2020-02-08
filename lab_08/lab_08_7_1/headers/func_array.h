/*
Array changing interface headers.
*/

int find_min_diff(double *const array, const double *const array_end_pointer, double **pos, const double *const cubic_mean);

void swap(double *first, double *second);

int move_array_elements(double *const array, const double *const array_end_pointer, double *const pos);

int remap_array(double *const array, const double *const array_end_pointer, double **pos, const double *const cubic_mean);

int change_array_len(double **array, double **array_end_pointer, const int *const start_size, const int change_size);

int insert_to_array(double *const array, double *const array_end_pointer, const double *const insertion_num, const int *const insertion_pos);

int check_pos_num(double *const array, double *const array_end_pointer, const int *const insertion_pos);