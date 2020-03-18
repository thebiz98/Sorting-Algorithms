The objctive of this assignment is to study the complexity of a select few algorithms and study the increase in complexity as the input size increases. 

The input is a dataset containing randomly generated numbers. 
There are two kinds of datasets, one of theem contains numbers generated from uniform distribution, the other contains data generated from normal distribution. 
Datasets of varying sizes are generated belonging to these two categories, and the number of comparisons is recorded. (additional data like number of moves, swaps, cpu time are also recorded for the algorithms for our own understanding/observation)
That is then used to determine and compare the complexity of each sorting algorithm.

(Note: The complexity in this assignment is determined solely based on the number of comparisons the data elements undergo. It does not incorporate the space or time complexity)

The sorting algorthms used in this assignment are: 

1. Merge Sort (O(n lg n))
2. Quick Sort: (O(n lg n))
	a. with last element as pivot
	b. with a randomly selected element as pivot
	c. with the median of medians as pivot
3. Bucket Sort (O(n))

A description of the programs in this repository is as follows: 

prog1.c : This is a program to generate datasets of varying sizes containing randomly generated numbers belonging to uniform distribution. The output is written to a file, the filename is provided as a command line argument. The number of data elements and the range of the numbers are also provided as command line arguments.

prog2.c : This is a program to generate datasets of varying sizes containing randomly generated numbers belonging to a normal distribution, whose median and standard deviation are provided as command line arguments. The desired size of the dataset is also provided as command line argument. The output is written to an output file, whose name is provided as command line arguments.

.
.
.
.
.
#not yet complete
