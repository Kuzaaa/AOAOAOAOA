

make baseline

./exec 14 0 1 > r1

make block_cache_mod

./exec 14 0 1 > r2

cmp r1 r2



