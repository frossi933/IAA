#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Clase 0: theta/4pi < r < (theta+pi)/4pi
// Clase 1: el resto...


// ./genC n
int main(int argc, char **argv){

    int n,c1=0,c0=0;    
    FILE *data = fopen("ej1c.data", "w+");
    FILE *names = fopen("ej1c.names", "w+");
    
    n = atoi(argv[1]);
    srand(time(NULL));

    float x,y,r,r0,r1,t;
    
    while(c1<n/2 || c0<n/2){
        x = ((((float)rand())/RAND_MAX)*2.0)-1.0;       // genero un flotante x entre -1 y 1
        y = ((((float)rand())/RAND_MAX)*2.0)-1.0;       // genero un flotante y entre -1 y 1

        r = sqrt((x*x)+(y*y));                          // radio de las coordenadas polares
        
        if(r<1){
            t = atan2(y,x);                             // theta de las coordanadas polares (entre 0 y 2pi)
            r0 = t/(4.0*M_PI);
            r1 = r0+0.25;                               // (t+pi)/4pi = (t/4pi)+(pi/4pi) = r0 + 1/4
            
            if( (r > r0 && r < r1) || (r > (r0+0.5) && r < (r1+0.5)) || (r > (r0+1)) ){
                // clase 0
                if(c0 >= n/2)
                    continue;
                else{
                    fprintf(data,"%f,%f,0\n",x,y);
                    c0++;
                }
            } else {
                // clase 1
                if(c1 >= n/2)
                    continue;
                else {
                    fprintf(data,"%f,%f,1\n",x,y);
                    c1++;
                }
            }
        }
    }
    
    fprintf(names,"clase0,clase1.\nx:continuous.\ny:continuous.\n");    
    
    fclose(data);
    fclose(names);
    return 0;
}