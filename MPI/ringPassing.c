#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char** argv){
    MPI_Init(&argc, &argv);
    
    int rank;
    int size;
    int loops = 10;

    int my_size = rank;
    int recv=0;
    double timer = MPI_Wtime();

    MPI_Status status;
    MPI_Request sendreq;
    MPI_Request recvreq;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    double timerAll = MPI_Wtime();

    MPI_Isend(&my_size, 1, MPI_INT, rank == size - 1 ? 0 : rank + 1, 256, MPI_COMM_WORLD, &sendreq);
    for (int i = 0; i < loops-1; i++)
    {
        MPI_Irecv(&recv, 1, MPI_INT,rank==0 ? size-1 : rank-1, 256, MPI_COMM_WORLD, &recvreq);
        my_size+=recv;
        MPI_Isend(&recv, 1, MPI_INT, rank==size-1 ? 0 : rank+1, 256, MPI_COMM_WORLD, &sendreq);
    }
    printf("Rank Sum: %i", my_size);

    MPI_Finalize();
    return 0;
}