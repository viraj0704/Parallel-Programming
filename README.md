# Parallel-Programming

run the code <br/>
$ g++ naive.cpp veo.cpp graph.cpp -o naive -lpthread <br/>
format : <br/>
$ ./naive datafile thresold numofgraph resultdir numofthreads <br/>
Ex.<br/>
$ ./naive data1.txt 70 6 res 5<br/>

This will output pairs and there similarity using static parallelisation<br/>
