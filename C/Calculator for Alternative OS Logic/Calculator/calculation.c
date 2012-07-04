#include "calculation.h"
#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#define PRECEDENCE_ADD 1
#define PRECEDENCE_SUBTRACT 1
#define PRECEDENCE_MULTIPLY 5


/*simple mode -aka Windows calc and OSX Leopard calc - Wrong imo :-( */
double Add(double number,double *sum)
{
    *sum+=number;
    return *sum;
}
double Subtract(double number,double *sum)
{
    *sum-=number;
    return *sum;
}
double Divide(double number,double *sum)
{
    *sum=*sum/number;
    return *sum;
}
double Multiply(double number,double *sum)
{
    *sum=*sum*number;
    return *sum;
}

void printOperationQueue(OperationList *operationList)
{
    OperationPtr node;
    register int i=1;

    printf("Highest operation depth =%d\n",operationList->operationDepth);
    node=operationList->head;
    while(node!=NULL)
    {
        if(node->prev!=NULL)
            printf("Operation is prev (%f) %c current (%f)\n",
                   node->prev->value,node->operation,node->value);
        else
            printf("Operation is prev (%d) %c current (%f)\n",
                   -1,node->operation,node->value);
        i++;
        node=node->next;
    }
}

/*add the next operation to list of operations*/
void queueOperation(OperationPtr operation,OperationList *operationList)
{
    OperationPtr node,prev;
    int compare;

    /*if no calculation then insert at the head*/
    if(operationList->head==NULL)
    {
        operationList->head=insertBetween(NULL,operationList->head,operation);
        return;
    }
    node=operationList->head;
    prev=node;
    do
    {
        compare=operation->precedence-node->precedence;
        /*the operation needs to occur next in the list so insert */
        if(compare>0)
        {
            node=insertBetween(prev,node,operation);
            return;
        }
        if(node!=NULL)
            prev=node;
        node=node->next;
    }while(node!=NULL);

    /*insert at the end .. this must be the lowest or equal to previous lowest precedence*/
    node=insertatEnd(prev,operation);
}
/*add an ADD operation*/
void queueAdd(double number,OperationList *operationList)
{
    OperationPtr op;
    op=malloc(sizeof(Operation));

    /*put in error return value later*/
    if(op==NULL)
        return;

    /*set addition operation and value etc*/
    op->prev=NULL;
    op->operation='+';
    op->value=number;
    op->next=NULL;
    op->precedence=operationList->operationDepth*PRECEDENCE_ADD;

    /*now insert the operation into the list to evalute when calculate is called*/
    queueOperation(op,operationList);
    return;
}
void queueSubtract(double number,OperationList *operationList)
{
   return;
}
void queueDivide(double number,OperationList *operationList)
{
   return;
}
void queueMultiply(double number,OperationList *operationList)
{
    OperationPtr op;
    op=malloc(sizeof(Operation));

    /*put in error return value later*/
    if(op==NULL)
        return;

    /*set addition operation and value etc*/
    op->prev=NULL;
    op->operation='*';
    op->value=number;
    op->next=NULL;
    op->precedence=operationList->operationDepth*PRECEDENCE_MULTIPLY;

    /*now insert the operation into the list to evalute when calculate is called*/
    queueOperation(op,operationList);
    return;
   return;
}

/*batch usage of calculator*/
void queueExpression(char *expressionToEvaluate,OperationList *operationList)
{
   return;
}

/*function to evaluate current expression*/
double calculate(OperationList *operationList)
{
    double result=0.0;
    return result;
}

void initCalculator(OperationList *operationList)
{
    operationList->head=NULL;
    operationList->operationDepth=1;

}
void clearCalculator(OperationList *operationList)
{
    /*return all memory from the operations*/
    OperationPtr head,prev;

    head=operationList->head;
    prev=head;
    while(head!=NULL)
    {
        prev=head;
        head=head->next;
        free(prev);
    }
}

void openBracket(OperationList *operationList);
void closeBracket(OperationList *operationList);
