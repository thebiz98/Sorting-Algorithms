//random number from uniform distribution
#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#include<math.h>

int main()
{
	int ele,l,u,i,num;
	FILE *f;
	char fname[100];
	printf("Enter the name of the file: ");
	scanf("%s",fname);
	printf("Enter the number of terms to be generated :");
	scanf("%d",&ele);
	printf("Enter the range of the distribution: ");
	scanf("%d %d",&l,&u);
	f=fopen(fname,"w");
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

