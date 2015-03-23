#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float pdfNormal(float s,float c, float x){
	static float s_aux,a;
	if(s_aux!=s){ 
		a = 1/(s*sqrt(2*M_PI));
		s_aux = s;
	}

	//return a*exp((-1/2)*pow((x-c)/s,2));

	return (1/(s*sqrt(2*M_PI)))*exp((-1/2)*pow((x-c)/s,2));

}

float *genDataSets(float centro, float sigma, int n){


        
        float *res = malloc(n*sizeof(float));
	float a=centro-(3*sigma);
	float b=centro+(3*sigma);		// revisar porq 3
	float max=pdfNormal(sigma,centro,centro);
	int i=0;
	
	while(i<n){
		float x = (float)(rand()+a)/(float)(RAND_MAX/b);	// x entre centro-3sigma y centro+3sigma
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

// ./genB d n c 
int main(int argc, char **argv){

	int d,n;
	float c;
	int i, j;
        
	d=atoi(argv[1]);
	n=atoi(argv[2]);
	c=atof(argv[3]);

        srand((unsigned) time(NULL));	
	FILE *res = fopen("ej1b.data","w+");	

        float **clases = malloc(d*sizeof(float *));
        
        // Clase 1, centro en (1,0,0,...,0)
        clases[0] = genDataSets(1,c,n/2);
	for(i=1;i<d;i++)
            clases[i] = genDataSets(0,c,n/2);
        
        
        for(j=0;j<n/2;j++){
            for(i=0;i<d;i++)
                fprintf(res,"%f,",clases[i][j]);
            fprintf(res,"1\n");
        }
        
        // Clase 0, centro en (-1,0,0,...,0)
        clases[0] = genDataSets(-1,c,n/2);
	for(i=1;i<d;i++)
            clases[i] = genDataSets(0,c,n/2);
        
        for(j=0;j<n/2;j++){
            for(i=0;i<d;i++)
                fprintf(res,"%f,",clases[i][j]);
            fprintf(res,"0\n");
        }

        for(i=0;i<d;i++)
            free(clases[i]);
        free(clases);
        fclose(res);
}
