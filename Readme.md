The objctive of this assignment is to study the complexity of a select few sorting algorithms and study the increase in complexity as the input size increases. 

The input to each program is a dataset containing randomly generated numbers.
There are two kinds of datasets, one of theem contains numbers generated from uniform distribution, the other contains data generated from normal distribution. 
Datasets of varying sizes are generated belonging to these two categories, and the number of comparisons is recorded. (additional data like number of moves, swaps, cpu time are also recorded for the algorithms for our own understanding/observation)
That is then used to determine and compare the complexity of each sorting algorithm.

(Note: The complexity in this assignment is determined solely based on the number of comparisons the data elements undergo. It is meant to give an approximate idea of the complexity of the algorithm)

The sorting algorthms used in this assignment are: 

1. Merge Sort (O(n lg n))
2. Quick Sort: (O(n lg n))
	a. with last element as pivot
	b. with a randomly selected element as pivot
	c. with the median of medians as pivot
3. Bucket Sort (O(n))


A description of the programs in this repository is as follows: 

prog1.c : This is a program to generate datasets of varying sizes containing randomly generated numbers belonging to uniform distribution. The output is written to a file, the filename is provided as a command line argument. The number of data elements and the range of the numbers are also provided as command line arguments.

execution format: 

$ gcc -o gen_uni prog1.c

$ ./gen_uni <outputfilename> <number_of_terms_required> <start_value> <end_value>


prog2.c : This is a program to generate datasets of varying sizes containing randomly generated numbers belonging to a normal distribution, whose median and standard deviation are provided as command line arguments. The desired size of the dataset is also provided as command line argument. The output is written to an output file, whose name is provided as a command line argument.

execution format:

$ gcc -o gen_norm prog2.c -lm

$ ./gen_norm <outputfilename> <number_of_terms_required> <mean> <standard_deviation>


NOTE: while generating the datasets, it is advised to start the file name of the dataset for uniform distribution with a 'u' and the filename for the dataset with normal distribution with a 'n', as the further programs use these letters to identify the kind of distribution being handled. For proper execution of the programs and obtaining proper results, this instruction must be adhered to.


mergeSort.c : This is a program to implement the merge sort algorithm. The program takes the filename containing the dataset as a command line argument, reads the data and then outputs the sorted data and the number of comparisons, moves and the cpu time required. The program shuffles the data 5 times randomly and sorts the data each time. A brief summary of the results after every shuffle is displayed on screen. The programs outputs to 6 files in total for a particular input dataset. Five of the files have names in the following format: 1. <inputfilename_sortname_check_shufflenumber> and the 6th file is 2. 'results.csv'
1. These files contain the sorted data after each shuffle. This is to help us check if the algorithm is sorting the data correctly
2. This file stores the results obtained after the sorting takes place, like the number of comparisons, moves, input size, shuffle number, and more details that would be used for our analysis.

execution format:

$ gcc -o ms mergeSort.c -lm

$ ./ms <file_name>


quickSort.c : This is a program to implement the quick sort algorithm that uses the last element as the pivot. The program takes the filename containing the dataset as a command line argument, reads the data and then outputs the sorted data and the number of comparisons, swaps and cpu time required. The program shuffles the data 5 times randomly and sorts the data each time, displaying the results briefly with each shuffle on the screen. The shuffled data and the detailed data are written in separate files. Five of the files store the sorted data, a file for each shuffling. The format for the file containing the sorted data after each shuffle is : <inputfilename_sortname_check_shufflenumber>. The detailed results, containing data such as distribution type, shuffle name, input size, number of comparisons, number of swaps and other useful data are written to the file 'results.csv'. This makes it easier to tabulate the data for analysis later.

execution format:

$ gcc -o qs quickSort.c -lm

$ ./qs <file_name>


rquickSort.c : This program implements the quick sort algorithm by choosing the pivot for partitioning at random. The functioning after that is similar to quick sort. The randomisation of the pivot makes the execution more statistically and mathematically sound, and increases the chances of obtaining a good partition. It reduces the dependency of the code on the order of elements in the input dataset. Even a sorted dataset as an input would not give worst case running time as the pivot as chosen at random, so it won't necessarily be the largest or smallest element. The only time when we will obtain the worst case partitioning is when the highest or lowest element is picked by our random pivot selection as pivot. The rest of the functioning, format of input and output files are similar to quickSort.c above.

execution format:

$ gcc -o rqs rquickSort.c -lm

$ ./rqs <file_name>


momqs.c : This program uses order statistics to choose the median of medians of the dataset as its pivot for array partition. Here I have used the worst case selection of the median of medians to get a linear worst case selection time. The program has a part that finds and returns the median of medians. This value is then used as the pivot for partitioning the dataset and the further algorithm is the general quick sort algorithm. This selection further increases the chances of obtaining a good partition. The program outputs a total of 16 files for any given input file. This is because, the worst case selection of median of medians uses three values to divide the dataset into smaller units and obtaining median of medians: 3, 5 and 7, for each shuffling of the dataset, and one results.csv file. The format for the name of the output files is: <inputfilename_sortname_check_smallestpartitionsize_shufflenumber>. The detailed results are written in the 'results.csv' file.

execution format:

$ gcc -o mqs momqs.c -lm

$ ./mqs <file_name>


bucketSort.c : This program uses the bucket sort algorithm to sort the input dataset. This algorithm ssorts the elements with linear complexity, by forming 'buckets' and putting the elements in the appropriate buckets, sorting the buckets and then reading the elements into the array in a serial manner to obtain the sorted dataset. The shuffling of the dataset makes no sense for this algorithm as the elements will end up in the same bucket, so shuffling has been avoided in this program. Therefore, this program outputs into two files for an input dataset: 1.<inputfilename_sortname_check> : The file with the output sorted dataset. 2.'results.csv' : The results of the sorting are stored here. In addition to number of comparisons and other general data, it also outputs the numbeer of buckets formed and the size of the largest bucket.

Note : The bucket sort function works with normalised data, as the allotment of bucket uses this normalisation as a feature. Therefore, the dataset for this program is supplied by the 'norm0to1.c' program as described below. It is advised to run the dataset to be sorted through the 'norm0to1.c' program and then give the output obtained from that program as the input for this program.

execution format:

$ gcc -o bs bucketSort.c -lm

$ ./bs <file_name>


These are the programs that deal with the generation of the datasets and implementation of the algorithms. Some additional programs that are needed are as follows: 

norm0to1.c : This program takes a dataset file as input and outputs its normalised version, i.e the data is normalised between 0-1,  in an output file that is named as: <norminputfilename>. This file is then used as the input for the bucketSort.c program, as it works on normalised data.

execution format:

$ gcc -o normalise norm0to1.c

$ ./normalise <file_name>


verify.c : This program is used to test if a dataset is sorted or not. If the datased is sorted, it says that sorting has been verified. If not, then it outputs the terms that are not in sorted order. It accepts just one <filename> as its input, which is the dataset to be checked. It outputs to the terminal window.

execution format:

$ gcc -o v verify.c

$ ./v <file_name>


This completes the description of all the programs required for the analysis of the algorithms. Now what follows is a bash script prepared for quick execution and demo.

assignment.sh : This is a bash script containing the commands to generate 12 datasets of uniform distribution and 12 datasets of normal distribution and then apply all the algorithms on the datasets and verify the results. It will lead to creation of a number of files, equivalent to executing all the programs 12 times. Therefore, it is advised to run the script in a clean folder which just has the compiled files. In case you havent copied the compiled files from here, copy all the source code files to that folder, and run all the 'gcc ...' commands listed here, then run the bash script. But before being able to execute the bash script, you will have to give it permission for execution. The way to do this is described as folows.

execution format:

$ chmod +x assignment.sh   ---> this command will give the bash script the execution permission

$ ./assignment.sh


All the gcc commands described here have been provided keeping in mind this script. The names for the compiled files are what have been written in the bash script.

The bash script will create 24 datasets for merge sort and the various variants of the quick sort algorithm, and 24 additional files will be created which are the normalised versions of these datasets, to be used for bucket sort. 
