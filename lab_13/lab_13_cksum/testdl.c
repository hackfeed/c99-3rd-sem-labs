#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <dlfcn.h>

void test_help()
{
    void *handle = dlopen("libcksum.so", RTLD_LAZY);
    uint32_t (*cksum)(FILE *, const char *);
    char *filename = "cksum.c";
    FILE *fp = fopen(filename, "rb");
    cksum = dlsym(handle, "cksum");
    (*cksum)(fp, filename);
    system("cksum --help");
    fclose(fp);
    dlclose(handle);
}

void test_version()
{
    void *handle = dlopen("libcksum.so", RTLD_LAZY);
    uint32_t (*cksum)(FILE *, const char *);
    char *filename = "cksum.c";
    FILE *fp = fopen(filename, "rb");
    cksum = dlsym(handle, "cksum");
    (*cksum)(fp, filename);
    system("cksum --version");
    fclose(fp);
    dlclose(handle);
}

void test_file()
{
    void *handle = dlopen("libcksum.so", RTLD_LAZY);
    uint32_t (*cksum)(FILE *, const char *);
    char *filename = "cksum.c";
    FILE *fp = fopen(filename, "rb");
    cksum = dlsym(handle, "cksum");
    (*cksum)(fp, filename);
    system("cksum cksum.c");
    fclose(fp);
    dlclose(handle);
}

void test_stdin()
{
    void *handle = dlopen("libcksum.so", RTLD_LAZY);
    uint32_t (*cksum)(FILE *, const char *);
    char *filename = "stdin";
    freopen("fake_input.txt", "rb", stdin);
    cksum = dlsym(handle, "cksum");
    (*cksum)(stdin, filename);
    system("cksum < fake_input.txt");
    dlclose(handle);
}

int main()
{
    printf("TEST DYNAMIC LOAD\n\n");
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