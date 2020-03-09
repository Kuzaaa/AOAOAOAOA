#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX 32

void baseline(unsigned n, float** a, float** b, float** c);
void printMat(char* name, float** mat, unsigned n);

int main(int argc, char *argv[]){

	if(argc != 2){
		printf("Usage : %s size\n",argv[0]);
    	return 0;
  	}

	float** a = NULL;
	float** b = NULL;
	float** c = NULL;

	unsigned i,j,n;
	n = (int)atoi(argv[1]);
	srand(time(NULL));

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

	printMat("A",a,n);
	printMat("B",b,n);
	printMat("C",c,n);

	baseline(n,a,b,c);

	printMat("A",a,n);
	printMat("B",b,n);
	printMat("C",c,n);

	for(i=0; i<n; i++){
	    free(a[i]);
	    free(b[i]);
	    free(c[i]);
	}

	free(a);
	free(b);
	free(c);
}

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