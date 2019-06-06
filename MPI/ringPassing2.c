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
    


    double timerAll = MPI_Wtime();
    MPI_Comm subcom;
    MPI_Comm_split(MPI_COMM_WORLD, rank / (size / 3) == 0 ? 0 : 1, 0, &subcom);

    int subrank = 0;
    int subsize = 0;
    MPI_Comm_rank(subcom, &subrank);
    MPI_Comm_size(subcom, &subsize);

    int my_size = rank/subrank;

    MPI_Isend(&my_size, 1, MPI_INT, subrank == subsize - 1 ? 0 : subrank + 1, 256, subcom, &sendreq);
    for (int i = 0; i < subsize-1; i++)
    {
        MPI_Irecv(&recv, 1, MPI_INT, subrank == 0 ? subsize - 1 : subrank - 1, 256, subcom, &recvreq);
        MPI_Wait(&recvreq, &status);
        my_size+=recv;
        MPI_Isend(&recv, 1, MPI_INT, subrank == subsize - 1 ? 0 : subrank + 1, 256, subcom, &sendreq);
    }
    printf("%d/%d Says:\tRank Sum: %d\n", rank, subrank, my_size);

    MPI_Finalize();
    return 0;
}