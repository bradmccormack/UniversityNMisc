#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED
#include "calculation.h"
#include <stdio.h>
OperationPtr insertBetween(OperationPtr prev,OperationPtr next,OperationPtr op);
OperationPtr insertatEnd(OperationPtr node,OperationPtr insertnode);
#endif
