#include "include/list.h"

/*
List node creation.

Input data:
* const pcoef_t data - polynominal coefficient data to write to node.

Output data:
* Pointer to created node - node or NULL.
*/
node_t *lcreate(const pcoef_t data)
{
    node_t *node = (node_t *)malloc(sizeof(node_t));
    if (!node)
    {
        return NULL;
    }
    node->data = data;
    node->next = NULL;

    return node;
}

/*
Insert node to list.

Input data:
* node_t **root - pointer to list's root.
* node_t **temp - pointer for reversing balance.
* const pcoef_t data - polynominal coefficient data to write to new node.
*/
void linsert(node_t **root, node_t **temp, const pcoef_t data)
{
    if (*root)
    {
        (*temp)->next = lcreate(data);
        *temp = (*temp)->next;
    }
    else
    {
        *root = lcreate(data);
        *temp = *root;
    }
}

/*
Input list data.

Input data:
* FILE *const stream - stream to read from.
* node_t **root - pointer to list's root.

Output data:
* Return code - EOK or EINPUTERROR.
*/
int linput(FILE *const stream, node_t **root)
{
    int num, power;
    pcoef_t data;
    node_t *temp;

    do
    {
        if (fscanf(stream, "%d %d", &num, &power) != 2 * GOT_ARG)
        {
            return EINPUTERROR;
        }
        data.num = num;
        data.power = power;
        linsert(root, &temp, data);
    } while (power != 0);

    return EOK;
}

/*
Trace and output list.

Input data:
* node_t **root - pointer to list's root.
* node_t **temp - pointer for reversing balance.
* const pcoef_t data - polynominal coefficient data to write to new node.
*/
void ltrace(FILE *const stream, node_t *const root)
{
    node_t *temp = root;
    while (temp)
    {
        fprintf(stream, "%d %d ", temp->data.num, temp->data.power);
        temp = temp->next;
    }
    fprintf(stream, "%c\n", 'L');
}

/*
Delete list.

Input data:
* node_t **root - pointer to list's root.
*/
void ldelete(node_t **root)
{
    while (*root)
    {
        node_t *temp = *root;
        *root = (*root)->next;
        free(temp);
    }
}
