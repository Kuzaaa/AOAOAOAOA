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
//Independant loops
void baseline(unsigned n, float* a, float* b, float* c){

	unsigned i, j;

	for(i=0; i<n; i++){
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
//Independant loops
void baseline(unsigned n, float* a, float* b, float* c){

	unsigned i,j,k,l;

	unsigned blockSize = 32; 

	for(i=0; i < n ; i+=blockSize){
		for(j=0 ;j < n-1; j+=blockSize ){

			for(k=i; k< i+blockSize ; k++){
				for(l=j; j < j+blockSize; l++){
					a[INDEX(l,k,n)] = b[INDEX(k,l,n)] - 1;
				}
			}

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