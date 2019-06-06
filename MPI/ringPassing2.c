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

    int recv=0;
    double timer = MPI_Wtime();

    MPI_Status status;
    MPI_Request sendreq;
    MPI_Request recvreq;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    int my_size = rank;


    double timerAll = MPI_Wtime();
    MPI_Comm subcom;
    MPI_Comm_split(MPI_COMM_WORLD, rank%3 == 0 ? 0 : 1, 0, &subcom);

    MPI_Isend(&my_size, 1, MPI_INT, rank == size - 1 ? 0 : rank + 1, 256, subcom, &sendreq);
    for (int i = 0; i < loops-1; i++)
    {
        MPI_Irecv(&recv, 1, MPI_INT, rank == 0 ? size - 1 : rank - 1, 256, subcom, &recvreq);
        MPI_Wait(&recvreq, &status);
        my_size+=recv;
        MPI_Isend(&recv, 1, MPI_INT, rank == size - 1 ? 0 : rank + 1, 256, subcom, &sendreq);
    }
    printf("Rank Sum: %d\n", my_size);

    MPI_Finalize();
    return 0;
}