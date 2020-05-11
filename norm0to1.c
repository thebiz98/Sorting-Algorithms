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

int main(int argc, char *argv[])
{
	FILE *f=fopen(argv[argc-1],"r");
	lint filesize=strlen(argv[argc-1])+4;
	char fname[filesize];
	lint n,i;
	lf *a,min,max;
	fname[0]='\0';
	strcat(fname,"norm");
	strcat(fname,argv[argc-1]);
	fscanf(f,"%lld",&n);
	a=(lf *)malloc(n*sizeof(lf));
	for(i=0;i<n;i++)
	{
		fscanf(f,"%lf",a+i);
		if(i==0)
		{
			min=a[0];
			max=a[0];
		}
		else if(a[i]<min)
			min=a[i];
		else if(a[i]>max)
			max=a[i];
	}
	fclose(f);
	printf("The normalised data is being written to the file: %s\n",fname);
	f=fopen(fname,"w");
	fprintf(f,"%lld ",n);
	i=0;
	while(i<n)
	{
		fprintf(f,"%lf ",(max-a[i])/(max-min+1));
		i++;
	}
	fclose(f);
	free(a);
	return 0;
}

