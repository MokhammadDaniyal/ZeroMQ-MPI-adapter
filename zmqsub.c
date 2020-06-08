#include <zmq.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include <mpi.h>

int main(int argc, char *argv[])
{

    printf("Waiting for publishers\n");

    int rank;
    char hostname[256];

    int limit;
    int number;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &limit);
    gethostname(hostname, 255);

    int rc;
    void *context = zmq_ctx_new();

    //  Socket to talk to server
    void *subscriber = zmq_socket(context, ZMQ_SUB);
    zmq_setsockopt(subscriber, ZMQ_SUBSCRIBE, "", 0);
    rc = zmq_connect(subscriber, "tcp://localhost:4444");
    assert(rc == 0);

    while (1)
    {
        char buf [256];

        int nbytes = zmq_recv(subscriber, buf, 256, 0);
        assert(nbytes != -1);
        printf("Process: %d, Recieved %s\n", rank, buf);

        sleep(1); //  Do some 'work'
    }

    zmq_close(subscriber);
    zmq_term(context);
    return 0;
}