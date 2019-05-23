#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char** argv){
    MPI_Init(&argc, &argv);
    
    int rank;
    int size;
    int loops = 50;

    float f;
    double timer = MPI_Wtime();

    MPI_Status status;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    for (int i = 0; i < loops; i++)
    {
        if (0 == rank % 2)
        {
            MPI_Recv(&f, 1, MPI_FLOAT, 1, 17, MPI_COMM_WORLD, &status);
            printf("Rank %d says: %s\tRTT=%f\n", rank, "PONG", MPI_Wtime() - timer);
            timer = MPI_Wtime();
            MPI_Send(&f, 1, MPI_FLOAT, 1, 23, MPI_COMM_WORLD);
        }
        else
        {
            MPI_Send(&f, 1, MPI_FLOAT, 0, 17, MPI_COMM_WORLD);
            printf("Rank %d says: %s\tRTT=%f\n", rank, "PING", MPI_Wtime() - timer);
            timer = MPI_Wtime();
            MPI_Recv(&f, 1, MPI_FLOAT, 0, 23, MPI_COMM_WORLD, &status);
        }
    }

    MPI_Finalize();
    return 0;
}