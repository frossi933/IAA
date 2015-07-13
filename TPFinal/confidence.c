#include <math.h>
#include <stdio.h>
#include <stdlib.h>
// confidence k h1 h2

int main(int argc, char **argv){

	int i;
	int k=atoi(argv[1]);
	FILE *h1=fopen(argv[2], "r+");
	FILE *h2=fopen(argv[3], "r+");

	double ret, s, sum=0, delta=0;
	double *e1=(double *)malloc(sizeof(double)*k);
	double *e2=(double *)malloc(sizeof(double)*k);

	for(i=0;i<k;i++){
		fscanf(h1, "%lf\n", &e1[i]);
		//printf("%lf\n",e1[i]);
		fscanf(h2, "%lf\n", e2+i);
		//printf("%lf\n",e2[i]);
		delta+=fabs(e1[i]-e2[i]);
	}
	delta=(double)(delta/(k*1.0));

	for(i=0;i<k;i++)
		sum+=exp2(fabs(e1[i]-e2[i]) - delta);

	s=sqrt((1.0/(k*(k-1)))*sum);
	ret=2.26*s;
	printf("Resultado: %f\n", ret);
	
}
