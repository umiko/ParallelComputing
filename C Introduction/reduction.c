#include <stdlib.h>
#include <stdio.h>

double f(int i){
    return (double)rand()/RAND_MAX*(i+1);
}

int main(){
    double res=0;
    #pragma omp parallel shared(res)
    {
        #pragma omp for reduction (+:res)
        for(int i=0; i<30; i++){
            res += f(i);
        }
    }
    printf("Sum: %f", res);
}