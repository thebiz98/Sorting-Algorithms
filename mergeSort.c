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

lint count=0,move=0;
clock_t start,end;
double cpu_time_used;

void merge(lf *arr, lint l, lint m, lint r)
{
	lint a=m-l+1;
	lint b=r-m,i=l,j=0,k=0;
	lf le[a];
	lf re[b];
	while(j<a)
	{
		le[j]=arr[i];
		j++;
		i++;
	}
	while(k<b)
	{
		re[k]=arr[i];
		k++;
		i++;
	}
	j=0;
	k=0;
	i=l;
	while(j<a&&k<b)
	{
		count++;
		move++;
		if(le[j]<=re[k])
		{
			arr[i]=le[j];
			j++;
		}
		else
		{
			arr[i]=re[k];
			k++;
		}
		i++;
	}
	while(j<a)
	{
		move++;
		arr[i]=le[j];
		i++;
		j++;
	}
	while(k<b)
	{
		move++;
		arr[i]=re[k];
		i++;
		k++;
	}
}

void mergeSort(lf *arr, lint l, lint r)
{
	if(l<r)
	{
		lint m=l+(r-l)/2;
		mergeSort(arr,l,m);
		mergeSort(arr,m+1,r);
		merge(arr,l,m,r);
	}
}
void mergeInt(lint *arr, lint l, lint m, lint r)
{
	lint a=m-l+1;
	lint b=r-m,i=l,j=0,k=0;
	lint le[a];
	lint re[b];
	while(j<a)
	{
		le[j]=arr[i];
		j++;
		i++;
	}
	while(k<b)
	{
		re[k]=arr[i];
		k++;
		i++;
	}
	j=0;
	k=0;
	i=l;
	while(j<a&&k<b)
	{
		count++;
		move++;
		if(le[j]<=re[k])
		{
			arr[i]=le[j];
			j++;
		}
		else
		{
			arr[i]=re[k];
			k++;
		}
		i++;
	}
	while(j<a)
	{
		move++;
		arr[i]=le[j];
		i++;
		j++;
	}
	while(k<b)
	{
		move++;
		arr[i]=re[k];
		i++;
		k++;
	}
}

void mergeSortInt(lint *arr, lint l, lint r)
{
	if(l<r)
	{
		lint m=l+(r-l)/2;
		mergeSortInt(arr,l,m);
		mergeSortInt(arr,m+1,r);
		mergeInt(arr,l,m,r);
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
		flag=1;
		arr=(lf *)malloc(n*sizeof(lf));
		for(i=0;i<n;i++)
		{
			fscanf(f,"%lf",arr+i);
		}
		start=clock();
		mergeSort(arr, 0, n-1);
		end=clock();
	}
	else if(dist=='u')
	{
		flag=2;
		a=(lint *)malloc(n*sizeof(lint));
		for(i=0;i<n;i++)
		{
			fscanf(f,"%lld",a+i);
		}
		start=clock();
		mergeSortInt(a,0,n-1);
		end=clock();
	}
	cpu_time_used=((double)(end-start))/CLOCKS_PER_SEC;
	f=fopen(argv[argc-1],"a");
	fprintf(f,"\n\nAfter mergesort the results are:\n\n");
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
	fprintf(f,"The number of moves is: %lld\n",move);
	fprintf(f,"The time taken is: %lf\n",cpu_time_used);
	fprintf(res,"MergeSort,%c,%lld,%lld,%lld,%lf\n",dist,n,count,move,cpu_time_used);
	fclose(f);
	fclose(res);
	if(flag==1)
		free(arr);
	else if(flag==2)
		free(a);
	return 0;
}

