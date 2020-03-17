#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>

#define NB_METAS 31

extern uint64_t rdtsc();
extern void baseline(unsigned n, float** a, float** b, float** c);

void printMat(char* name, float** mat, unsigned n);

int main(int argc, char *argv[]){

	if(argc != 4){
		printf("Usage : %s <size> <nb warmup repets> <nb measure repets>\n",argv[0]);
		return 0;
  	}

	unsigned int i,j,n,m;
	int repm,repw;
	uint64_t t1,t2;
	clock_t start,end;

	n = atoi(argv[1]);
	repw = atoi(argv[2]);
	repm = atoi(argv[3]);

	srand(time(NULL));

	for(m=0;m<NB_METAS;m++) {

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

		if(m == 0){
			for(i=0;i<repw;i++){
				baseline(n,a,b,c);
			}
		}
		else {
			baseline(n,a,b,c);
		}

		t1 = rdtsc();
		start = clock();
		for(i=0;i<repm;i++){
			baseline(n,a,b,c);
		}
		end = clock();
		t2 = rdtsc();

		//printf("%.2f cycles/operation\n",(float)(t2 - t1) / ((float) n * n * repm));
		printf("%.6f\n",(end - start) / ((float) CLOCKS_PER_SEC * repm));

		/*printMat("A",a,n);
		printMat("B",b,n);
		printMat("C",c,n);*/

		for(i=0; i<n; i++){
		    free(a[i]);
		    free(b[i]);
		    free(c[i]);
		}

		free(a);
		free(b);
		free(c);
	}

	return 0;
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