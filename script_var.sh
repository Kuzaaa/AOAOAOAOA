#!/bin/bash

rm resultat_*

echo "Variante : "
for var in baseline tab_1d independant independant_split block_cache block_cache_mod independant_parallel independant_split_parallel block_cache_parallel
do
	echo $var
	make $var
	./exec 48 380000 380000 >> "resultat_"$var".txt"
done

make clean
