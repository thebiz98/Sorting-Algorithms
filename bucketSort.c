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

typedef struct snode{
	double data;
	struct snode *next;
}node;

lint count=0,bucky=0,maxb=0;
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

void printarray(lf *a, lint l, lint h)
{
	lint i;
	printf("l= %lld, h= %lld\n",l,h);
	for(i=l;i<h;i++)
		printf("%lf ",a[i]);
	printf("\n\n");
}

node *addNode(node *start, lf item)
{
	node *t=(node *)malloc(sizeof(node));
	t->data=item;
	t->next=NULL;
	if(start==NULL)
		return t;
	node *tmp=NULL;
	tmp=start;
	while(tmp->next!=NULL)
		tmp=tmp->next;
	tmp->next=t;
	return start;
}

void sort(lf *a, lint l, lint h)
{
	lint i,j;
	lf x;
	for(i=l+1;i<h;i++)
	{
		x=a[i];
		j=i-1;
		count++;
		while(a[j]>x)
		{
			count++;
			a[j+1]=a[j];
			j--;
		}
		a[j+1]=x;
	}
}

void bucketSort(lf *a, lint n)
{
	lint i=0,x,k=0,size;
	node *t=NULL;
	node **arr=(node **)malloc(n*sizeof(node *));
	while(i<n)
	{
		arr[i]=NULL;
		i++;
	}
	i=0;
	while(i<n)
	{
		x=a[i]*n;
		arr[x]=addNode(arr[x],a[i]);
		i++;
	}
	i=0;
	while(i<n)
	{
		if(arr[i]!=NULL)
		{
			size=0;
			bucky++;
			t=arr[i];
			while(t!=NULL)
			{
				a[k]=t->data;
				t=t->next;
				k++;
				size++;
			}
			if(size>maxb)
				maxb=size;
			printarray(a,k-size,k);
			sort(a,k-size,k);
			printarray(a,k-size,k);
		}
		i++;
	}
	free(arr);
}


int main(int argc, char *argv[])
{
	FILE *f=fopen(argv[argc-1],"r");
	FILE *res=fopen("results.csv","a");
	lint n,i,x=1;
	lint n2,n3,tmp;
	lf n1,c1,c2,c3,c4;
	char dist=argv[argc-1][0];
	int len=strlen(argv[argc-1])+12;
	char out_file[len];
	out_file[0]='\0';
	strcat(out_file,argv[argc-1]);
	strcat(out_file,"bucketcheck0");
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
		bucky=0;
		maxb=0;
		printf("\nShuffle no.: %lld\n",x);
		shuffle(a,n);
		out_file[len-1]++;
		f=fopen(out_file,"w");
		printf("\nThe output is being written to the file: %s\n",out_file);
		start=clock();
		bucketSort(a,n);
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
		printf("The number of buckets formed is: %lld\n",bucky);
		printf("The maximum bucket size is: %lld\n",maxb);
		printf("The time taken for the sorting is: %lf\n",cpu_time_used);
		fprintf(res,"Bucket_Sort,%c,%lld,%lld,%lf,%lld,%lld,%lld,%lf,%lf,%lf,%lf,%lld,%lf,%lld\n",dist,x,n,n1,n2,n3,count,c1,c2,c3,c4,bucky,cpu_time_used,maxb);
	}
	fprintf(res,"\n");
	fclose(res);
	return 0;
}
