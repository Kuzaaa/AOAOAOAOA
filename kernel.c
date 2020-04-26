#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define INDEX(row, col, n) (((row) * (n)) + (col))

#if BASELINE
//Code source
void baseline(unsigned n, float** a, float** b, float** c){

	unsigned i, j;

	for(i=0; i<n; i++){
		for(j=0; j<n-1; j++){
			a[j][i] = b[i][j] - 1;
		}

		for(j=0; j<n-1; j++){
			c[i][j] = a[j+1][i] * b[i][j+1];
		}
	}
}
#endif

#if TAB1D
//Tableau1D
void baseline(unsigned n, float* a, float* b, float* c){

	unsigned i, j;

	for(i=0; i<n; i++){
		for(j=0; j<n-1; j++){
			a[INDEX(j,i,n)] = b[INDEX(i,j,n)] - 1;
		}

		for(j=0; j<n-1; j++){
			c[INDEX(i,j,n)] = a[INDEX(j+1,i,n)] * b[INDEX(i,j+1,n)];
		}
	}
}
#endif

#if INDEPENDANT
//Independant loops
void baseline(unsigned n, float* a, float* b, float* c){

	unsigned i, j;

	for(i=0; i<n; i++){
		for(j=0; j<n-1; j++){
			a[INDEX(j,i,n)] = b[INDEX(i,j,n)] - 1;
		}

		for(j=0; j<n-2; j++){
			c[INDEX(i,j,n)] = (b[INDEX(i,j+1,n)] - 1) * b[INDEX(i,j+1,n)];
		}
		c[INDEX(i,n-2,n)] = a[INDEX(n-1,i,n)] * b[INDEX(i,n-1,n)];
	}
}
#endif

#if INDEPENDANT_SPLIT
//Independant loops + split
void baseline(unsigned n, float* a, float* b, float* c){

	unsigned i, j;

	for(i=0; i < n; i++){
		for(j=0; j<n-1; j++){
			a[INDEX(j,i,n)] = b[INDEX(i,j,n)] - 1;
		}
	}

	for(i=0;i<n;i++){
		for(j=i*n; j<INDEX(i,n-2,n); j++){
			c[j] = (b[j+1] - 1) * b[j+1];
		}
		c[j] = a[INDEX(n-1,i,n)] * b[j+1];
	}
}
#endif


#if BLOCK_CACHE
//Transposée par blocs
void baseline(unsigned n, float* a, float* b, float* c){
	unsigned k =0;
	unsigned l =0;
	unsigned m = 0;
	unsigned i = 0;
	unsigned j =0;

	int blockSize = 16;

	//// TRANSPOSEE ///////

    int resteLigne = (n-1)%blockSize;

    int resteCol = n%blockSize;


	//Calcul par blocs de taille blockSize

    for(i=0; i+blockSize < n ; i+=blockSize){//Position des blocs en colonne
        for(j=0 ; j+blockSize < n-1; j+=blockSize ){//Position des blocs en ligne
            for(k=i; k < i+blockSize ; k++){//Parcourt le bloc en colonne
                for(l=j; l < j+blockSize; l++){//Parcourt le bloc en ligne
                    a[INDEX(l,k,n)] = b[INDEX(k,l,n)] - 1;
                }
            }
        }
    }

	//Colonnes en dehors des blocs

    for(int o = n-resteCol; o < n; o++){
        for(int p = 0 ; p < n-1; p++){
            a[INDEX(p,o,n)] = b[INDEX(o,p,n)] - 1;
        }

    }

	//Lignes en dehors des blocs (sauf la dernière)

    for(int o = 0; o < n-resteCol; o++){
        for(int p = (n-1)-resteLigne ; p < n-1; p++){
            a[INDEX(p,o,n)] = b[INDEX(o,p,n)] - 1;
        }

    }


    /////// FIN TRANSPOSEE ////////

	for(i=0;i<n;i++){
		for(j=i*n; j<INDEX(i,n-2,n); j++){
			c[j] = (b[j+1] - 1) * b[j+1];
		}
		c[j] = a[INDEX(n-1,i,n)] * b[j+1];
	}


}
#endif


#if INDEPENDANT_PARALLEL
//Independant loops parallel
void baseline(unsigned n, float* a, float* b, float* c){

	unsigned i, j;
	omp_set_num_threads(omp_get_num_procs());

	#pragma omp parallel for private(j)
	for(i=0; i<n; i++){
		for(j=0; j<n-1; j++){
			a[INDEX(j,i,n)] = b[INDEX(i,j,n)] - 1;
		}

		for(j=0; j<n-2; j++){
			c[INDEX(i,j,n)] = (b[INDEX(i,j+1,n)] - 1) * b[INDEX(i,j+1,n)];
		}
		c[INDEX(i,n-2,n)] = a[INDEX(n-1,i,n)] * b[INDEX(i,n-1,n)];
	}
}
#endif

#if INDEPENDANT_SPLIT_PARALLEL
//Independant loops + split parallel
void baseline(unsigned n, float* a, float* b, float* c){

	unsigned i, j;
	omp_set_num_threads(omp_get_num_procs());

	#pragma omp parallel for private(j)
	for(i=0; i < n; i++){
		for(j=0; j<n-1; j++){
			a[INDEX(j,i,n)] = b[INDEX(i,j,n)] - 1;
		}
	}

	#pragma omp parallel for private(j)
	for(i=0;i<n;i++){
		for(j=i*n; j<INDEX(i,n-2,n); j++){
			c[j] = (b[j+1] - 1) * b[j+1];
		}
		c[j] = a[INDEX(n-1,i,n)] * b[j+1];
	}
}
#endif

#if BLOCKPARALLEL
//Transposée par blocs parallèles
void baseline(unsigned n, float* a, float* b, float* c){
	unsigned k =0;
	unsigned l =0;
	unsigned m = 0;
	unsigned i = 0;
	unsigned j =0;
	int p,o;

	int blockSize = 16;

	//// TRANSPOSEE ///////

    int resteLigne = (n-1)%blockSize;

    int resteCol = n%blockSize;

	omp_set_num_threads(omp_get_num_procs());

	//Calcul par blocs de taille blockSize

	#pragma omp parallel for private(j,k,l)
    for(i=0; i < n-blockSize ; i+=blockSize){//Position des blocs en colonne
        for(j=0 ; j+blockSize < n-1; j+=blockSize ){//Position des blocs en ligne
            for(k=i; k < i+blockSize ; k++){//Parcours le bloc en colonne
                for(l=j; l < j+blockSize; l++){//Parcours le bloc en ligne
                    a[INDEX(l,k,n)] = b[INDEX(k,l,n)] - 1;
                }
            }
        }
    }

	//Colonnes en dehors des blocs

	#pragma omp parallel for private(p)
    for(o = n-resteCol; o < n; o++){
        for(p = 0 ; p < n-1; p++){
            a[INDEX(p,o,n)] = b[INDEX(o,p,n)] - 1;
        }

    }

	//Lignes en dehors des blocs (sauf la dernière)

	#pragma omp parallel for private(p)
    for(o = 0; o < n-resteCol; o++){
        for(p = (n-1)-resteLigne ; p < n-1; p++){
            a[INDEX(p,o,n)] = b[INDEX(o,p,n)] - 1;
        }

    }


    //////// FIN TRANSPOSEE ////////
    
	#pragma omp parallel for private(j)
	for(i=0;i<n;i++){
		for(j=i*n; j<INDEX(i,n-2,n); j++){
			c[j] = (b[j+1] - 1) * b[j+1];
		}
		c[j] = a[INDEX(n-1,i,n)] * b[j+1];
	}


}
#endif
