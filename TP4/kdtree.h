

typedef double* Data;

typedef struct kdtree {
    struct kdtree  *right,*left;
    Data    data;
} KDTree;

int atr_cmp;                                                            // numero de atributo por el cual ordeno los datos...

KDTree *kdtree_fromList(Data *datos, int n_datos, int k);

Data *kdtree_k_nearest(KDTree *tree, Data d, int k);

int kdtree_isLeaf(KDTree *tree);