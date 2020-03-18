//random number from normal distribution
#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#include<math.h>

#define PI 3.141592654

double gaussrand()
{
	static double U,V;
	static int phase=0;
	double Z;
	if(phase==0)
	{
		U=(rand()+1.)/(RAND_MAX+2.);
		V=rand()/(RAND_MAX+1.);
		Z=sqrt(-2*log(U))*sin(2*PI*V);
	}
	else
	{
		Z=sqrt(-2*log(U))*cos(2*PI*V);
	}
	phase=1-phase;
	return Z;
}

int main()
{
        int ele,i,m,sd;
	double num;
        FILE *f;
        char fname[100];
        printf("Enter the name of the file: ");
        scanf("%s",fname);
        printf("Enter the number of terms to be generated :");
        scanf("%d",&ele);
	printf("Enter the mean: ");
	scanf("%d",&m);
	printf("Enter the standard deviation: ");
	scanf("%d",&sd);
        f=fopen(fname,"w");
        if(f==NULL)
        {
                printf("File opening error.\n");
                return 0;
        }
	fprintf(f,"%d ",ele);
        for(i=0;i<ele;i++)
        {
                num=gaussrand();
		num=num*sd+m;
                fprintf(f,"%.4lf ",num);
        }
        fclose(f);
        return 0;
}

