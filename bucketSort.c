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
	lf data;
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

void bucketSort(lf *a, lint n)
{
	lint i=0,x,k,size,prev,l,j;
	lf tmp;
	node **arr=(node **)malloc((n)*sizeof(node *));
	node *t;
	for(i=0;i<n+1;i++)
		arr[i]=NULL;
	for(i=0;i<n;i++)
	{
		x=a[i]*n;
		arr[x]=addNode(arr[x],a[i]);
	}
	k=0;
	for(i=0;i<n;i++)
	{
		if(arr[i]!=NULL)
		{
			t=arr[i];
			bucky++;
			size=0;
			prev=k;
			while(t!=NULL)
			{
				a[k]=t->data;
				k++;
				size++;
				t=t->next;
			}
			if(maxb<size)
				maxb=size;
			for(j=prev+1;j<(prev+size);j++)
			{
				tmp=a[j];
				l=j-1;
				count++;
				while(l>=0&&a[l]>tmp)
				{
					count++;
					a[l+1]=a[l];
					l--;
				}
				a[l+1]=tmp;
			}
		}
	}
	free(arr);
}

int main(int argc, char *argv[])
{
	FILE *f=fopen(argv[argc-1],"r");
	FILE *res=fopen("results.csv","a");
	lint n,i;
	lint n2,n3,tmp;
	lf n1,c1,c2,c3,c4;
	char dist=argv[argc-1][4];
	int len=strlen(argv[argc-1])+11;
	char out_file[len];
	out_file[0]='\0';
	strcat(out_file,argv[argc-1]);
	strcat(out_file,"bucketcheck");
	lf *a;
	fscanf(f,"%lld",&n);
	a=(lf *)malloc(n*sizeof(lf));
	for(i=0;i<n;i++)
	{
		fscanf(f,"%lf",a+i);
	}
	fclose(f);
	srand(time(0));
	count=0;
	bucky=0;
	maxb=0;
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
	fprintf(res,"Bucket_Sort,%c,%lld,%lf,%lld,%lld,%lld,%lf,%lf,%lf,%lf,%lld,%lf,%lld\n",dist,n,n1,n2,n3,count,c1,c2,c3,c4,bucky,cpu_time_used,maxb);
	fprintf(res,"\n");
	fclose(res);
	free(a);
	return 0;
}
