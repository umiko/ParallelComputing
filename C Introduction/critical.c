#include <stdlib.h>
#include <stdio.h>

#define rows 16
#define cols 16
int main(){
    int matrix[rows][cols];
    int numberOfZeros = 0;

    for (int row = 0; row < rows; row++)
    {
        for (int col = 0; col < cols; col++)
        {
            matrix[row][col] = 0;
        }
    }

    #pragma omp parallel default(none) shared(matrix, numberOfZeros)
    {
        #pragma omp for
        for (int row = 0; row < rows; row++)
        {
            for (int col = 0; col < cols; col++)
            {
                if (matrix [row][col]==0)
                {
                    #pragma omp critical
                    {
                        numberOfZeros++;
                    }
                }

                
            }
            
        }
    }

    for (int row = 0; row < rows; row++)
    {
        for (int col = 0; col < cols; col++)
        {
            printf("%d ", matrix [row][col]);
        }
        printf("\n");
    }

    printf("The matrix has %d 0's", numberOfZeros);
}