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
			a[INDEX(j,i,n-1)] = b[INDEX(i,j,n-1)] - 1;
		}

		for(j=0; j<n-1; j++){
			c[INDEX(i,j,n-1)] = a[INDEX(j+1,i,n-1)] * b[INDEX(i,j+1,n-1)];
		}
	}
}
#endif 
