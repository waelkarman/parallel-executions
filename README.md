# parallel programming [in development]
The main goal is to master parallel programming using C++ primitives, POSIX Threads and OpenMPI.

<img src="doc/screen.gif">

- C++/20 primitives
- POSIX Threads
- OpenMPI
 
<!-- lstopo --> 
<!-- numactl -->



# C++/20 build within a Docker
Use the dockerfile to compile the C++/20 code if your system does not support it.

Please build using the following commands:

> sudo docker build -t cpp20-runner .

To run:

> sudo docker run cpp20-runner ./\<EXECUTABLE NAME\>

To stop the execution find the ID of your container using:

> sudo docker ps

To stop:

> sudo docker stop \<CONTAINER ID\>