#include "include/fileops.h"

text_t *fillfile(FILE *stream)
{
    fseek(stream, 0, SEEK_SET);

    char tmp[STRLEN];

    text_t *text = (text_t *)malloc(sizeof(text_t));
    text->arr = (char **)malloc(sizeof(char *));
    text->size = 0;

    while (fscanf(stream, "%s", tmp) != EOF)
    {
        text->arr = (char **)realloc(text->arr, sizeof(char *) * (text->size + 1));
        text->arr[text->size] = (char *)malloc(strlen(tmp) + 1);
        strcpy(text->arr[text->size], tmp);
        text->size++;
    }

    return text;
}

void tunique(text_t *text)
{
    for (int i = 0; i < text->size - 1; ++i)
    {
        for (int j = i + 1; j < text->size; ++j)
        {
            if (!strcmp(text->arr[i], text->arr[j]))
            {
                for (int k = j; k < text->size - 1; ++k)
                {
                    text->arr[k] = (char *)realloc(text->arr[k], strlen(text->arr[k + 1]) + 1);
                    strcpy(text->arr[k], text->arr[k + 1]);
                }
                j--;
                text->size--;
                text->arr = (char **)realloc(text->arr, sizeof(char *) * text->size);
            }
        }
    }
}

void tsort(text_t *text)
{
    for (int i = 0; i < text->size - 1; ++i)
    {
        for (int j = i + 1; j < text->size; ++j)
        {
            if (strcmp(text->arr[i], text->arr[j]) > 0)
            {
                int i_len = strlen(text->arr[i]);
                char tmp[STRLEN];
                strcpy(tmp, text->arr[i]);
                text->arr[i] = (char *)realloc(text->arr[i], strlen(text->arr[j]) + 1);
                strcpy(text->arr[i], text->arr[j]);
                text->arr[j] = (char *)realloc(text->arr[j], i_len + 1);
                strcpy(text->arr[j], tmp);
            }
        }
    }
}

sntcs_t *fillsntcs(FILE *stream, text_t text)
{
    fseek(stream, 0, SEEK_SET);

    char tmp[STRLEN];
    char *token;

    sntcs_t *sentences = (sntcs_t *)malloc(sizeof(sntcs_t));
    sentences->sntcs = (sntc_t *)malloc(sizeof(sntc_t));
    sentences->size = 0;

    while (fgets(tmp, STRLEN, stream))
    {
        sentences->sntcs = (sntc_t *)realloc(sentences->sntcs, sizeof(sntc_t) * (sentences->size + 1));
        sentences->sntcs[sentences->size].arr = (char **)malloc(sizeof(char *));
        sentences->sntcs[sentences->size].size = 0;
        sentences->sntcs[sentences->size].unsize = text.size;
        sentences->sntcs[sentences->size].bin = (int *)calloc(text.size, sizeof(int));
        token = strtok(tmp, " ");
        while (token)
        {
            if (token[strlen(token) - 1] == '\n')
            {
                token[strlen(token) - 1] = '\0';
            }
            for (int i = 0; i < text.size; ++i)
            {
                if (!strcmp(token, text.arr[i]))
                {
                    sentences->sntcs[sentences->size].bin[i] = 1;
                }
            }
            sentences->sntcs[sentences->size].arr =
                (char **)realloc(sentences->sntcs[sentences->size].arr, sizeof(char *) * (sentences->sntcs[sentences->size].size + 1));
            sentences->sntcs[sentences->size].arr[sentences->sntcs[sentences->size].size] = (char *)malloc(strlen(token) + 1);
            strcpy(sentences->sntcs[sentences->size].arr[sentences->sntcs[sentences->size].size], token);
            sentences->sntcs[sentences->size].size++;
            token = strtok(NULL, " ");
        }
        sentences->size++;
    }

    return sentences;
}

void rmatches(sntcs_t *sentences, text_t *text)
{
    int ind = 0;

    while (ind < text->size)
    {
        int matches = 0;

        for (int i = 0; i < sentences->size; ++i)
        {
            if (sentences->sntcs[i].bin[ind] == 1)
            {
                matches++;
            }
        }

        if (matches == sentences->size)
        {
            for (int i = 0; i < sentences->size; ++i)
            {
                sentences->sntcs[i].bin[ind] = 0;

                for (int j = 0; j < sentences->sntcs[i].size; ++j)
                {
                    if (!strcmp(text->arr[ind], sentences->sntcs[i].arr[j]))
                    {
                        for (int k = j; k < sentences->sntcs[i].size - 1; ++k)
                        {
                            sentences->sntcs[i].arr[k] =
                                (char *)realloc(sentences->sntcs[i].arr[k], strlen(sentences->sntcs[i].arr[k + 1]) + 1);
                            strcpy(sentences->sntcs[i].arr[k], sentences->sntcs[i].arr[k + 1]);
                        }
                        j--;
                        sentences->sntcs[i].size--;
                        sentences->sntcs[i].arr = (char **)realloc(sentences->sntcs[i].arr, sizeof(char *) * sentences->sntcs[i].size);
                    }
                }
            }

            for (int i = ind; i < text->size - 1; ++i)
            {
                for (int j = i; j < text->size; ++j)
                {
                    text->arr[j] = (char *)realloc(text->arr[j], strlen(text->arr[j + 1]) + 1);
                    strcpy(text->arr[j], text->arr[j + 1]);
                }
                i--;
                text->size--;
                text->arr = (char **)realloc(text->arr, sizeof(char *) * text->size);
            }
        }

        ind++;
    }
}

void outfile(FILE *stream, text_t text)
{
    for (int i = 0; i < text.size; ++i)
    {
        fprintf(stream, "%s ", text.arr[i]);
    }
    fprintf(stream, "\n");
}

void outsntcs(FILE *stream, sntcs_t sentences)
{
    for (int i = 0; i < sentences.size; ++i)
    {
        for (int j = 0; j < sentences.sntcs[i].unsize; ++j)
        {
            fprintf(stream, "%d ", sentences.sntcs[i].bin[j]);
        }
        fprintf(stream, "\n");
    }
}