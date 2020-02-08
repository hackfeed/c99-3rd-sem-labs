#include <stdio.h>
#include <string.h>
#include <limits.h>

#include "my_string.h"

#define OK 0
#define FAIL 1

#define BUFSIZE 255

int snprintf_cmp(const int lib_out, const int my_out, char *lib_str, char *my_str)
{
    if (lib_out != my_out || strcmp(lib_str, my_str))
    {
        return FAIL; 
    }

    return OK;
}

void test_s_spec()
{
    int err_cnt = 0;

    char lib_buf[BUFSIZE];
    char my_buf[BUFSIZE];
    int lib_res = snprintf(lib_buf, 5, "%s", "flex");
    int my_res = my_snprintf(my_buf, 5, "%s", "flex");

    err_cnt += snprintf_cmp(lib_res, my_res, lib_buf, my_buf);

    printf("%s: %s\n", __func__, err_cnt ? "FAILED" : "OK");
}

void test_c_spec()
{
    int err_cnt = 0;

    char lib_buf[BUFSIZE];
    char my_buf[BUFSIZE];
    int lib_res = snprintf(lib_buf, 100, "%c", 'c');
    int my_res = my_snprintf(my_buf, 100, "%c", 'c');

    err_cnt += snprintf_cmp(lib_res, my_res, lib_buf, my_buf);

    printf("%s: %s\n", __func__, err_cnt ? "FAILED" : "OK");
}

void test_x_spec()
{
    int err_cnt = 0;

    char lib_buf[BUFSIZE];
    char my_buf[BUFSIZE];
    int lib_res = snprintf(lib_buf, 100, "%x", 256);
    int my_res = my_snprintf(my_buf, 100, "%x", 256);

    err_cnt += snprintf_cmp(lib_res, my_res, lib_buf, my_buf);

    printf("%s: %s\n", __func__, err_cnt ? "FAILED" : "OK");
}

void test_lx_spec()
{
    int err_cnt = 0;

    char lib_buf[BUFSIZE];
    char my_buf[BUFSIZE];
    int lib_res = snprintf(lib_buf, 100, "%lx", ULONG_MAX);
    int my_res = my_snprintf(my_buf, 100, "%lx", ULONG_MAX);

    err_cnt += snprintf_cmp(lib_res, my_res, lib_buf, my_buf);

    printf("%s: %s\n", __func__, err_cnt ? "FAILED" : "OK");
}

void test_llx_spec()
{
    int err_cnt = 0;

    char lib_buf[BUFSIZE];
    char my_buf[BUFSIZE];
    int lib_res = snprintf(lib_buf, 100, "%llx", ULLONG_MAX);
    int my_res = my_snprintf(my_buf, 100, "%llx", ULLONG_MAX);

    err_cnt += snprintf_cmp(lib_res, my_res, lib_buf, my_buf);

    printf("%s: %s\n", __func__, err_cnt ? "FAILED" : "OK");
}

void test_null_buf()
{
    int err_cnt = 0;

    int lib_res = snprintf(NULL, 0, "%llx", ULLONG_MAX);
    int my_res = my_snprintf(NULL, 0, "%llx", ULLONG_MAX);

    if (lib_res != my_res)
    {
        err_cnt++;
    }

    printf("%s: %s\n", __func__, err_cnt ? "FAILED" : "OK");
}

void test_zero_size()
{
    int err_cnt = 0;

    char lib_buf[BUFSIZE] = { 0 };
    char my_buf[BUFSIZE] = { 0 };
    int lib_res = snprintf(lib_buf, 0, "flex %llx", ULLONG_MAX);
    int my_res = my_snprintf(my_buf, 0, "flex %llx", ULLONG_MAX);

    err_cnt += snprintf_cmp(lib_res, my_res, lib_buf, my_buf);

    printf("%s: %s\n", __func__, err_cnt ? "FAILED" : "OK");
}

void test_only_size()
{
    int err_cnt = 0;

    char lib_buf[BUFSIZE] = { 0 };
    char my_buf[BUFSIZE] = { 0 };
    int lib_res = snprintf(lib_buf, 1, "flex %llx", ULLONG_MAX);
    int my_res = my_snprintf(my_buf, 1, "flex %llx", ULLONG_MAX);

    err_cnt += snprintf_cmp(lib_res, my_res, lib_buf, my_buf);

    printf("%s: %s\n", __func__, err_cnt ? "FAILED" : "OK");
}

void test_empty_fmt()
{
    int err_cnt = 0;

    char lib_buf[BUFSIZE];
    char my_buf[BUFSIZE];
    int lib_res = snprintf(lib_buf, 10, "", ULLONG_MAX);
    int my_res = my_snprintf(my_buf, 10, "", ULLONG_MAX);

    err_cnt += snprintf_cmp(lib_res, my_res, lib_buf, my_buf);

    printf("%s: %s\n", __func__, err_cnt ? "FAILED" : "OK");
}

void test_str_less_size()
{
    int err_cnt = 0;

    char lib_buf[BUFSIZE];
    char my_buf[BUFSIZE];
    int lib_res = snprintf(lib_buf, 100, "%llx", ULLONG_MAX);
    int my_res = my_snprintf(my_buf, 100, "%llx", ULLONG_MAX);

    err_cnt += snprintf_cmp(lib_res, my_res, lib_buf, my_buf);

    printf("%s: %s\n", __func__, err_cnt ? "FAILED" : "OK");
}

void test_str_great_size()
{
    int err_cnt = 0;

    char lib_buf[BUFSIZE];
    char my_buf[BUFSIZE];
    int lib_res = snprintf(lib_buf, 5, "%llx", ULLONG_MAX);
    int my_res = my_snprintf(my_buf, 5, "%llx", ULLONG_MAX);

    err_cnt += snprintf_cmp(lib_res, my_res, lib_buf, my_buf);

    printf("%s: %s\n", __func__, err_cnt ? "FAILED" : "OK");
}

int main()
{
    test_s_spec();
    test_c_spec();
    test_x_spec();
    test_lx_spec();
    test_llx_spec();
    test_null_buf();
    test_zero_size();
    test_empty_fmt();
    test_str_less_size();
    test_str_great_size();

    return OK;
}