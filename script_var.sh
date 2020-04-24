#!/bin/bash

rm resultat_*

echo "Variante : "
for var in baseline tab_1d independant independant_split block_cache block_cache_mod block_cache_no_index
do
	echo $var
	make $var
	./exec 362 750 1500 >> "resultat_"$var".txt" 
done

make clean