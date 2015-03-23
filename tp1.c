#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float pdfNormal(float s,float c, float x){
	static float s_aux,a;
	if(s_aux!=s){ 
		a = 1/(s*sqrt(2*M_PI));
		s_aux = s;
	}

	return a*exp((-1/2)*pow((x-c)/s,2));

	//return (1/(s*sqrt(2*M_PI)))*exp((-1/2)*pow((x-c)/s,2));

}

void genDataSets(float centro, int d, int n, float c){

	srand((unsigned) time(NULL));

	float sigma = c * sqrt(d);
	float a=centro-(3*sigma);
	float b=centro+(3*sigma);		// revisar porq 3
	float max=pdfNormal(sigma,centro,centro);
	int i=0;
	
	while(i<n/2){
		float x = (float)(rand()+a)/(float)(RAND_MAX/b);	// x entre centro-3sigma y centro+3sigma
		float y = (float)rand()/(float)(RAND_MAX/max);			// y entre 0 y max
		
		if(y <= pdfNormal(sigma,centro,x))
			//lo acepto
			printf("acepto: %f %f\n",x,y);
		else
			printf("no acepto: %f %f\n",x,y);
			// no lo acepto
		i++;
	}
		
}

// ./gen d n c 
int main(int argc, char **argv){

	int d,n;
	float c;
	
	d=atoi(argv[1]);
	n=atoi(argv[2]);
	c=atof(argv[3]);
	
	FILE *res = fopen("ej1.data","w+");	
	genDataSets(1,d,n,c);
}
