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
	return (rand()%n+1);
}

void shuffle(lf *a, lint n)
{
	lint i,index;
	for(i=0;i<n;i++)
	{
		index=randomize(n);
		swap(&a[i],&a[index]);
	}
}

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

int main(int argc, char *argv[])
{
	FILE *f=fopen(argv[argc-1],"r");
	FILE *res=fopen("results.csv","a");
	char dist=argv[argc-1][0];
	lf *arr;
	lint n,i,shuff=1;
	lf n1,n2,n3,c1,c2,c3,c4;
	lint len=strlen(argv[argc-1])+5+5;
	char out_file[len+1];
	out_file[0]='\0';
	strcat(out_file,argv[argc-1]);
	strcat(out_file,"merge");
	strcat(out_file,"check");
	srand(time(0));
	fscanf(f,"%lld",&n);
	arr=(lf *)malloc(n*sizeof(lf));
	for(i=0;i<n;i++)
	{
		fscanf(f,"%lf",arr+i);
	}
	fclose(f);
	for(;shuff<=5;shuff++)
	{
		count=0;
		move=0;
		printf("Shuffle no.: %lld\n",shuff);
		start=clock();
		mergeSort(arr, 0, n-1);
		end=clock();
		cpu_time_used=((double)(end-start))/CLOCKS_PER_SEC;
		out_file[len]=(char)(shuff+'0');
		f=fopen(out_file,"w");
		printf("The output is written to file: %s\n\n",out_file);
		fprintf(f,"%lld ",n);
		for(i=0;i<n;i++)
		{
			fprintf(f,"%lf ",arr[i]);
		}
		printf("\n\nThe number of comparisons is: %lld\n",count);
		printf("The number of moves is: %lld\n",move);
		printf("The time taken is: %lf\n\n",cpu_time_used);
		n1=n*(log(n)/log(2));
		n2=n*n;
		n3=10*n;
		c1=count/n;
		c2=count/n1;
		c3=count/n2;
		c4=count/n3;
		fprintf(res,"MergeSort,%c,%lld,%lld,%lf,%lf,%lf,%lld,%lf,%lf,%lf,%lf,%lld,%lf\n",dist,shuff,n,n1,n2,n3,count,c1,c2,c3,c4,move,cpu_time_used);
		fclose(f);
		shuffle(arr,n);
	}
	fprintf(res,"\n");
	fclose(res);
	free(arr);
	return 0;
}

