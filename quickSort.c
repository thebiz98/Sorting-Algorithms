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

void swap(lf *a, lf *b)
{
	lf tmp=*a;
	*a=*b;
	*b=tmp;
}

lint randomize(lint n)
{
	return (rand()%n);
}

void shuffle(lf *a, lint n)
{
	lint i,x;
	for(i=0;i<n;i++)
	{
		x=randomize(n);
		swap(&a[i],&a[x]);
	}
}

int partition(lf *arr, lint l, lint h)
{
	lf pivot=arr[h],t;
	lint i=l-1;
	lint j;
	for(j=l;j<h;j++)
	{
		count++;
		if(arr[j]<pivot)
		{
			swaps++;
			i++;
			t=arr[j];
			arr[j]=arr[i];
			arr[i]=t;
		}
	}
	swaps++;
	t=arr[i+1];
	arr[i+1]=arr[h];
	arr[h]=t;
	return i+1;
}

void quickSort(lf *arr, lint low, lint high)
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
	FILE *f=fopen(argv[argc-1],"r");
	FILE *res=fopen("results.csv","a");
	lint n,i,x=1;
	lint n2,n3,tmp;
	lf n1,c1,c2,c3,c4;
	char dist=argv[argc-1][0];
	int len=strlen(argv[argc-1])+11;
	char out_file[len];
	out_file[0]='\0';
	strcat(out_file,argv[argc-1]);
	strcat(out_file,"quickcheck");
	out_file[len-1]='0';
	lf *a;
	fscanf(f,"%lld",&n);
	a=(lf *)malloc(n*sizeof(lf));
	for(i=0;i<n;i++)
	{
		fscanf(f,"%lf",a+i);
	}
	fclose(f);
	srand(time(0));
	for(;x<=5;x++)
	{
		count=0;
		swaps=0;
		printf("\nShuffle no.: %lld\n",x);
		shuffle(a,n);
		out_file[len-1]++;
		f=fopen(out_file,"w");
		printf("The output is being written to the file: %s\n",out_file);
		start=clock();
		quickSort(a,0,n-1);
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
		fclose(f);
		n1=n*(log(n)/log(2));
		n2=n*n;
		n3=10*n;
		c1=count/(n*1.0);
		c2=count/n1;
		c3=count/(n2*1.0);
		c4=count/(n3*1.0);
		printf("The number of comparisons is: %lld\n",count);
		printf("The number of swaps is: %lld\n",swaps);
		printf("The time taken for the sorting is: %lf\n",cpu_time_used);
		fprintf(res,"Quick_Sort,%c,%lld,%lld,%lf,%lld,%lld,%lld,%lf,%lf,%lf,%lf,%lld,%lf\n",dist,x,n,n1,n2,n3,count,c1,c2,c3,c4,swaps,cpu_time_used);
	}
	fprintf(res,"\n");
	fclose(res);
	free(a);
	return 0;
}

