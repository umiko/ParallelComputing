#include <stdlib.h>
#include <stdio.h>

unsigned long long fibonacci(int fibonacciNumber);
int fibonacciRecursive(int fibonacciNumber);

int main(int argc, char** argv){

    if(argc<2){
        fprintf(stderr, "usage: %s <array size>\nexit\n", argv[0]);
        return 1;
    }

    int fibMax = atoi(argv[1]);

    unsigned long long* fibArray = (unsigned long long*)malloc(fibMax*sizeof(unsigned long long));

    int i=0;
    #pragma omp parallel for private(i)
    for(i = 0; i < fibMax; i++){
        fibArray[i] = fibonacci(i);
    }
    //end parallel

    for (int i = 0; i < fibMax; i++)
    {
        printf("%d Fibonacci number: %llu\n", i, fibArray[i]);
    }

    free(fibArray);

    return 0;
}


unsigned long long fibonacci(int fibonacciNumber){
    unsigned long long a=0, b=1, c=0;
    for (int j = 0; j < fibonacciNumber; j++)
    {
        c=a+b;
        a=b;
        b=c;
    }
    return c;
}

int fibonacciRecursive(int fibonacciNumber){
    if(fibonacciNumber<=1){
        return 1;
    }
    else{
        int a,b,c;
        #pragma omp parallel num_threads(2)
        {
            #pragma omp single
            {
                #pragma omp task
                a = fibonacciRecursive(fibonacciNumber-1);
                #pragma omp task
                b = fibonacciRecursive(fibonacciNumber-2);
                #pragma omp taskwait
                c = a+b;
            }
        }
        return c;
    }
}