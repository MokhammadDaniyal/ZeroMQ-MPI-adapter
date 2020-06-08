//  Hello World client
#include <zmq.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

int main(void)
{
    //  Prepare our context and publisher

    void *context = zmq_ctx_new ();
    void *publisher = zmq_socket (context, ZMQ_PUB);
    int rc = zmq_connect(publisher, "tcp://localhost:4445");
    // assert(rc == 0);
    // zmq_bind (publisher, "tcp://*:4445");
    char *string = "Hi!\n";
    char a;

    void *syncservice = zmq_socket(context, ZMQ_REQ);
    zmq_bind(syncservice, "tcp://*:4462");
    printf("Waiting for subscribers\n");
    int subscribers = 0;
    // while (subscribers < 1)
    // {
    //     //  - wait for synchronization request
    //     char *string[1];
    //     zmq_recv(syncservice, string, 1, 0);

    //     //  - send synchronization reply
    //     zmq_send(syncservice, "", 1, 0);
    //     subscribers++;
    //     printf("Subscribers: %d", subscribers);
    // }
    int i = 0;
    char* str[1000];
    while (1) {
        sprintf(str, "%d", i);
        //  Send message to all subscribers
        int rc = zmq_send (publisher, str, 5, ZMQ_NOBLOCK);
        printf("Sent %d bytes\n", rc);
        i++;
        sleep (2);
    }

    zmq_close (publisher);
    zmq_term (context);
    return 0;
}