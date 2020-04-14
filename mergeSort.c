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

void merge(lf *arr, lint l, lint m, lint r)
{
	lint x=m-l+1;
	lint y=r-m;
	lint i=0,j=0,k=0;
	lf *L=(lf *)malloc(x*sizeof(lf));
	lf *R=(lf *)malloc(y*sizeof(lf));
	for(i=0;i<x;i++)
	{
		L[i]=arr[l+i];
	}
	for(i=0;i<y;i++)
	{
		R[i]=arr[m+i+1];
	}
	i=0;
	j=0;
	for(k=l;k<=r;k++)
	{
		if((i<x)&&(j<y))
		{
			count++;
			move++;
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
			move++;
			arr[k]=L[i];
			i++;
		}
		else if(i>=x&&j<y)
		{
			move++;
			arr[k]=R[j];
			j++;
		}
	}
	free(L);
	free(R);
}

void mergeSort(lf *arr, lint l, lint r)
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
	strcat(out_file,"mergecheck0");
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
		move=0;
		printf("\nShuffle no.: %lld\n",x);
		shuffle(a,n);
		out_file[len-1]++;
		f=fopen(out_file,"w");
		printf("\nThe output is being written to the file: %s\n",out_file);
		start=clock();
		mergeSort(a,0,n-1);
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
		printf("The number of moves is: %lld\n",move);
		printf("The time taken for the sorting is: %lf\n",cpu_time_used);
		fprintf(res,"Merge_Sort,%c,%lld,%lld,%lf,%lld,%lld,%lld,%lf,%lf,%lf,%lf,%lld,%lf\n",dist,x,n,n1,n2,n3,count,c1,c2,c3,c4,move,cpu_time_used);
	}
	fprintf(res,"\n");
	fclose(res);
	free(a);
	return 0;
}
