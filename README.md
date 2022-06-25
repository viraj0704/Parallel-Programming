# Parallel-Programming

1. STATIC PARALLELISATION <br/>
run the code <br/>
$ g++ naive.cpp veo.cpp graph.cpp -o naive -lpthread <br/>
format : <br/>
$ ./naive datafile thresold numofgraph resultdir numofthreads <br/>
Ex.<br/>
$ ./naive data1.txt 70 6 res 5<br/>

This will output pairs and there similarity using static parallelisation<br/>


2. PARALLELISATION WITH SEGMENT <br/>
run the code <br/>
$ g++ naive2.cpp veo.cpp graph.cpp -o naive -lpthread <br/>
format : <br/>
$ ./naive datafile thresold numofgraph resultdir numofthreads length_of_segment<br/>
Ex.<br/>
$ ./naive data1.txt 70 6 res 3 2 <br/>

This will output pairs and there similarity using segment parallelisation <br/>
