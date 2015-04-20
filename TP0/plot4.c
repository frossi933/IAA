#include <stdlib.h>
#include <stdio.h>

// programa para traducir el archivo .data generado en dos archivos para usar en el gnuplot (un archivo para cada clase)
// este caso es para valores con 4 entradas

// file: archivo .data
// n: cant de valores en total

// ./plot4 file n
int main(int argc, char **argv){

    FILE *f = fopen(argv[1],"r");
    FILE *out1 = fopen("out1.dat","w+");
    FILE *out0 = fopen("out0.dat","w+");
    
    int i,c,n;
    float x,y,w,z;

    n = atoi(argv[2]);
    for(i=0;i<n;i++){
        fscanf(f,"%f,%f,%f,%f,%d\n", &x, &y, &w,&z,&c);
        if(c==0)
            fprintf(out0, "%f %f %f %f\n", x, y, w, z);
        else
            fprintf(out1, "%f %f %f %f\n", x, y, w, z);
    }
    
    fclose(f);
    fclose(out0);
    fclose(out1);
    
}