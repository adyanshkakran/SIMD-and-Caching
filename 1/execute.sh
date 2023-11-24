#!/bin/bash

gcc dot.c -o dot
gcc -mavx2 vector_dot.c -o vector_dot
gcc -mavx2 even_vector.c -o even_vector

echo "n,operation,time,cpu_consumption,cache-misses" > out.csv

arg=100
x=False
for i in {2..16}
do
    echo "Vector Size: $arg"

    echo -n "$arg,dot," >> out.csv
    perf stat -e cache-misses,cpu-clock -o temp.txt  ./dot $arg >> out.csv
    python3 process.py "temp.txt" >> out.csv

    echo -n "$arg,vector_dot," >> out.csv
    perf stat -e cache-misses,cpu-clock -o temp.txt  ./vector_dot $arg >> out.csv
    python3 process.py "temp.txt" >> out.csv

    echo -n "$arg,even_vector," >> out.csv
    perf stat -e cache-misses,cpu-clock -o temp.txt  ./even_vector $arg >> out.csv
    python3 process.py "temp.txt" >> out.csv

    if [ $x = True ]
    then
        arg=$((arg*2))
        x=False
    else
        arg=$((arg*5))
        x=True
    fi
done

python3 graph.py

rm dot vector_dot even_vector temp.txt