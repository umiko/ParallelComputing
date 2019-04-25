#include <stdlib.h>
#include <stdio.h>

int main(int argc, char** argv){

    if(argc<2){
        fprintf(stderr, "usage: %s <array size>\nexit\n", argv[0]);
        return 1;
    }

    int arraySize = atoi(argv[1]);

    int* A = (int*) malloc(arraySize*sizeof(int));
    int* B = (int*) malloc(arraySize*sizeof(int));
    int* C = (int*) malloc(arraySize*sizeof(int));

    srand(1234);
    for(int i = 0; i < arraySize; i++){
        A[i]=rand();
        B[i]=rand();
    }
    #pragma omp parallel for
    for(int i = 0; i < arraySize; i++){
        C[i]=A[i]+B[i];
    }

    //for(int i = 0; i < arraySize; i++){
    //    printf("%d + %d = %d\n", A[i], B[i], C[i]);
    //}

    free(A);
    free(B);
    free(C);
    return 0;
}