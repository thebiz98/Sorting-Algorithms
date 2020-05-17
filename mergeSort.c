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

lint count=0,move=0;
clock_t start,end;
double cpu_time_used;

void swap(lf *a, lf *b)							//function to swap values
{
	lf tmp=*a;
	*a=*b;
	*b=tmp;
}

lint randomize(lint n) 							//function to generate random index for shuffling
{
	return (rand()%n);
}

void shuffle(lf *a, lint n) 						//function to shuffle data
{
	lint i,x;
	for(i=0;i<n;i++)
	{
		x=randomize(n);
		swap(&a[i],&a[x]);
	}
}

void merge(lf *arr, lint l, lint m, lint r)				//merge function to merge the subarrays; used by the merge sort procedure
{
	lint x=m-l+1;
	lint y=r-m;
	lint i=0,j=0,k=0;
	lf *L=(lf *)malloc(x*sizeof(lf));
	lf *R=(lf *)malloc(y*sizeof(lf));
	for(i=0;i<x;i++)
		L[i]=arr[l+i];
	for(i=0;i<y;i++)
		R[i]=arr[m+i+1];
	i=0;
	j=0;
	for(k=l;k<=r;k++)
	{
		if((i<x)&&(j<y))
		{
			count++;					// counts the number of comparisons performed. this data will be used to analyse complexity of the procedure
			move++;						// counts the number of times an element is moved from its position
			if(L[i]<=R[j])
			{
				arr[k]=L[i];
				i++;
			}
			else
			{
				arr[k]=R[j];
				j++;
			}
		}
		else if(i<x&&j>=y)
		{
			move++;						//move counter increased again as elements moved from original location
			arr[k]=L[i];
			i++;
		}
		else if(i>=x&&j<y)
		{
			move++;						//move counter increased again as element moved from original location
			arr[k]=R[j];
			j++;
		}
	}
	free(L);
	free(R);
}

void mergeSort(lf *arr, lint l, lint r)					//the procedure to implement the merge sort algorithm
{
	lint m;
	if(l<r)
	{
		m=(l+r)/2;
		mergeSort(arr,l,m);
		mergeSort(arr,m+1,r);
		merge(arr,l,m,r);
	}
}

int main(int argc, char *argv[])
{
	FILE *f=fopen(argv[argc-1],"r");							//opening file that contains the dataset
	FILE *res=fopen("results.csv","a");							//opening file that will store the result analysis
	lint n,i,x=1,tmp;
	lf n1,c1;
	char dist=argv[argc-1][0];
	int len=strlen(argv[argc-1])+11;
	char out_file[len];
	out_file[0]='\0';
	strcat(out_file,argv[argc-1]);
	strcat(out_file,"mergecheck0");								//generating filename that will store sorted data for verification
	lf *a;
	fscanf(f,"%lld",&n);
	a=(lf *)malloc(n*sizeof(lf));
	for(i=0;i<n;i++)
		fscanf(f,"%lf",a+i);
	fclose(f);										//dataset read into the program and dataset file closed
	srand(time(0));
	for(;x<=5;x++)										//loop to control shuffling of data
	{
		count=0;
		move=0;										//move and comparison counter initialised
		printf("\nShuffle no.: %lld\n",x);
		shuffle(a,n);
		out_file[len-1]++;
		f=fopen(out_file,"w");								//opening file to store sorted dataset
		printf("\nThe output is being written to the file: %s\n",out_file);
		start=clock();
		mergeSort(a,0,n-1);								//calling the mergesort procedure with the dataset
		end=clock();
		cpu_time_used=((double)(end-start))/CLOCKS_PER_SEC;
		fprintf(f,"%lld ",n);								//writing sorted data to output file
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
		fclose(f);									//output data file closed
		n1=n*(log(n)/log(2));								//as the algorithm is supposed to have O(n lg n) complexity, we will use this data for our analysis
		c1=count/n1;									//data to be used for analysis
		printf("The number of comparisons is: %lld\n",count);
		printf("The number of moves is: %lld\n",move);
		printf("The time taken for the sorting is: %lf\n",cpu_time_used);
		fprintf(res,"Merge_Sort,%c,%lld,%lld,%lf,%lld,%lf,%lld,%lf\n",dist,x,n,n1,count,c1,move,cpu_time_used);			//data generated and written to results.csv for analysis of the algorithm
	}
	fprintf(res,"\n");
	fclose(res);										//results file closed
	free(a);										//memory deallocated
	return 0;
}
