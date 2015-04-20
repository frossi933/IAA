#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

float pdfNormal(float s,float c, float x){

    return (1.0/(s*sqrt(2.0*M_PI)))*expf((((float)-1.0/2.0))*pow((x-c)/s,2.0));
}

float *genDataSets(float centro, float sigma, int n){
        
        float *res = malloc(n*sizeof(float));
	float a=centro-(5*sigma);
	float b=centro+(5*sigma);
	float max=pdfNormal(sigma,centro,centro);
	int i=0;
	
	while(i<n){
		float x = ((((float)rand())/RAND_MAX)*(b-a))+a;   // x entre centro-3sigma y centro+3sigma
		float y = (float)rand()/(float)RAND_MAX;          // y entre 0 y 1
		
		if(y <= pdfNormal(sigma,centro,x)){
			//lo acepto
                        res[i]=x;
                        i++;
                }
	}
	return res;
}

// ./genB d n c sten 
int main(int argc, char **argv){

	int d,n;
	float c;
	int i, j;
        char snames[50],sdata[50];

	d=atoi(argv[1]);
	n=atoi(argv[2]);
	c=atof(argv[3]);
	strcpy(sdata,argv[4]);
	strcpy(snames,argv[4]);
	strcat(snames,".names");
	strcat(sdata,".data");

        srand((unsigned) time(NULL));	

        FILE *data = fopen(sdata,"w+");	
        FILE *names = fopen(snames,"w+");
        
        float **clases = malloc(d*sizeof(float *));
        
        // Clase 1, centro en (1,0,0,...,0)
        clases[0] = genDataSets(1,c,n/2);
	for(i=1;i<d;i++)
            clases[i] = genDataSets(0,c,n/2);
        
        for(j=0;j<n/2;j++){
            for(i=0;i<d;i++)
                fprintf(data,"%f,",clases[i][j]);
            fprintf(data,"1\n");
        }
        
        // libero los datos de la clase 1...
        for(i=0;i<d;i++)
            free(clases[i]);

        
        // Clase 0, centro en (-1,0,0,...,0)
        clases[0] = genDataSets(-1,c,n/2);
	for(i=1;i<d;i++)
            clases[i] = genDataSets(0,c,n/2);
        
        for(j=0;j<n/2;j++){
            for(i=0;i<d;i++)
                fprintf(data,"%f,",clases[i][j]);
            fprintf(data,"0\n");
        }

        fprintf(names,"clase0,clase1.\n");

        for(i=0;i<d;i++){
            free(clases[i]);                                // libero los datos de la clase 0
            fprintf(names,"d%d:continuous.\n",i);           // completo el archivo .names
        }

        free(clases);
        fclose(data);
        fclose(names);
}
