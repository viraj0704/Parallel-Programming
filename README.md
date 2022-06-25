# Parallel-Programming

run the code 
$ g++ naive.cpp veo.cpp graph.cpp -o naive -lpthread
format :
$ ./naive datafile thresold numofgraph resultdir numofthreads
Ex.
$ ./naive data1.txt 70 6 res 5

This will output pairs and there similarity using static parallelisation
