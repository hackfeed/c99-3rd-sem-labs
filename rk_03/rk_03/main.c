#include "include/fileops.h"

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

    text_t *text = fillfile(fin);
    tunique(text);
    tsort(text);
    outfile(stdout, *text);

    sntcs_t *sntcs = fillsntcs(fin, *text);
    outsntcs(stdout, *sntcs);
    rmatches(sntcs, text);
    outfile(stdout, *text);
    outsntcs(stdout, *sntcs);

    return EOK;
}
