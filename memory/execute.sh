#!/bin/bash

gcc --std=c11 -O3 -o basic -g basic.c
gcc --std=c11 -O3 -o strassen -g strassen.c

echo "n,program,instructions,CPI,l1-cache-hit ratio,last-cache-hit ratio" > out.csv

arg=16
for i in {4..14}
do
    echo -n "$arg,basic," >> out.csv

    perf stat -r 5 -o temp.txt ./basic $arg
    python3 instructions.py temp.txt >> out.csv

    perf stat -e cache-references,cache-misses -r 5 -o temp.txt ./basic $arg
    python3 cache.py temp.txt >> out.csv
    echo -n "," >> out.csv
    perf stat -e LLC-loads,LLC-load-misses -o temp.txt ./basic 32
    python3 cache.py temp.txt >> out.csv

    echo -e -n "\n$arg,strassen," >> out.csv

    perf stat -r 5 -o temp.txt ./strassen $arg
    python3 instructions.py temp.txt >> out.csv

    perf stat -e cache-references,cache-misses -r 5 -o temp.txt ./strassen $arg
    python3 cache.py temp.txt >> out.csv
    echo -n "," >> out.csv
    perf stat -e LLC-loads,LLC-load-misses -o temp.txt ./strassen 32
    python3 cache.py temp.txt >> out.csv

    echo "" >> out.csv

    arg=$((arg*2))
done

rm temp.txt basic strassen
printf "Done writing to out.csv\n"