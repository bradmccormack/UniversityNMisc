#ifndef CALCULATION_H_INCLUDED
#define CALCULATION_H_INCLUDED
#include "bstring.h"

/*type of operations the calculator supports*/


/*operation that is queued for evaluation later*/
typedef struct operationInfo* OperationPtr;
typedef struct operationInfo
{
    /*where in the expression the operation should be evaluated*/
    unsigned int precedence;
    char operation;
    double value;
    OperationPtr prev,next;
}Operation;

/*list of operations that should be evaluted for final calculation value*/
typedef struct operationListInfo
{
    OperationPtr head;
    unsigned int operationDepth;

}OperationList;

/*simple mode*/
double Add(double number,double *sum);
double Subtract(double number,double *sum);
double Divide(double number,double *sum);
double Multiply(double number,double *sum);

/*scientific mode*/
void queueAdd(double number,OperationList *operationList);
void queueSubtract(double number,OperationList *operationList);
void queueDivide(double number,OperationList *operationList);
void queueMultiply(double number,OperationList *operationList);
void queueExpression(char *expressionToEvaluate,OperationList *operationList);
void queueOperation(OperationPtr operation,OperationList *operationList);

/*function to evaluate current expression*/
double calculate(OperationList *operationList);

/*misc functions*/

/*setup the calculator*/
void initCalculator(OperationList *operationList);

/*clear the list of operations*/
void clearCalculator(OperationList *operationList);

void openBracket(OperationList *operationList);
void closeBracket(OperationList *operationList);

/*for debugging .. show the order of operations as placed in the queue*/
void printOperationQueue(OperationList *operationList);




#endif


