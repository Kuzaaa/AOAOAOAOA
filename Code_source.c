#include <stdio.h>

void baseline(unsigned n, float a[n][n], float b[n][n], float c[n][n]);

int main(){

  baseline();
}

void baseline(unsigned n, float a[n][n], float b[n][n], float c[n][n]){
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
