The objctive of this assignment is to study the complexity of a select few sorting algorithms and study the increase in complexity as the input size increases. 

The input to each program is a dataset containing randomly generated numbers.
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

prog2.c : This is a program to generate datasets of varying sizes containing randomly generated numbers belonging to a normal distribution, whose median and standard deviation are provided as command line arguments. The desired size of the dataset is also provided as command line argument. The output is written to an output file, whose name is provided as a command line argument.

mergeSort.c : This is a program to implement the merge sort algorithm. The program takes the filename containing the dataset as a command line argument, reads the data and then outputs the sorted data and the number of comparisons, moves and the cpu time required. The program shuffles the data 5 times randomly and sorts the data each time. A brief summary of the results after every shuffle is displayed on screen. The programs outputs to 6 files in total for a particular input dataset. Five of the files have names in the following format: 1. <inputfilename_sortname_check_shufflenumber> and the 6th file is 2. 'results.csv'
1. These files contain the sorted data after each shuffle. This is to help us check if the algorithm is sorting the data correctly
2. This file stores the results obtained after the sorting takes place, like the number of comparisons, moves, input size, shuffle number, and more details that would be used for our analysis.

quickSort.c : This is a program to implement the quick sort algorithm that uses the last element as the pivot. The program takes the filename containing the dataset as a command line argument, reads the data and then outputs the sorted data and the number of comparisons, swaps and cpu time required. The program shuffles the data 5 times randomly and sorts the data each time, displaying the results briefly with each shuffle on the screen. The shuffled data and the detailed data are written in separate files. Five of the files store the sorted data, a file for each shuffling. The format for the file containing the sorted data after each shuffle is : <inputfilename_sortname_check_shufflenumber>. The detailed results, containing data such as distribution type, shuffle name, input size, number of comparisons, number of swaps and other useful data are written to the file 'results.csv'. This makes it easier to tabulate the data for analysis later.
.
.
.
.
#not yet complete
