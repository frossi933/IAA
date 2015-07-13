/*
 K-nearest neighbors
 """""""""""""""""""
 
 by Federico Rossi
*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#include "kdtree.h"

#define LOW 1.e-14                 /*Minimo valor posible para una probabilidad*/


int N_IN;           /*Total numbre of inputs*/
int N_Class;        /*Total number of classes (outputs)*/

int PTOT;           /* cantidad TOTAL de patrones en el archivo .data */
int PR;             /* cantidad de patrones de ENTRENAMIENTO */
int PTEST;          /* cantidad de patrones de TEST (archivo .test) */
                    /* cantidad de patrones de VALIDACION: PTOT - PR*/

int SEED;           /* semilla para la funcion rand(). Los posibles valores son:*/
                    /* SEED: -1: No mezclar los patrones: usar los primeros PR para entrenar
                                 y el resto para validar.Toma la semilla del rand con el reloj.
                              0: Seleccionar semilla con el reloj, y mezclar los patrones.
                             >0: Usa el numero leido como semilla, y mezcla los patrones. */

double D;              /* Distancia a tener en cuenta en la votacion */
                    
int N_TOTAL;                      /*Numero de patrones a usar durante el entrenamiento*/

/*matrices globales  DECLARAR ACA LAS MATRICES NECESARIAS */

Data    *train_data;                     /* train data */
Data    *test_data;                     /* test  data */
int     *pred;                     /* clases predichas */

KDTree  *tree_data;                 /* arbol con los datos de entrenamiento */

int *seq;      	       		  /* sequencia de presentacion de los patrones*/

/*variables globales auxiliares*/
char filepat[100];


/* -------------------------------------------------------------------------- */
/*define_matrix: reserva espacio en memoria para todas las matrices declaradas.
  Todas las dimensiones son leidas del archivo .info en la funcion arquitec()  */
/* -------------------------------------------------------------------------- */
int define_matrix(){

  int max, i;
  if(PTOT>PTEST) max=PTOT;
  else max=PTEST;

  seq =(int *)calloc(max,sizeof(int));
  pred=(int *)calloc(max,sizeof(int));
  if(seq==NULL||pred==NULL) return 1;
  
  train_data=(Data *)malloc(PTOT*sizeof(Data));
  if(PTEST) test_data=(Data *)malloc(PTEST*sizeof(Data));
  if(train_data==NULL ||(PTEST&&test_data==NULL)) return 1;

  for(i=0;i<PTOT;i++){
    train_data[i]=(Data)calloc(N_IN+1,sizeof(double));
	if(train_data[i]==NULL) return 1;
  }
  for(i=0;i<PTEST;i++){
    test_data[i]=(Data)calloc(N_IN+1,sizeof(double));
	if(test_data[i]==NULL) return 1;
  }

  return 0;
}
/* ---------------------------------------------------------------------------------- */
/*arquitec: Lee el archivo .info e inicializa el algoritmo en funcion de los valores leidos
  filename es el nombre del archivo .info (sin la extension) */
/* ---------------------------------------------------------------------------------- */
int arquitec(char *filename){
  FILE *b;
  time_t t;

  /*Paso 1:leer el archivo con la configuracion*/
  sprintf(filepat,"%s.info",filename);
  b=fopen(filepat,"r");
  if(b==NULL){
    printf("Error al abrir el archivo de parametros\n");
    return 1;
  }

  /* Dimensiones */
  fscanf(b,"%d",&N_IN);
  fscanf(b,"%d",&N_Class);

  /* Archivo de patrones: datos para train y para validacion */
  fscanf(b,"%d",&PTOT);
  fscanf(b,"%d",&PR);
  fscanf(b,"%d",&PTEST);

  /* Semilla para la funcion rand()*/
  fscanf(b,"%d",&SEED);

  /* Numero D de la distancia a considerar para la votacion */
  fscanf(b,"%lf",&D);
  
  fclose(b);

  /*Paso 2: Definir matrices para datos y parametros (e inicializarlos*/
  if(define_matrix()){
    printf("Error en la definicion de matrices\n");
    return 1;
  }

  /* Chequear semilla para la funcion rand() */
  if(SEED==0) SEED=time(&t);

  /*Imprimir control por pantalla*/
  printf("\nInstance Based Learning - K Nearest neighbors\nCantidad de entradas:%d",N_IN);
  printf("\nCantidad de clases:%d",N_Class);
  printf("\nArchivo de patrones: %s",filename);
  printf("\nCantidad total de patrones: %d",PTOT);
  printf("\nCantidad de patrones de entrenamiento: %d",PR);
  printf("\nCantidad de patrones de validacion: %d",PTOT-PR);
  printf("\nCantidad de patrones de test: %d",PTEST);
  printf("\nSemilla para la funcion rand(): %d",SEED);
  printf("\nDistancia de vecinos: %f", D);

  return 0;
}
/* -------------------------------------------------------------------------------------- */
/*read_data: lee los datos de los archivos de entrenamiento(.data) y test(.test)
  filename es el nombre de los archivos (sin extension)
  La cantidad de datos y la estructura de los archivos fue leida en la funcion arquitec()
  Los registros en el archivo pueden estar separados por blancos ( o tab ) o por comas    */
/* -------------------------------------------------------------------------------------- */
int read_data(char *filename){

  FILE *fpat;
  double valor;
  int separador;
  int i,k;

  sprintf(filepat,"%s.data",filename);
  fpat=fopen(filepat,"r");
  if(fpat==NULL){
    printf("Error al abrir el archivo de datos\n");
    return 1;
  }

  for(k=0;k<PTOT;k++){
    for(i=0;i<N_IN+1;i++){
      fscanf(fpat,"%lf",&valor);
      train_data[k][i]=valor;
      separador=getc(fpat);
      if(separador!=',') ungetc(separador,fpat);
    }
  }
  fclose(fpat);

  if(!PTEST) return 0;

  sprintf(filepat,"%s.test",filename);
  fpat=fopen(filepat,"r");
  if(fpat==NULL){
    printf("Error al abrir el archivo de test\n");
    return 1;
  }

  for(k=0;k<PTEST;k++){
    for(i=0;i<N_IN+1;i++){
      fscanf(fpat,"%lf",&valor);
      test_data[k][i]=valor;
      separador=getc(fpat);
      if(separador!=',') ungetc(separador,fpat);
    }
  }
  fclose(fpat);

  return 0;

}
/* ------------------------------------------------------------ */
/* shuffle: mezcla el vector seq al azar.
   El vector seq es un indice para acceder a los patrones.
   Los patrones mezclados van desde seq[0] hasta seq[hasta-1]
   Esto permite separar la parte de validacion de la de train   */
/* ------------------------------------------------------------ */
void shuffle(int hasta){
   double x;
   int tmp;
   int top,select;

   top=hasta-1;
   while (top > 0) {
	x = (double)rand();
	x /= RAND_MAX;
	x *= (top+1);
	select = (int)x;
	tmp = seq[top];
	seq[top] = seq[select];
	seq[select] = tmp;
	top --;
   }
}

/* ------------------------------------------------------------------------------ */
/*output: calcula la probabilidad de cada clase dado un vector de entrada *input
  usa el log(p(x)) (sumado)
  devuelve la de mayor probabilidad                                               */
/* ------------------------------------------------------------------------------ */
int output(Data input){
   	
  int i, j, c, best=0;
  Data *nearer = kdtree_nearerthan(tree_data, input, D, N_IN);

  if(nearer[0]==NULL){
    /* no hay puntos cerca */
    c=rand()%N_Class;             // elijo random
    free(nearer);
    return c;
  }
  
#ifdef DEBUG
  printf("\nnearest de %f %f:\t",input[0], input[1]);
  i=0;
  while(nearer[i]!=NULL){
    printf("%f %f ;",nearer[i][0],nearer[i][1]);
    i++;
  }
#endif

  int *votes = calloc(N_Class, sizeof(int));
  i=0;
  while(nearer[i]){
    c=(int)nearer[i][N_IN];
    votes[c]++;
    i++;
  }
  
  /* elijo el mayor, y en caso de empate elijo una clase random */
  for(i=0;i<N_Class;i++){
    if(votes[i]>best){
        c=i;
        best=votes[i];
    } else if(votes[i]==best && rand()%2)
        c=i;
  }

  free(nearer);
  free(votes);
  return c;
}
/* ------------------------------------------------------------------------------ */
/*propagar: calcula las clases predichas para un conjunto de datos
  la matriz S tiene que tener el formato adecuado ( definido en arquitec() )
  pat_ini y pat_fin son los extremos a tomar en la matriz
  usar_seq define si se accede a los datos directamente o a travez del indice seq
  los resultados (las propagaciones) se guardan en la matriz seq                  */
/* ------------------------------------------------------------------------------ */
double propagar(Data *S, int pat_ini, int pat_fin, int usar_seq){

  double err=0.0;
  int nu;
  int patron;
  
  for (patron=pat_ini; patron<pat_fin; patron++) {

   /*nu tiene el numero del patron que se va a presentar*/
    if(usar_seq) nu = seq[patron];
    else         nu = patron;

    /* clase para el patron nu */
    pred[nu]=output(S[nu]);

    /*actualizar error*/
    if(S[nu][N_IN]!=(double)pred[nu]) err+=1.;
  }
    
  err /= ( (double)(pat_fin-pat_ini));
  return err;
}

int predic(char *filename){
    
  FILE *fpredic;
  int k,i;
  
  /* archivo de predicciones */
  sprintf(filepat,"%s.predic",filename);
  fpredic=fopen(filepat,"w");
  if(fpredic==NULL){
      printf("Error al abrir archivo para guardar predicciones\n");
      return 1;
  }
  
  for(k=0; k<PTEST ; k++){
    for(i=0;i<N_IN;i++) 
      fprintf(fpredic,"%f\t",test_data[k][i]);
    fprintf(fpredic,"%d\n",pred[k]);
  }
  fclose(fpredic);

  return 0;
}

/* ----------------------------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------------------------- */
int main(int argc, char **argv){
    
  float train_error, test_error, valid_error;

  if(argc!=2){
    printf("Modo de uso: knn <filename>\ndonde:\tfilename es el nombre del archivo (sin extension)\n");
    return 0;
  }

  /* defino la estructura*/
  if(arquitec(argv[1])){
    printf("Error en la definicion de parametros\n");
    return 1;
  }

  /* leo los datos */
  if(read_data(argv[1])){
    printf("Error en la lectura de datos\n");
    return 1;
  }

  if(SEED > 0)
      srand(SEED);                             // random para elegir en caso de empate y etc
  else
      srand(time(NULL));  
  
  if(PR==PTOT){
      /* creo el arbol k-d con los datos */
      tree_data = kdtree_fromList(train_data, PTOT, N_IN);
      /* calculo errores */
      train_error=propagar(train_data,0,PTOT,0);
      valid_error=0.0;
  } else {
      if(SEED > -1){
        Data *rand_train_data = (Data *)malloc(sizeof(Data) * PR);
        int i;

        for(i=0;i<PTOT;i++)
            seq[i]=i;  /* inicializacion del indice de acceso a los datos */
        shuffle(PTOT);
        
        for(i=0;i<PR;i++)
            rand_train_data[i]=train_data[seq[i]];
      
        tree_data = kdtree_fromList(rand_train_data, PR, N_IN);
        free(rand_train_data);
        /* calculo errores */
        train_error=propagar(train_data,0,PR,1);
        valid_error=propagar(train_data,PR,PTOT,1);
          
      } else {
        tree_data = kdtree_fromList(train_data, PR, N_IN);
        /* calculo errores */
        train_error=propagar(train_data, 0, PR, 0);
        valid_error=propagar(train_data, PR, PTOT, 0);
      }
  }
  
  if(PTEST>0)
      test_error=propagar(test_data,0,PTEST,0);
  else
      test_error=0.0;
  
  if(predic(argv[1])){
    printf("Error en la prediccion\n");
    return 1;
  }

  printf("\nFin del algoritmo.\n\n");
  printf("Errores:\nEntrenamiento:%f%%\n",train_error*100.);
  printf("Validacion:%f%%\nTest:%f%%\n",valid_error*100.,test_error*100.);
  
  return 0;
}
/* ----------------------------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------------------------- */