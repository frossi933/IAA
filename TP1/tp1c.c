#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Clase 0: theta/4pi < r < (theta+pi)/4pi
// Clase 1: el resto...


// ./genC n
int main(int argc, char **argv){

    int n,c1=0,c0=0;    
    FILE *res = fopen("ej1c.data", "w+");
    
    n = atoi(argv[1]);
    srand(time(NULL));

    float x,y,r,t;
    
    while(c1<n/2 || c0<n/2){
        x = ((((float)rand())/RAND_MAX)*2.0)-1.0;       // genero un flotante x entre -1 y 1
        y = ((((float)rand())/RAND_MAX)*2.0)-1.0;       // genero un flotante y entre -1 y 1

        r = sqrt((x*x)+(y*y));                          // radio de las coordenadas polares
        
        if(r<1){
            t = atan(y/x);                              // theta de las coordanadas polares
            if(r > (t/(4.0*M_PI)) && r < (t+M_PI)/(4.0*M_PI)){
                // clase 0
                if(c0 >= n/2)
                    continue;
                else{
                    fprintf(res,"%f,%f,0\n",x,y);
                    c0++;
                }
            } else {
                // clase 1
                if(c1 >= n/2)
                    continue;
                else {
                    fprintf(res,"%f,%f,1\n",x,y);
                    c1++;
                }
            }
        }
    }
    
    
    fclose(res);
}