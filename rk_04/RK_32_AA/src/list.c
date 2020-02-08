#include "include/list.h"

node_t *lcreate(const char data)
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

void linsert(node_t **root, node_t **temp, const char data)
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

void linsert_front(node_t **root, const char data)
{
    if (*root)
    {
        node_t *temp = lcreate(data);
        temp->next = *root;
        *root = temp;
    }
    else
    {
        *root = lcreate(data);
    }
}

int linput(FILE *const stream, node_t **root)
{
    char data;
    node_t *temp;

    do
    {
        if (fscanf(stream, "%c", &data) != GOT_ARG)
        {
            return EINPUTERROR;
        }
        linsert(root, &temp, data);
    } while (data != EOF);

    return EOK;
}

void ltrace(FILE *const stream, node_t *const root)
{
    node_t *temp = root;
    while (temp)
    {
        if (temp->data == ' ')
        {
            fprintf(stream, "\n");
        }
        else
        {
            fprintf(stream, "%c", temp->data);
        }
        temp = temp->next;
    }
    fprintf(stream, "\n");
}

void ldelete(node_t **root)
{
    while (*root)
    {
        node_t *temp = *root;
        *root = (*root)->next;
        free(temp);
    }
}
