#include <czmq.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include <mpi.h>

int main(int argc, char **argv)
{
    int rank;
    char hostname[256];

    int limit;
    int number;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &limit);
    gethostname(hostname, 255);

    if (rank == 0)
    {
        printf("I am Adapter --- %d \n", rank);
        //  Socket to talk to clients
        void *context = zmq_ctx_new();
        void *responder = zmq_socket(context, ZMQ_REP);
        int rc = zmq_bind(responder, "tcp://*:5555");
        assert(rc == 0);
        number = 2;

            while (1)
            {
                char buffer[10];
                zmq_recv(responder, buffer, 10, 0);
                printf("%c Recieved\n", buffer[0]);
                sleep(1); //  Do some 'work'
                zmq_send (responder, "World", 5, 0);
                MPI_Send(&number, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
                number++;
            }
    }

    else
    {
        while (1)
        {
            MPI_Recv(&number, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            {
                printf("Process %d received number %d from process %d\n", rank, number, rank - 1);
            }
        }
        // printf("I am MIDDLEWARE --- %d \n", rank);
    }
    return 0;
}
