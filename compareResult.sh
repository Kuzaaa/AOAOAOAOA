


make baseline

./exec 10 1 1 > r1

make block_cache

./exec 10 1 1 > r2

cmp r1 r2


