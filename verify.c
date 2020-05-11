#include<stdio.h>
#include<stdlib.h>

#define lint long long int
#define lf double

int main(int argc, char *argv[])
{
	FILE *f=fopen(argv[argc-1],"r");
	lint i,n;
	lf tmp,prev;
	fscanf(f,"%lld",&n);
	for(i=0;i<n;i++)
	{
		fscanf(f,"%lf",&tmp);
		if(i==0)
			prev=tmp;
		else
		{
			if(prev>tmp)
			{
				printf("The faulty pair is: %lf and %lf\n",prev,tmp);
				printf("Dataset not sorted\n");
				fclose(f);
				return 0;
			}
			prev=tmp;
		}
	}
	printf("Dataset sorting verified.\n");
	fclose(f);
	return 0;
}
