#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char** argv){
    MPI_Init(&argc, &argv);
    
    const int MAX_NUMBERS = 100;
    int numbers[MAX_NUMBERS];
    int numberAmount;
    int rank;
    int size;
    int loops = 5;

    MPI_Status status;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);


    if(0 == rank){
        for (int i = 0; i < (size-1)*loops; i++)
        {
            MPI_Recv(numbers, MAX_NUMBERS, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
            MPI_Get_count(&status, MPI_INT, &numberAmount);
            printf("I received %d numbers. Message Source: %d Tag: %d\n", numberAmount, status.MPI_SOURCE, status.MPI_TAG);
        }

    }
    else{
        srand(rank);
        for (int i = 0; i < (size-1)*loops; i++)
        {
            numberAmount = (rand()/(float)RAND_MAX) * MAX_NUMBERS;
            MPI_Send(numbers, numberAmount, MPI_INT, 0, 0, MPI_COMM_WORLD);
            //printf("0 sent %d numbers to 1\n", numberAmount);
        }
    }

    MPI_Finalize();
    return 0;
}