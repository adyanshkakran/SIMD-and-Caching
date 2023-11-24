#!/bin/bash

gcc --std=c11 -o basic -g basic.c
gcc --std=c11 -o strassen -g strassen.c

BASIC="./basic"
STRASSEN="./strassen"

echo "n,program,instructions,CPI,l1-cache-hit ratio,l2-cache-hit ratio,l3-cache-hit ratio,time" > out.csv

L1_EVENTS="L1-dcache-loads,L1-dcache-load-misses"
L2_EVENTS="l2_rqsts.all_demand_references,l2_rqsts.all_demand_miss,LLC-stores,LLC-store-misses"
L3_EVENTS="LLC-loads,LLC-load-misses"
CPI="instructions,cycles"

> temp.txt

arg=16
for i in {4..10}
do
    echo -n "$arg,basic," >> out.csv

    perf stat -e "$L1_EVENTS" "$BASIC" "$arg" &>> temp.txt
    perf stat -e "$L2_EVENTS" "$BASIC" "$arg" &>> temp.txt
    perf stat -e "$L3_EVENTS" "$BASIC" "$arg" &>> temp.txt
    perf stat -e "$CPI" "$BASIC" "$arg" &>> temp.txt
    python3 process.py temp.txt >> out.csv

    > temp.txt

    echo -e -n "$arg,strassen," >> out.csv

    perf stat -e "$L1_EVENTS" "$STRASSEN" "$arg" &>> temp.txt
    perf stat -e "$L2_EVENTS" "$STRASSEN" "$arg" &>> temp.txt
    perf stat -e "$L3_EVENTS" "$STRASSEN" "$arg" &>> temp.txt
    perf stat -e "$CPI" "$STRASSEN" "$arg" &>> temp.txt
    python3 process.py temp.txt >> out.csv

    > temp.txt

    echo "Done with $arg"
    
    arg=$((arg*2))
done

python3 graph.py


rm temp.txt basic strassen
printf "Done writing to out.csv\n"