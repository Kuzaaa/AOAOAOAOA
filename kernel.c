#include <stdio.h>
#include <stdlib.h>

#define INDEX(row, col, n) (((row) * (n)) + (col))




void printMatt(char* name, float* mat, unsigned n){

	unsigned i,j;

	printf("%s :\n",name);

	for(i=0; i<n; i++){
		printf("|");
	    for(j=0; j<n; j++){
			printf(" %f ",mat[INDEX(i,j,n)]);
	    }
	    printf("|\n");
	}
}

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
//Independant loops
void baseline(unsigned n, float* a, float* b, float* c){

	unsigned i, j;
	//printf("debut fonction \n");
	for(i=0; i < n; i++){
		for(j=0; j<n-1; j++){
			//printf("i: %d j: %d \n ",i,j);
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
//Independant loops
void baseline(unsigned n, float* a, float* b, float* c){
	unsigned k =0;
	unsigned l =0;
	unsigned m = 0;
	unsigned i = 0;
	unsigned j =0;

	int blockSize = 4; 

	//// TRANSPOSER ///////
 
    int resteLigne = (n-1)%blockSize;

    int resteCol = n%blockSize;


	//Calcul par block de taille blockSize

    for(i=0; i+blockSize < n ; i+=blockSize){//Position des blocs en colonne
        for(j=0 ; j+blockSize < n-1; j+=blockSize ){//Position des blocs en ligne
		//printf("block de taille %d en %d, %d\n",blockSize,j,i);
            for(k=i; k < i+blockSize ; k++){//Parcours le bloc en colonne
                for(l=j; l < j+blockSize; l++){//Parcours le bloc en ligne
                    //printf("case %d,%d\n",k,l);
                	//printf("i: %d j: %d : k: %d l: %d \n",i,j,k,l );
                    a[INDEX(l,k,n)] = b[INDEX(k,l,n)] - 1;
                }
            }

        }
    }

	//Colonne en dehors des blocs

    //printf("Premiere boucle\n");

    //printf("Ligne %d à %d pour les colonnes %d à %d\n",0,n-1,n-resteCol,n);
   	
    for(int o = n-resteCol; o < n; o++){
        for(int p = 0 ; p < n-1; p++){
            a[INDEX(p,o,n)] = b[INDEX(o,p,n)] - 1;
        }
    
    }

	//Ligne en dehors des blocs (sauf la dernière)

	//printf("Deuxieme boucle\n");
   // printMat1D("A",a,n);
    //printf("Ligne %d à %d pour les colonnes %d à %d\n",(n-1)-resteLigne,n-1,0,n-resteCol);
    for(int o = 0; o < n-resteCol; o++){
        for(int p = (n-1)-resteLigne ; p < n-1; p++){
            a[INDEX(p,o,n)] = b[INDEX(o,p,n)] - 1;
        }
    
    }

	
    ///////////// FIN TRANSPOSE

	for(i=0;i<n;i++){
		for(j=i*n; j<INDEX(i,n-2,n); j++){
			c[j] = (b[j+1] - 1) * b[j+1];
		}
		c[j] = a[INDEX(n-1,i,n)] * b[j+1];
	}


}
#endif


#if BLOCK_CACHE_MOD
//Independant loops
void baseline(unsigned n, float* a, float* b, float* c){
	unsigned k =0;
	unsigned l =0;
	unsigned m = 0;
	unsigned i = 0;
	unsigned j =0;

	int blockSize = 4; 

	//// TRANSPOSER ///////
 
    //int resteLigne = (n-1)%blockSize;
    //int resteCol = n%blockSize;
    int reste = n%blockSize;

    /*
    	store la derniere ligne
    */

   // printf("debut fonction \n");
    // printMatt("A",a,n);
    float *tamp = malloc(sizeof(float)*n ) ;

   	for(int x =0; x < n; ++x){

   		for(int y=n-1; y < n; ++y){
			tamp[x]= a[INDEX(y,x,n)];
			//printf("tamp[x]= %f \n",tamp[x]);
   		}

   	}

	//Calcul par block de taille blockSize
   	
   for(i=0; i+blockSize <= n ; i+=blockSize){//Position des blocs en colonne
   //	printf("block de taille %d en %d, %d\n",blockSize,j,i);
        for(j=0 ; j+blockSize <= n; j+=blockSize ){//Position des blocs en ligne

		
            for(k=i; k < i+blockSize ; k++){//Parcours le bloc en colonne
                for(l=j; l < j+blockSize; l++){//Parcours le bloc en ligne
                    //printf("case %d,%d\n",k,l);
                	//printf("i: %d j: %d : k: %d l: %d \n",i,j,k,l );
                    a[INDEX(l,k,n)] = b[INDEX(k,l,n)] - 1;
                }
            }

        }
    }

	//Colonne en dehors des blocs

    //printf("Premiere boucle\n");

    //printf("Ligne %d à %d pour les colonnes %d à %d\n",0,n-1,n-resteCol,n);
   	
    for(int o = n-reste; o < n; o++){
        for(int p = 0 ; p < n; p++){
            a[INDEX(p,o,n)] = b[INDEX(o,p,n)] - 1;
        }
    
    }

	//Ligne en dehors des blocs (sauf la dernière)

	//printf("Deuxieme boucle\n");
   // printMat1D("A",a,n);
    //printf("Ligne %d à %d pour les colonnes %d à %d\n",(n-1)-resteLigne,n-1,0,n-resteCol);
    for(int o = 0; o < n-reste; o++){
        for(int p = n-reste ; p < n-1; p++){
            a[INDEX(p,o,n)] = b[INDEX(o,p,n)] - 1;
        }
    
    } 
    //printMatt("A",a,n);
    for(int x =0; x < n; ++x){

   		for(int y=n-1; y < n; ++y){
			a[INDEX(y,x,n)]=tamp[x] ;
   		}

   		//printf("tamp[x]= %f \n",tamp[x]);
   	}

	//printMatt("A",a,n);
    ///////////// FIN TRANSPOSE

	for(i=0;i<n;i++){
		for(j=i*n; j<INDEX(i,n-2,n); j++){
			c[j] = (b[j+1] - 1) * b[j+1];
		}
		c[j] = a[INDEX(n-1,i,n)] * b[j+1];
	} 
	free(tamp);

}
#endif


