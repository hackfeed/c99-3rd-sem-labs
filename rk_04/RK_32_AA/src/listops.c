#include "include/listops.h"

node_t *reverse(node_t *root)
{
    node_t *reversed = NULL;
    node_t *temp = root;
    
    while(temp)
    {
        linsert_front(&reversed, temp->data);
        temp = temp->next;
    }
    
    return reversed;
}