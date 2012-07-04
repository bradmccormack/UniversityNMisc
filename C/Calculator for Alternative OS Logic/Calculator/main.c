#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "calculation.h"

int main()
{
    /*for simple mode*/
   double sum=0.0;

    /*ptr to list of operations to calculate*/
    OperationList ops;
    initCalculator(&ops);


    /*storage for the expression to evaluate*/
    /*stringInit(&calculation);*/

    printf("Calculator test\n");

    Add(1,&sum);
    Add(2,&sum);

    /*queueAdd(2,&ops);*/

    assert(sum==3);
    printf("1+2=3 test PASSED SIMPLE MODE\n");


    queueAdd(1,&ops);
    queueAdd(2,&ops);
    queueMultiply(3,&ops);
    printOperationQueue(&ops);

    assert(calculate(&ops)==3);
    printf("1+2=3 test PASSED PRECEDENCE MODE\n");


    Multiply(3,&sum);
    /*queueMultiply(3,&ops);*/
    printf("=%f\n",sum);
    assert(sum==9);

    printf("1+2*3=9 test PASSED SIMPLE MODE\n");



    return 0;
}
