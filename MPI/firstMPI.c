#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>
#include <unistd.h>

int main(int argc, char** argv){
    MPI_Init(&argc, &argv);
    char hn[128];
    gethostname(hn, 128);
    int pid = getpid();

    int size;
    int rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int rec;


    if(rank==0){
        MPI_Send(&size, sizeof(size), MPI_INT, rank+1, 0, MPI_COMM_WORLD);
    }
    else{
        MPI_Recv(&size, sizeof(size), MPI_INT, rank-1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        if(rank<size-1){
            MPI_Send(&size, sizeof(size), MPI_INT, rank+1, 0, MPI_COMM_WORLD);
        }
    }
    //printf("Hello World!\nThis is %s, Process %i!\nNode size is %i and this process is ranked %i.\n", hn, pid, size, rank);
    printf("%s, Process %i, Node size %i, ranked %i.\n", hn, pid, size, rank);

    MPI_Finalize();
    return 0;
}