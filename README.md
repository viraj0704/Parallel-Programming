# Computing Graph Similarity with Shared Memory Parallelization

This project focuses on calculating the similarity between two graphs using the Vertex Edge Overlap (VEO) method with shared memory parallelization.

## Table of Contents
- [Static Parallelization](#static-parallelization)
- [Parallelization with Segment](#parallelization-with-segment)

## Static Parallelization

### How to Run

To execute the code for static parallelization, follow these steps:

1. Compile the code:
```shell
$ g++ naive.cpp veo.cpp graph.cpp -o naive -lpthread
```

2. Run the code with the following format:
```shell
$ ./naive datafile threshold numofgraph resultdir numofthreads
```


#### Example
```shell
$ ./naive data2.txt 70 6 res 5
```


This command will produce pairs and their similarity using static parallelization.

## Parallelization with Segment

### How to Run

To execute the code for parallelization with segments, follow these steps:

1. Compile the code:
```shell
$ g++ naive2.cpp veo.cpp graph.cpp -o naive -lpthread
```


2. Run the code with the following format:
```shell
$ ./naive datafile threshold numofgraph resultdir numofthreads length_of_segment
```

#### Example
```shell
$ ./naive data2.txt 70 6 res 3 2
```

This command will produce pairs and their similarity using segment parallelization.

