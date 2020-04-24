#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <emmintrin.h>


//Méta-répétions
#define NB_METAS 31

//
#define INDEX(row, col, n) (((row) * (n)) + (col))

//Permet de récuperer le nombre de cycles
extern uint64_t rdtsc();

//Code source

//
#if BASELINE
extern void baseline(unsigned n, float** a, float** b, float** c);
#endif

//
#if BASELINE == 0
extern void baseline(unsigned n, float* a, float* b, float* c);
#endif

//Fonction debug/test qui affiche une matrice
void printMat(char* name, float** mat, unsigned n);
void printMat1D(char* name, float* mat, unsigned n);

int main(int argc, char *argv[]){

	//Verification du nombre d'arguments
	if(argc != 4){
		printf("Usage : %s <size> <nb warmup repets> <nb measure repets>\n",argv[0]);
		return 0;
  	}

	unsigned int i,j,n,m;
	int repm,repw;
	uint64_t t1,t2;

	n = atoi(argv[1]);
	repw = atoi(argv[2]);
	repm = atoi(argv[3]);
	srand(0);

	//Pour chaque méta-répétitions
	for(m=0;m<NB_METAS;m++) {

		/*
		 *Initialisation des tableaux
		 */

		//
		#if BASELINE
		float** a = NULL;
		float** b = NULL;
		float** c = NULL;

		a = malloc(n*sizeof(float*));
		b = malloc(n*sizeof(float*));
		c = malloc(n*sizeof(float*));

		for(i=0; i<n; i++){
			a[i] = malloc(n*sizeof(float));
		    b[i] = malloc(n*sizeof(float));
		    c[i] = malloc(n*sizeof(float));

		    for(j=0; j<n; j++){
		    	a[i][j] = ((float)rand())/RAND_MAX;
		    	b[i][j] = ((float)rand())/RAND_MAX;
		    	c[i][j] = ((float)rand())/RAND_MAX;
		    }
		}
		#endif

		//
		#ifndef BASELINE
		float* a = NULL;
		float* b = NULL;
		float* c = NULL;

		//
		a = _mm_malloc(n*n*sizeof(float),32);
		b = _mm_malloc(n*n*sizeof(float),32);
		c = _mm_malloc(n*n*sizeof(float),32);

		//
		for(i=0; i<n*n; i++){
		   	a[i] = ((float)rand())/RAND_MAX;
		   	b[i] = ((float)rand())/RAND_MAX;
		   	c[i] = ((float)rand())/RAND_MAX;
		}
		#endif

		//Warm-up * nombre de répétitions du warm-up
		for(i=0;i<repw;i++){
			baseline(n,a,b,c);
		}


		//Exécution du code souce * nombre de répétitions des mesures
		t1 = rdtsc();
		for(i=0;i<repm;i++){
			baseline(n,a,b,c);
		}
		t2 = rdtsc();

		//Affichage du nombre de cycles par instructions
		printf("%.2f\n",(float)(t2 - t1) / ((float) n * n * repm));

		/*
		 *Debug/test
		 *Affiche les matrices du code source
		 */
		/*
		#if BASELINE
		printMat("A",a,n);
		printMat("B",b,n);
		printMat("C",c,n);
		#endif

		#ifndef BASELINE
		printMat1D("A",a,n);
		printMat1D("B",b,n);
		printMat1D("C",c,n);
		#endif
		*/

		/*
		 *Libération mémoire
		 */

		//
		#if BASELINE
		for(i=0; i<n; i++){
		    free(a[i]);
		    free(b[i]);
		    free(c[i]);
		}
		free(a);
		free(b);
		free(c);
		#endif

		//
		#ifndef BASELINE
		_mm_free(a);
		_mm_free(b);
		_mm_free(c);
		#endif

	}

	return 0;
}

//Fonction debug/test qui affiche une matrice
void printMat(char* name, float** mat, unsigned n){

	unsigned i,j;

	printf("%s :\n",name);

	for(i=0; i<n; i++){
		printf("|");
	    for(j=0; j<n; j++){
			printf(" %f ",mat[i][j]);
	    }
	    printf("|\n");
	}
}

//Fonction debug/test qui affiche une matrice
void printMat1D(char* name, float* mat, unsigned n){

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
