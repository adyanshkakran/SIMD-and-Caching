#!/bin/bash

gcc dot.c -o dot
gcc -mavx2 vector_dot.c -o vector_dot
gcc -mavx2 even_vector.c -o even_vector

echo "n,dot,vector_dot,even_vector" > out.csv

arg=16000
for i in {1..18}
do
    echo "Matrix Size: $arg"
    echo -n "$arg," >> out.csv
    ./dot $arg >> out.csv

    echo -n "," >> out.csv
    ./vector_dot $arg >> out.csv

    echo -n "," >> out.csv
    ./even_vector $arg >> out.csv

    echo "" >> out.csv

    arg=$((arg*2))
done

rm dot
rm vector_dot
rm even_vector