#include <stdio.h>
#include <stdlib.h>

#include "cksum.h"

void test_help()
{
    char *filename = "cksum.c";
    FILE *fp = fopen(filename, "rb");
    cksum(fp, "--help");
    system("cksum --help");
    fclose(fp);
}

void test_version()
{
    char *filename = "cksum.c";
    FILE *fp = fopen(filename, "rb");
    cksum(fp, "--version");
    system("cksum --version");
    fclose(fp);
}

void test_file()
{
    char *filename = "cksum.c";
    FILE *fp = fopen(filename, "rb");
    cksum(fp, filename);
    system("cksum cksum.c");
    fclose(fp);
}

void test_stdin()
{
    char *filename = "stdin";
    freopen("fake_input.txt", "rb", stdin);
    cksum(stdin, filename);
    system("cksum < fake_input.txt");
}

int main()
{
    printf("TEST COMPOSE\n\n");
    printf("\nTEST --help OPTION\n\n");
    test_help();
    printf("\nTEST --version OPTION\n\n");
    test_version();
    printf("\nTEST FILE OPTION\n\n");
    test_file();
    printf("\nTEST STDIN OPTION\n\n");
    test_stdin();

    return 0;
}