# ZeroMQ-MPI-adapter

TCP adapter that uses advantages of ZeroMQ asynchronous high-performance messaging library to be used in a distributed system of MPI Processes.

The created adapter will allow Pub/Sub design to push or get data from the MPI process as well as it will multiplex on regular TCP connections at the same time. This will allow a wide variety applications that require fast and asynchronous constant data flow between MPI processes and TCP sockets.
