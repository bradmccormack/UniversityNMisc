#include <stdio.h>
#include "list.h"

OperationPtr insertatEnd(OperationPtr node,OperationPtr insertnode)
{
    insertnode->prev=node;
    insertnode->next=NULL;
    node->next=insertnode;

    return node;
}

OperationPtr insertBetween(OperationPtr prev,OperationPtr next,OperationPtr op)
{
    if(prev!=NULL)
    {
              prev->next=op;
              op->prev=prev;
    }

    if(next!=NULL)
        next->prev=op;

    op->next=next;
    return op;

}
