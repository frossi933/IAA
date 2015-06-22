#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>

typedef float* Data;

typedef struct {
    Data    data;
    float   dist;
} DataDist;


typedef struct kdtree {
    struct kdtree  *right,*left;
    Data    data;
} KDTree;

int atr_cmp;                                                            // numero de atributo por el cual ordeno los datos...

static int cmpfunc (const void * a, const void * b){
   return ( ((Data *)a)[atr_cmp] - ((Data *)b)[atr_cmp] );
}

static int cmpdatadist (const void * a, const void * b){
   return ( ((DataDist *)a)->dist - ((DataDist *)b)->dist );
}

float distance(Data a, Data b, int k){
    int i;
    float sum=0.0;
    for(i=0;i<k;i++)
        sum+=pow(a[i]-b[i],2);
    return sqrt(sum);    
}


KDTree *kdtree_fromList(Data *datos, int n_datos, int k, int deep){

    if(n_datos == 0)
        return NULL;

    KDTree *root=(KDTree *)malloc(sizeof(KDTree));
    if(n_datos==1){
        root->data = *datos;
        root->right = NULL;
        root->left = NULL;
        return root;        
    }
      
    int med;
    
    atr_cmp = deep % k;
    qsort(datos, n_datos, sizeof(Data), cmpfunc);
    med = n_datos / 2;
    root->data = datos[med];
    root->right = kdtree_fromList(datos+med+1, n_datos-med-1, k, deep+1);
    root->left = kdtree_fromList(datos, med, k, deep+1);
    return root;
}


/* res esta ordenada del mas cerca al mas lejos */
void k_nearest_rec(KDTree *tree, Data d, int k, DataDist **res, int deep){
    
    if(tree == NULL)
        return;
    else if(kdtree_isLeaf(tree)){
        res[0]->data=tree->data;
        res[0]->dist=distance(tree->data, d,k);
        return;
    } else {
        int atr = deep % k;
        float worst, current, diff;
        if(d[atr] < tree->data[atr]){
            k_nearest_rec(tree->left, d, k, res, deep+1);

            worst = res[k-1]->dist;
            current = distance(tree->data,d,k);
            if(current < worst){
                res[k-1]->data=tree->data;
                res[k-1]->dist=current;
                qsort(res, k, sizeof(DataDist), cmpdatadist);
            }
            
            diff = abs(tree->data[atr] - d[atr]);
            if(diff < worst)
                // debo revisar el otro lado
                k_nearest_rec(tree->right, d, k, res, deep+1);
            
        } else {
            k_nearest_rec(tree->right, d, k, res, deep+1);
            worst = res[k-1]->dist;
            current = distance(tree->data,d,k);
            if(current < worst){
                res[k-1]->data=tree->data;
                res[k-1]->dist=current;
                qsort(res, k, sizeof(DataDist), cmpdatadist);
            }
            
            diff = abs(tree->data[atr] - d[atr]);
            if(diff < worst)
                // debo revisar el otro lado
                k_nearest_rec(tree->left, d, k, res, deep+1);
        }
    }
}

DataDist **kdtree_k_nearest(KDTree *tree, Data d, int k){

    int i;
    DataDist **res = (DataDist **)malloc(sizeof(DataDist*) * k);
    for(i=0;i<k;i++){
        res[i]->data=NULL;
        res[i]->dist=FLT_MAX;
    }
    k_nearest_rec(tree, d, k, res, 0);
    return res;
}

int kdtree_isLeaf(KDTree *tree){
    return ((tree->right == NULL) && (tree->left == NULL));
}

int main(){
    
    return 1;
    
}