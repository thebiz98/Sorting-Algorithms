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

int main(int argc, char *argv[])
{
        int ele,i,m,sd;
	double num;
        FILE *f;
        ele=atoi(argv[argc-3]);
	m=atoi(argv[argc-2]);
	sd=atoi(argv[argc-1]);
        f=fopen(argv[argc-4],"w");
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

