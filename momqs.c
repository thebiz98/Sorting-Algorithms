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

lint randoms(lint low, lint high)
{
	return low+randomize(high-low+1);
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

lint part(lf *arr, lint low, lint high, lf x)
{
	lint i,j,pos=high;
	lf pivot;
	for(i=low;i<high;i++)
	{
		if(arr[i]==x)
			pos=i;
	}
	swap(&arr[pos],&arr[high]);
	pivot=arr[high];
	i=low;
	for(j=low;j<high;j++)
	{
		if(arr[j]<pivot)
		{
			swap(&arr[j],&arr[i]);
			i++;
		}
	}
	swap(&arr[i],&arr[high]);
	return i;
}

lf find_median(lf *arr, lint n)
{
	lf b[10];
	lint i,j;
	lf x;
	for(i=0;i<n;i++)
		b[i]=arr[i];
	for(i=1;i<n;i++)
	{
		x=b[i];
		j=i-1;
		while(b[j]>x)
		{
			b[j+1]=b[j];
			j--;
		}
		b[j+1]=x;
	}
	x=b[n/2];
	return x;
}

lf worstCaseSelect(lf *arr, lint l, lint u, lint k, lint choice)
{
	if(k>0&&k<=u)
	{
		lint n=u-l+1,i,pos;
		lf m;
		lf medians[(n+(choice-1))/choice];
		for(i=0;i<(n/choice);i++)
			medians[i]=find_median(arr+l+i*choice,choice);
		if(i*(n/choice)!=n)
		{
			medians[i]=find_median(arr+l+i*choice,n%choice);
			i++;
		}
		m=(i==1)?medians[i-1]:worstCaseSelect(medians,0,i-1,i/2,choice);
		pos=part(arr,l,u,m);
		if(pos-l==k-1)
			return arr[pos];
		else if(pos-l>k-1)
			return worstCaseSelect(arr,l,pos-1,k,choice);
		return worstCaseSelect(arr,pos+1,u,k-pos+l-1,choice);
	}
}	

lint partition(lf *arr, lint l, lint h, lint x)
{
	lint i,pos=h,j;
	for(i=l;i<h;i++)
	{
		if(arr[i]==x)
		{
			pos=i;
			break;
		}
	}
	swap(&arr[pos],&arr[h]);
	swaps++;
	lf pivot=arr[h],t;
	i=l-1;
	for(j=l;j<h;j++)
	{
		count++;
		if(arr[j]<pivot)
		{
			swaps++;
			i++;
			swap(&arr[j],&arr[i]);
		}
	}
	swaps++;
	swap(&arr[i+1],&arr[h]);
	return i+1;
}

void momquickSort(lf *arr, lint low, lint high, lint choice)
{
	if(low<high)
	{
		lint i,j;
		lf *copy=(lf *)malloc((high-low+1)*sizeof(lf));
		for(i=low,j=0;i<=high;i++,j++)
			copy[j]=arr[i];
		lint r=worstCaseSelect(copy,0,j-1,j/2,choice);
		free(copy);
		lint pi=partition(arr,low,high,r);
		momquickSort(arr,low,pi-1,choice);
		momquickSort(arr,pi+1,high,choice);
	}
}

int main(int argc, char *argv[])
{
	FILE *f=fopen(argv[argc-1],"r");
	FILE *res=fopen("results.csv","a");
	lint n,i,x=1,choice=3;
	lint n2,n3,tmp;
	lf n1,c1,c2,c3,c4;
	char dist=argv[argc-1][0];
	int len=strlen(argv[argc-1])+15;
	char out_file[len];
	out_file[0]='\0';
	strcat(out_file,argv[argc-1]);
	strcat(out_file,"momquickcheck30");
	lf *a;
	fscanf(f,"%lld",&n);
	a=(lf *)malloc(n*sizeof(lf));
	for(i=0;i<n;i++)
	{
		fscanf(f,"%lf",a+i);
	}
	fclose(f);
	srand(time(0));
	for(;x<=15;x++)
	{
		count=0;
		swaps=0;
		if(x==1)
			printf("\nFor partition size: %lld\n",choice);
		if(x==6)
		{
			choice=5;
			out_file[len-2]='5';
			out_file[len-1]='0';
			printf("\nFor partition size: %lld\n",choice);
		}
		else if(x==11)
		{
			choice=7;
			out_file[len-2]='7';
			out_file[len-1]='0';
			printf("\nFor partition size: %lld\n",choice);
		}
		if(x%5!=0)
			printf("\nShuffle no.: %lld\n",x%5);
		else
			printf("\nShuffle no.: %d\n",5);
		shuffle(a,n);
		out_file[len-1]++;
		f=fopen(out_file,"w");
		printf("The output is being written to the file: %s\n",out_file);
		start=clock();
		momquickSort(a,0,n-1,choice);
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
		if(x%5!=0)
			fprintf(res,"MoM_Quick_Sort,%c,%lld,%lld,%lf,%lld,%lld,%lld,%lf,%lf,%lf,%lf,%lld,%lf,%lld\n",dist,(x%5),n,n1,n2,n3,count,c1,c2,c3,c4,swaps,cpu_time_used,choice);
		else
			fprintf(res,"MoM_Quick_Sort,%c,%d,%lld,%lf,%lld,%lld,%lld,%lf,%lf,%lf,%lf,%lld,%lf,%lld\n",dist,5,n,n1,n2,n3,count,c1,c2,c3,c4,swaps,cpu_time_used,choice);
	}
	fprintf(res,"\n");
	fclose(res);
	free(a);
	return 0;
}

