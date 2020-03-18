//random number from uniform distribution
#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#include<math.h>

int main(int argc, char *argv[])
{
	int ele,l,u,i,num;
	FILE *f;
	l=atoi(argv[argc-2]);
	u=atoi(argv[argc-1]);
	ele=atoi(argv[argc-3]);
	f=fopen(argv[argc-4],"w");
	fprintf(f,"%d ",ele);
	if(f==NULL)
	{
		printf("File opening error.\n");
		return 0;
	}
	for(i=0;i<ele;i++)
	{
		num= (rand() % (u-l+1))+l;
		fprintf(f,"%d ",num);
	}
	fclose(f);
	return 0;
}

