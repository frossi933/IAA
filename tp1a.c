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

float *genDataSets(float centro, float sigma, int n,float x){


        
        float *res = malloc(n*sizeof(float));
	float max=pdfNormal(sigma,centro,centro);
	int i=0;
	
	while(i<n){
		float y = (float)rand()/(float)(RAND_MAX/max);			// y entre 0 y max
		if(y <= pdfNormal(sigma,centro,x)){
			//lo acepto
			printf("acepto: %f %f\n",x,y);
                        res[i]=y;
                        i++;
                } else
                        printf("no acepto: %f %f\n",x,y);
                        // no lo acepto
	}
	return res;
}

// ./genA d n c 
int main(int argc, char **argv){

	int d,n;
	float c;
	int i;
        
	d=atoi(argv[1]);
	n=atoi(argv[2]);
	c=atof(argv[3]);
	
        float *clase;

        srand((unsigned) time(NULL));
        
	FILE *res = fopen("ej1a.data","w+");	
        float sigma = c*sqrt(d);
        // Clase 1, centro en (1,1,...,1)
	for(i=0;i<n/2;i++){

            float a=1-(3*sigma);
            float b=1+(3*sigma);		// revisar porq 3
            float x = (float)(rand()+a)/(float)(RAND_MAX/b);	// x entre centro-3sigma y centro+3sigma
            clase = genDataSets(1,sigma,d-1,x);
        
            int j;
            fprintf(res,"%f,",x);
            for(j=0;j<d-1;j++)
                fprintf(res,"%f,",clase[j]);
            fprintf(res,"1\n");
            free(clase);
        }
        
        // Clase 0, centro en (-1,-1,...,-1)
	for(i=0;i<n/2;i++){

            float a=1-(3*sigma);
            float b=1+(3*sigma);		// revisar porq 3
            float x = (float)(rand()+a)/(float)(RAND_MAX/b);	// x entre centro-3sigma y centro+3sigma
            clase = genDataSets(-1,sigma,d-1,x);
        
            int j;
            fprintf(res,"%f,",x);
            for(j=0;j<d-1;j++)
                fprintf(res,"%f,",clase[j]);
            fprintf(res,"0\n");
            free(clase);
        }

        fclose(res);
}
