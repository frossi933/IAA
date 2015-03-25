#include <stdlib.h>
#include <stdio.h>

// ./plot file n
int main(int argc, char **argv){

    FILE *f = fopen(argv[1],"r");
    FILE *out1 = fopen("out1.dat","w+");
    FILE *out0 = fopen("out0.dat","w+");
    
    int i,c,n;
    float x,y;

    n = atoi(argv[2]);
    for(i=0;i<n;i++){
        fscanf(f,"%f,%f,%d\n", &x, &y,&c);
        if(c==0)
            fprintf(out0, "%f %f\n", x, y);
        else
            fprintf(out1, "%f %f\n", x, y);
    }
    
    fclose(f);
    fclose(out0);
    fclose(out1);
    
}