

typedef double* Data;

typedef struct kdtree {
    struct kdtree  *right,*left;
    Data    data;
} KDTree;


KDTree *kdtree_fromList(Data *datos, int n_datos, int n_atr);

Data *kdtree_k_nearest(KDTree *tree, Data d, int k, int n_atr);

Data *kdtree_nearerthan(KDTree *tree, Data input, double d, int n_atr);

int kdtree_isLeaf(KDTree *tree);