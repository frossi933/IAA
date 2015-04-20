#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

float pdfNormal(float s,float c, float x){
    
  return (1.0/(s*sqrt(2.0*M_PI)))*exp(((float)-1.0/2.0)*pow((x-c)/s,2.0));
}

float *genDataSets(float centro, float sigma, int n){

        float *res = malloc(n*sizeof(float));
	float max=pdfNormal(sigma,centro,centro);
	int i=0;
        float a=centro-(5*sigma);
        float b=centro+(5*sigma);

        while(i<n){
		float x = ((((float)rand())/(float)RAND_MAX)*(b-a))+a;	        // x entre centro-5sigma y centro+5sigma
		float y = (((float)rand())/(float)RAND_MAX);		        // y entre 0 y 1
		if(y <= pdfNormal(sigma,centro,x)){
                    //lo acepto
                    res[i]=x;
                    i++;
                }
	}
	return res;
}

// ./genA d n c sten 
int main(int argc, char **argv){

	int d,n;
	float c;
	int i,j;
	char snames[50], sdata[50];
        
	d=atoi(argv[1]);
	n=atoi(argv[2]);
	c=atof(argv[3]);
	strcpy(snames,argv[4]);
	strcpy(sdata,argv[4]);
	strcat(sdata,".data");
	strcat(snames,".names");

        float *clase;

        srand((unsigned) time(NULL));
        
	FILE *data = fopen(sdata,"w+");
        FILE *names = fopen(snames,"w+");
        
        float sigma = c*sqrt(d);

        // Clase 1, centro en (1,1,...,1)
	for(i=0;i<n/2;i++){

            clase = genDataSets(1.0,sigma,d);
        
            for(j=0;j<d;j++)
                fprintf(data,"%f,",clase[j]);
            fprintf(data,"1\n");
            free(clase);
        }
        
        // Clase 0, centro en (-1,-1,...,-1)
	for(i=0;i<n/2;i++){

            clase = genDataSets(-1.0,sigma,d);
        
            for(j=0;j<d;j++)
                fprintf(data,"%f,",clase[j]);
            fprintf(data,"0\n");
            free(clase);
        }

        fprintf(names,"clase0,clase1.\n");
        for(i=0;i<d;i++)
            fprintf(names,"d%d:continuous.\n",i);
        
        fclose(names);
        fclose(data);
}
