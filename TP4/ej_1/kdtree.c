#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>

#include "kdtree.h"

typedef struct {
    Data    data;
    double   dist;
} DataDist;

static int cmpfunc (const void * a, const void * b){
   double da=(*((Data *)a))[atr_cmp];
   double db=(*((Data *)b))[atr_cmp];
   return ((da > db) - (da < db));
}

static int cmpdatadist (const void * a, const void * b){
   double da=(*((DataDist **)a))->dist;
   double db=(*((DataDist **)b))->dist;
   return ((da > db) - (da < db));
}

double distance(Data a, Data b, int n){
    int i;
    double sum=0.0;
    for(i=0;i<n;i++)
        sum+=pow(a[i]-b[i],2);
    return sqrt(sum);    
}


KDTree *kdtree_fromList_rec(Data *datos, int n_datos, int n_atr, int deep){

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
    
    atr_cmp = deep % n_atr;
    qsort(datos, n_datos, sizeof(Data), cmpfunc);
    med = n_datos / 2;
    root->data = datos[med];
    root->right = kdtree_fromList_rec(datos+med+1, n_datos-med-1, n_atr, deep+1);
    root->left = kdtree_fromList_rec(datos, med, n_atr, deep+1);
    return root;
}

KDTree *kdtree_fromList(Data *datos, int n_datos, int n_atr){
    
    return kdtree_fromList_rec(datos, n_datos, n_atr, 0);
}


/* res esta ordenada del mas cerca al mas lejos */
void k_nearest_rec(KDTree *tree, Data d, int k, DataDist **res, int n_atr, int deep){
    
    if(tree == NULL)
        return;
    else if(kdtree_isLeaf(tree)){
        double dst = distance(tree->data, d, n_atr);
        if(res[k-1]->dist > dst){
            res[k-1]->data=tree->data;
            res[k-1]->dist=dst;
            qsort(res, k, sizeof(DataDist *), cmpdatadist);
        }
    } else {
        int atr = deep % n_atr;
        double worst, current, diff;
        if(d[atr] < tree->data[atr]){
            k_nearest_rec(tree->left, d, k, res, n_atr, deep+1);

            worst = res[k-1]->dist;
            current = distance(tree->data,d,n_atr);
            if(current < worst){
                res[k-1]->data=tree->data;
                res[k-1]->dist=current;
                qsort(res, k, sizeof(DataDist *), cmpdatadist);
            }
            
            diff = fabs(tree->data[atr] - d[atr]);
            if(diff < res[k-1]->dist)
                // debo revisar el otro lado
                k_nearest_rec(tree->right, d, k, res, n_atr, deep+1);
            
        } else if(d[atr] > tree->data[atr]) {
            k_nearest_rec(tree->right, d, k, res, n_atr, deep+1);
            
            worst = res[k-1]->dist;
            current = distance(tree->data,d,n_atr);
            if(current < worst){
                res[k-1]->data=tree->data;
                res[k-1]->dist=current;
                qsort(res, k, sizeof(DataDist *), cmpdatadist);
            }
            
            diff = fabs(tree->data[atr] - d[atr]);
            if(diff < res[k-1]->dist)
                // debo revisar el otro lado
                k_nearest_rec(tree->left, d, k, res, n_atr, deep+1);
        } else {/* tiene el mismo atributo del valor del nodo */
            worst = res[k-1]->dist;
            current = distance(tree->data,d,n_atr);
            if(current < worst){
                res[k-1]->data=tree->data;
                res[k-1]->dist=current;
                qsort(res, k, sizeof(DataDist*), cmpdatadist);
            }
            
            k_nearest_rec(tree->right, d, k, res, n_atr, deep+1);
            k_nearest_rec(tree->left, d, k, res, n_atr, deep+1);
        }
    }
}

Data *kdtree_k_nearest(KDTree *tree, Data d, int k, int n_atr){

    int i;
    DataDist **res = (DataDist **)malloc(sizeof(DataDist*) * k);
    Data *ret = (Data *)malloc(sizeof(Data)*k);
    for(i=0;i<k;i++){
        res[i] = (DataDist *)malloc(sizeof(DataDist));
        res[i]->data=NULL;
        res[i]->dist=1000.0;
    }
    k_nearest_rec(tree, d, k, res, n_atr, 0);
    for(i=0;i<k;i++)
        ret[i]=res[i]->data;

    free(res);
    return ret;
}

int kdtree_isLeaf(KDTree *tree){
    return ((tree->right == NULL) && (tree->left == NULL));
}