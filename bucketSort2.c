#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<time.h>

#define lint long long int

typedef struct snode
{
	double data;
	struct snode *next;
}node;

lint count=0;
clock_t start,end;
double cpu_time_used;

node *addNodeSorted(node *start,double item)
{
	node *t=(node *)malloc(sizeof(node));
	t->data=item;
	t->next=NULL;
	if(start==NULL)
	{
		return t;
	}
	count++;
	if(start->data>=item)
	{
		t->next=start;
		return t;
	}
	node *p=NULL,*q=NULL;
	p=start;
	while(p!=NULL)
	{
		count++;
		if(p->data>=item)
		{
			q->next=t;
			t->next=p;
			return start;
		}
		q=p;
		p=p->next;
	}
	q->next=t;
	return start;
}

void bucket(double *a,lint n)
{
	lint i=0,x,k=0;
	node *t=NULL;
	node **arr=(node **)malloc((n)*sizeof(node *));
	while(i<n)
	{
		arr[i]=NULL;
		i++;
	}
	i=0;
	while(i<n)
	{
		x=a[i]*n;
		//printf("x= %lld item= %lf\n",x,a[i]);
		arr[x]=addNodeSorted(arr[x],a[i]);
		i++;
	}
	i=0;
	while(i<n)
	{
		if(arr[i]!=NULL)
		{
			t=arr[i];
			while(t!=NULL)
			{
				a[k]=t->data;
				t=t->next;
				k++;
			}
		}
		i++;
	}
	a[k]=1.0;
	k++;
	free(arr);
}

int main(int argc, char *argv[])
{
	FILE *f=fopen(argv[argc-1],"r");
	FILE *res=fopen("results.csv","a");
	char dist=argv[argc-1][4];
	lint n,i;
	fscanf(f,"%lld",&n);
	double *a=(double *)malloc(n*sizeof(double));
	for(i=0;i<n;i++)
	{
		fscanf(f,"%lf",&a[i]);
	}
	start=clock();
	bucket(a,n);
	end=clock();
	cpu_time_used=((double)(end-start))/CLOCKS_PER_SEC;
	fclose(f);
	f=fopen(argv[argc-1],"a");
	fprintf(f,"\n\nAfter bucketsort, the results are:\n\n");
	fprintf(f,"%lld ",n);
	for(i=0;i<n;i++)
	{
		fprintf(f,"%lf ",a[i]);
	}
	fprintf(f,"\n\nThe number of comparisons is: %lld\n",count);
	fprintf(f,"The time taken is: %lf\n",cpu_time_used);
	fprintf(res,"BucketSort,%c,%lld,%lld,%d,%lf\n",dist,n,count,0,cpu_time_used);
	fclose(res);
	fclose(f);
	free(a);
	return 0;
}

