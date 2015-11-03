How to run the programme/s
==========================

First of all build all programmes:

    $ make
    
Afterwards you can run the programme (e.g. bubble sort) as follows:

    $ ./bubble_sort <problem-size>
    
If you want to submit a job (e.g. quicksort job) simply run:

    $ ./qsub quicksort.sge
    
If you want to clean up just do:

    $ make clean
    
Measurements
============

Host machine: LCC Cluster with 5 nodes, where each node contains 8 CPUs
Measurement technique: I had to use c-libraries to measure the time, because the profiler programmes (Intel and PGI) did not work on lcc

Programme             | Problem size           | Runtime (in s) | Complexity (average case)
:---------------------|-----------------------:|---------------:|---------------------------------------:
matrix_multiplication | 10000x10000x2          | 16566.48       | O(n³)
gaussian_elimination  | 10000x10000-1          | 3868.46        | O(n²)
dijkstra              | 10000 (49995000 edges) | 8.24           | O(n² x m), where m is edge count
sieve_of_eratosthenes | 1000000000             | 189.48         | O(n)
bubble_sort           | 1000000                | 7541.54        | O(n²)
bucket_sort           | 1000000 (1000 buckets) | 0.17           | O(n+k), where k is bucket count
counting_sort         | 1000000                | 0.05           | O(n+k), where k is the number intervall
insertion_sort        | 1000000                | 1336.00        | O(n²)
selection_sort        | 1000000                | 2102.71        | O(n²)
quicksort             | 1000000                | 0.37           | O(n log n)

The corresponding problem sizes were chosen dependent on the complexity of the algorithms. The sorting algorithms were parameterized with the same problem size, to compare their runtimes.

The matrix multiplication and the gaussian_elimination are comparable, because they both use matrices. The matrix multiplication needs much more than twice the time the gaussian elimination needs for half of the problem size, which seems valid, because the complexity is n times higher. The chosen problem size for dijkstra is relatively small, due to the amount of graph initialising time (for problem size 100000 the algorithm did not terminate after 2 days in the cluster). This could be optimized. The sieve of erastosthenes is comparably fast, because it has the lowest complexity. The runtimes for the sorting algorithms with the same problem size seem to be all valid as well considering their complexity. Of course the algorithms with same problem size and complexity can have different runtimes due to different implementations, cache misses, measurement mistakes etc.