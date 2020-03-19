#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<math.h>
#include<time.h>

#define lint long long int
#define lf double

lint count=0,swap=0;
clock_t start,end;
double cpu_time_used;

lint partition(lf *arr, lint l, lint h, lint r)
{
	lf t;
	swap++;
	t=arr[h];
	arr[h]=arr[r];
	arr[r]=t;
	lf pivot=arr[h];
	lint i=l-1;
	lint j;
	for(j=l;j<h;j++)
	{
		count++;
		if(arr[j]<pivot)
		{
			swap++;
			i++;
			t=arr[j];
			arr[j]=arr[i];
			arr[i]=t;
		}
	}
	swap++;
	t=arr[i+1];
	arr[i+1]=arr[h];
	arr[h]=t;
	return i+1;
}

lint partitionInt(lint *arr, lint l, lint h, lint r)
{
	lint t;
	swap++;
	t=arr[h];
	arr[h]=arr[r];
	arr[r]=t;
	lint pivot=arr[h];
	lint i=l-1;
	lint j;
	for(j=l;j<h;j++)
	{
		count++;
		if(arr[j]<pivot)
		{
			swap++;
			i++;
			t=arr[j];
			arr[j]=arr[i];
			arr[i]=t;
		}
	}
	swap++;
	t=arr[i+1];
	arr[i+1]=arr[h];
	arr[h]=t;
	return i+1;
}

lint randoms(lint low, lint high)
{
	srand(time(0));
	lint index=(rand()%((high-low)+1))+low;
	//printf("index= %lld\n",index);
	return index;
}

void quickSort(lf *arr, lint low, lint high)
{
	if(low<high)
	{
		lint r=randoms(low,high);
		lint pi=partition(arr,low,high,r);
		quickSort(arr,low,pi-1);
		quickSort(arr,pi+1,high);
	}
}

void quickSortInt(lint *arr, lint low, lint high)
{
	if(low<high)
	{
		lint r=randoms(low,high);
		lint pi=partitionInt(arr,low,high,r);
		quickSortInt(arr,low,pi-1);
		quickSortInt(arr,pi+1,high);
	}
}

int main(int argc, char *argv[])
{
	FILE *f=fopen(argv[argc-1],"r");
	FILE *res=fopen("results.csv","a");
	char dist=argv[argc-1][0];
	lf *arr;
	lint *a;
	lint n,i,flag=0;
	fscanf(f,"%lld",&n);
	if(dist=='n')
	{
		arr=(lf *)malloc(n*sizeof(lf));
		for(i=0;i<n;i++)
		{
			fscanf(f,"%lf",arr+i);
		}
		start=clock();
		quickSort(arr, 0, n-1);
		end=clock();
		flag=1;
	}
	else if(dist=='u')
	{
		a=(lint *)malloc(n*sizeof(lint));
		for(i=0;i<n;i++)
		{
			fscanf(f,"%lld",a+i);
		}
		start=clock();
		quickSortInt(a,0,n-1);
		end=clock();
		flag=2;
	}
	cpu_time_used=((double)(end-start))/CLOCKS_PER_SEC;
	fclose(f);
	f=fopen(argv[argc-1],"a");
	fprintf(f,"\n\nAfter randomised quicksort, the results are:\n\n");
	fprintf(f,"%lld ",n);
	for(i=0;i<n;i++)
	{
		if(dist=='n')
		{
			fprintf(f,"%lf ",arr[i]);
		}
		else if(dist=='u')
		{
			fprintf(f,"%lld ",a[i]);
		}
	}
	fprintf(f,"\n\nThe number of comparisons is: %lld\n",count);
	fprintf(f,"The number of swaps is: %lld\n",swap);
	fprintf(f,"The time taken: %lf\n",cpu_time_used);
	fprintf(res,"RandomisedQuickSort,%c,%lld,%lld,%lld,%lf\n",dist,n,count,swap,cpu_time_used);
	fclose(f);
	fclose(res);
	if(flag==1)
		free(arr);
	else if(flag==2)
		free(a);
	return 0;
}

