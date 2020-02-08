#include "include/listops.h"

int main(int argc, char *argv[])
{
    FILE *fin = fopen(argv[1], "r");
    if (!fin)
    {
        return EFILENOTFOUND;
    }
    FILE *fout = fopen("out.txt", "w");
    if (!fout)
    {
        return EFILENOTFOUND;
    }
    
    node_t *root = NULL;
    linput(fin, &root);
    root = reverse(root);
    ltrace(fout, root);
    ldelete(&root);
    fclose(fin);
    fclose(fout);
    
    return EOK;
}
