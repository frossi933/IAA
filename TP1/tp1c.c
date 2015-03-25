#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// ./genC n
int main(int argc, char **argv){

    int n,c1=0,c0=0;
    
    n = atoi(argv[1]);
    srand(time(NULL));

    float x,y,r,a;
    
    while(c1<n/2 && c0<n/2){
        x = ((((float)rand())/RAND_MAX)*2.0)-1.0      // genero un flotante x entre -1 y 1
        y = ((((float)rand())/RAND_MAX)*2.0)-1.0      // genero un flotante y entre -1 y 1

        r = sqrt((x*x)+(y*y));
        if()
            
    }
}