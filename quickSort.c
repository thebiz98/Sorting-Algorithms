#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<math.h>
#include<time.h>
#include<string.h>

#define lint long long int
#define lf double

lint count=0,swaps=0;
clock_t start,end;
double cpu_time_used;

void swap(lf *a, lf *b)								//function to swap values
{
	lf tmp=*a;
	*a=*b;
	*b=tmp;
}

lint randomize(lint n)								//function to generate random index for shufflling data
{
	return (rand()%n);
}

void shuffle(lf *a, lint n)							//function to shuffle data
{
	lint i,x;
	for(i=0;i<n;i++)
	{
		x=randomize(n);
		swap(&a[i],&a[x]);
	}
}

lint partition(lf *arr, lint l, lint h)						//function to partition dataset, to be used by the quick sort procedure
{
	lf pivot=arr[h];							//last element of the array chosen as pivot
	lint i=l-1;
	lint j;
	for(j=l;j<h;j++)
	{
		count++;							//counting number of comparisons to use for analysis later
		if(arr[j]<pivot)
		{
			swaps++;						//counting the number of times data values are swapped
			i++;
			swap(&arr[i],&arr[j]);
		}
	}
	swaps++;
	swap(&arr[i+1],&arr[h]);
	return i+1;								//returning position of pivot
}

void quickSort(lf *arr, lint low, lint high)					//function to implement quick sort algorithm
{
	if(low<high)
	{
		lint pi=partition(arr,low,high);
		quickSort(arr,low,pi-1);
		quickSort(arr,pi+1,high);
	}
}

int main(int argc, char *argv[])
{
	FILE *f=fopen(argv[argc-1],"r");			//opening the file containing the dataset
	FILE *res=fopen("results.csv","a");			//opening the file that will store the results for analysis
	lint n,i,x=1,n2,n3,tmp;
	lf n1,c1,c2,c3,c4;
	char dist=argv[argc-1][0];
	int len=strlen(argv[argc-1])+11;
	char out_file[len];
	out_file[0]='\0';
	strcat(out_file,argv[argc-1]);
	strcat(out_file,"quickcheck0");				//generating filename of the file that will store the sorted data for verification
	lf *a;
	fscanf(f,"%lld",&n);
	a=(lf *)malloc(n*sizeof(lf));
	for(i=0;i<n;i++)
		fscanf(f,"%lf",a+i);
	fclose(f);						//dataset read into program and dataset file closed
	srand(time(0));
	for(;x<=5;x++)						//loop to control shuffling of data
	{
		count=0;
		swaps=0;					//move and swap count initialised
		printf("\nShuffle no.: %lld\n",x);
		shuffle(a,n);
		out_file[len-1]++;
		f=fopen(out_file,"w");				//file to store sorted dataset opened
		printf("The output is being written to the file: %s\n",out_file);
		start=clock();
		quickSort(a,0,n-1);				//quicksort procedure called
		end=clock();
		cpu_time_used=((double)(end-start))/CLOCKS_PER_SEC;
		fprintf(f,"%lld ",n);
		for(i=0;i<n;i++)
		{
			if(dist=='u')
			{
				tmp=(lint)a[i];
				fprintf(f,"%lld ",tmp);
			}
			else
			{
				fprintf(f,"%lf ",a[i]);
			}
		}
		fclose(f);					//sorted data written to file and file closed
		n1=n*(log(n)/log(2));
		n2=n*n;
		c1=count/n1;
		c2=count/(n2*1.0);				//calculating data for analysis. both comparisons by n lg n and n*n are stored as the complexity of this method varies from  O(n lg n) to O(n^2)
		printf("The number of comparisons is: %lld\n",count);
		printf("The number of swaps is: %lld\n",swaps);
		printf("The time taken for the sorting is: %lf\n",cpu_time_used);
		fprintf(res,"Quick_Sort,%c,%lld,%lld,%lf,%lld,%lld,%lf,%lf,%lld,%lf\n",dist,x,n,n1,n2,count,c1,c2,swaps,cpu_time_used);
	}
	fprintf(res,"\n");
	fclose(res);
	free(a);
	return 0;
}

