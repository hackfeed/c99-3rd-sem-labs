#include "include/listops.h"

/*
Find polynom's value with inputted x.

Input data:
* FILE *const stream_in - stream to read from.
* FILE *const stream - stream to write to.

Output data:
* Return code - EOK or EINPUTERROR.
*/
int val(FILE *const stream_in, FILE *const stream_out)
{
    node_t *root = NULL;
    double num;
    double value = 0;
    int ec;

    ec = linput(stream_in, &root);
    if (ec)
    {
        ldelete(&root);
        return ec;
    }
    ec = dinput(stream_in, &num);
    if (ec)
    {
        ldelete(&root);
        return ec;
    }

    node_t *temp = root;
    while (temp)
    {
        value += temp->data.num * powf(num, temp->data.power);
        temp = temp->next;
    }

    fprintf(stream_out, "%lf\n", value);
    ldelete(&root);

    return EOK;
}

/*
Find polynom's derivative.

Input data:
* FILE *const stream_in - stream to read from.
* FILE *const stream - stream to write to.

Output data:
* Return code - EOK or EINPUTERROR.
*/
int ddx(FILE *const stream_in, FILE *const stream_out)
{
    node_t *root = NULL;
    int ec;

    ec = linput(stream_in, &root);
    if (ec)
    {
        ldelete(&root);
        return ec;
    }

    node_t *temp = root;
    if (temp->data.power == 0)
    {
        temp->data.num = 0;
    }
    while (temp->next)
    {
        temp->data.num = temp->data.num * temp->data.power;
        temp->data.power--;
        if (temp->next->next)
        {
            temp = temp->next;
        }
        else
        {
            free(temp->next);
            temp->next = NULL;
        }
    }

    ltrace(stream_out, root);
    ldelete(&root);

    return EOK;
}

/*
Find two polynoms' sum.

Input data:
* FILE *const stream_in - stream to read from.
* FILE *const stream - stream to write to.

Output data:
* Return code - EOK or EINPUTERROR.
*/
int sum(FILE *const stream_in, FILE *const stream_out)
{
    node_t *froot = NULL, *froot_copy;
    node_t *sroot = NULL, *sroot_copy;
    int ec;

    ec = linput(stream_in, &froot);
    if (ec)
    {
        ldelete(&froot);
        return ec;
    }
    ec = linput(stream_in, &sroot);
    if (ec)
    {
        ldelete(&froot);
        ldelete(&sroot);
        return ec;
    }

    froot_copy = froot;
    sroot_copy = sroot;

    pcoef_t data;
    node_t *res = NULL, *temp = NULL;
    while (froot && sroot)
    {
        if (froot->data.power == sroot->data.power)
        {
            data.num = froot->data.num + sroot->data.num;
            data.power = froot->data.power;
            linsert(&res, &temp, data);
            froot = froot->next;
            sroot = sroot->next;
            continue;
        }
        if (froot->data.power > sroot->data.power)
        {
            data.num = froot->data.num;
            data.power = froot->data.power;
            linsert(&res, &temp, data);
            froot = froot->next;
            continue;
        }
        if (froot->data.power < sroot->data.power)
        {
            data.num = sroot->data.num;
            data.power = sroot->data.power;
            linsert(&res, &temp, data);
            sroot = sroot->next;
            continue;
        }
    }
    while (froot)
    {
        data.num = froot->data.num;
        data.power = froot->data.power;
        linsert(&res, &temp, data);
        froot = froot->next;
    }
    while (sroot)
    {
        data.num = sroot->data.num;
        data.power = sroot->data.power;
        linsert(&res, &temp, data);
        sroot = sroot->next;
    }

    ltrace(stream_out, res);

    ldelete(&res);
    ldelete(&froot_copy);
    ldelete(&sroot_copy);

    return EOK;
}

/*
Split two polynoms' in polynoms with only even or only odd powers.

Input data:
* FILE *const stream_in - stream to read from.
* FILE *const stream - stream to write to.

Output data:
* Return code - EOK or EINPUTERROR.
*/
int dvd(FILE *const stream_in, FILE *const stream_out)
{
    node_t *root = NULL, *root_copy;
    int ec;

    ec = linput(stream_in, &root);
    if (ec)
    {
        ldelete(&root);
        return ec;
    }
    root_copy = root;

    node_t *root_even = NULL, *temp_even = NULL;
    node_t *root_odd = NULL, *temp_odd = NULL;
    while (root)
    {
        if (root->data.power % 2)
        {
            linsert(&root_odd, &temp_odd, root->data);
        }
        else
        {
            linsert(&root_even, &temp_even, root->data);
        }
        root = root->next;
    }

    if (!root_odd)
    {
        pcoef_t data = { .num = 0, .power = 0 };
        linsert(&root_odd, &temp_odd, data);
    }
    if (!root_even)
    {
        pcoef_t data = { .num = 0, .power = 0 };
        linsert(&root_even, &temp_even, data);
    }

    ltrace(stream_out, root_even);
    ltrace(stream_out, root_odd);

    ldelete(&root_copy);
    ldelete(&root_even);
    ldelete(&root_odd);

    return EOK;
}

/*
Run the party.

Input data:
* FILE *const stream_in - stream to read from.
* FILE *const stream - stream to write to.

Output data:
* Return code - EOK, EINPUTERROR or ENOMATCH.
*/
int run_cmd(FILE *const stream_in, FILE *const stream_out)
{
    char cmd[SIZE];

    if (sinput(stream_in, cmd) != EOK)
    {
        return EINPUTERROR;
    }
    if (strcmp(cmd, "val") == GOT_MATCH)
    {
        return val(stream_in, stream_out);
    }
    if (strcmp(cmd, "ddx") == GOT_MATCH)
    {
        return ddx(stream_in, stream_out);
    }
    if (strcmp(cmd, "sum") == GOT_MATCH)
    {
        return sum(stream_in, stream_out);
    }
    if (strcmp(cmd, "dvd") == GOT_MATCH)
    {
        return dvd(stream_in, stream_out);
    }

    return ENOMATCH;
}