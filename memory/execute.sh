#!/bin/bash

gcc --std=c11 -o basic -g basic.c
gcc --std=c11 -o strassen -g strassen.c

BASIC="./basic"
STRASSEN="./strassen"

echo "n,program,instructions,CPI,l1-cache-hit ratio,l2-cache-hit ratio,l3-cache-hit-ratio,time" > out.csv

L1_EVENTS="L1-dcache-loads,L1-dcache-load-misses"
L2_EVENTS="l2_rqsts.all_demand_references,l2_rqsts.all_demand_miss,LLC-stores,LLC-store-misses"
L3_EVENTS="LLC-loads,LLC-load-misses"
CPI="instructions,cycles"

run_perf() {
  local events="$1"
  local size="$2"
  local program="$3"
  echo "Matrix Size: $size" >> temp.txt
  perf stat -e "$events" "$program" "$size" &>> temp.txt
}

> temp.txt

arg=16
for i in {4..10}
do
    echo -n "$arg,basic," >> out.csv

    run_perf "$L1_EVENTS" "$arg" "$BASIC"
    run_perf "$L2_EVENTS" "$arg" "$BASIC"
    run_perf "$L3_EVENTS" "$arg" "$BASIC"
    run_perf "$CPI" "$arg" "$BASIC"
    python3 process.py temp.txt >> out.csv

    > temp.txt

    echo -e -n "$arg,strassen," >> out.csv

    run_perf "$L1_EVENTS" "$arg" "$BASIC"
    run_perf "$L2_EVENTS" "$arg" "$BASIC"
    run_perf "$L3_EVENTS" "$arg" "$BASIC"
    run_perf "$CPI" "$arg" "$BASIC"
    python3 process.py temp.txt >> out.csv

    > temp.txt

    echo "Done with $arg"
    
    arg=$((arg*2))
done


rm temp.txt basic strassen
printf "Done writing to out.csv\n"