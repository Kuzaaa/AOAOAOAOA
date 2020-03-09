#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX 32


void baseline(unsigned n, float** a, float** b, float** c);

int main(int argc, char *argv[]){

  if(argc<2||argc>2){
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
      a[i][j] = ((float)rand())/MAX;
      b[i][j] = ((float)rand())/MAX;
      c[i][j] = ((float)rand())/MAX;
    }
  }

  baseline(n,a,b,c);

 //Il faudrait free mais j'ai la flemme
}

void baseline(unsigned n, float** a, float** b, float** c){
  unsigned i, j;

  for(i=0; i<n; i++){
    for(j=0; j<n; j++){
      a[j][i] = b[i][j] - 1;
    }
    for(j=0; j<n-1; j++){
      c[i][j] = a[j+1][i] * b[i][j+1];
    }
  }
}
