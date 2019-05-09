#include <stdlib.h>
#include <stdio.h>

double f(int i){
    return rand()/(i+1);
}

int main(){
    int h;
    double res;
    #pragma omp parallel shared(h,res)
    {
        #pragma omp for reduction (+:res)
        for(int i=0; i<30; i++){
            res += f(i);
        }
    }
    printf("Sum: %f", res);
}