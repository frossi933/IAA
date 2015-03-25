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

float *genDataSets(float centro, float sigma, int n){

        float *res = malloc(n*sizeof(float));
	float max=pdfNormal(sigma,centro,centro);
	int i=0;
        float a=centro-(3*sigma);
        float b=centro+(3*sigma);		                         // revisar porq 3

        while(i<n){
		float x = ((((float)rand())/RAND_MAX)*(b-a))+a;	         // x entre centro-3sigma y centro+3sigma
		float y = (float)rand()/(float)(RAND_MAX/max);		 // y entre 0 y max
		if(y <= pdfNormal(sigma,centro,x)){
                    //lo acepto
                    printf("%f,",x);                                 // sacar
                    res[i]=x;
                    i++;
                } else
                    // no lo acepto
                    printf("no acepto: %f %f\n",x,y);               // sacar
	}
	return res;
}

// ./genA d n c 
int main(int argc, char **argv){

	int d,n;
	float c;
	int i,j;
        
	d=atoi(argv[1]);
	n=atoi(argv[2]);
	c=atof(argv[3]);
	
        float *clase;

        srand((unsigned) time(NULL));
        
	FILE *res = fopen("ej1a.data","w+");	
        float sigma = c*sqrt(d);

        // Clase 1, centro en (1,1,...,1)
	for(i=0;i<n/2;i++){

            clase = genDataSets(1,sigma,d);
        
            for(j=0;j<d;j++)
                fprintf(res,"%f,",clase[j]);
            fprintf(res,"1\n");
            free(clase);
        }
        printf("\nclase 0\n");
        
        // Clase 0, centro en (-1,-1,...,-1)
	for(i=0;i<n/2;i++){

            clase = genDataSets(-1,sigma,d);
        
            for(j=0;j<d;j++)
                fprintf(res,"%f,",clase[j]);
            fprintf(res,"0\n");
            free(clase);
        }

        fclose(res);
}
