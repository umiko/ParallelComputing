#include <stdlib.h>
#include <stdio.h>

int fibonacci(int fibonacciNumber);

int main(int argc, char** argv){

    if(argc<2){
        fprintf(stderr, "usage: %s <array size>\nexit\n", argv[0]);
        return 1;
    }

    int fibMax = atoi(argv[1]);

    int* fibArray = (int*)malloc(fibMax*sizeof(int));
    #pragma omp parallel for
    for(int i = 0; i < fibMax; i++){
        fibArray[i] = fibonacci(i);
    }
    //end parallel

    //for (int i = 0; i < fibMax; i++)
    //{
        printf("%d Fibonacci number: %d\n", fibMax, fibArray[fibMax-1]);
    //}

    free(fibArray);

    return 0;
}


int fibonacci(int fibonacciNumber){
    int a=0, b=1, c=0;
    for (int j = 0; j < fibonacciNumber; j++)
    {
        c=a+b;
        a=b;
        b=c;
    }
    return c;
}