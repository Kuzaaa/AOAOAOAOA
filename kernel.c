//il faudra rajouter les opti avec le même nom de fonction

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
