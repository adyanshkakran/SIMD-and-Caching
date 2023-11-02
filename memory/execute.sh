#!/bin/bash

gcc --std=c11 -O3 -o basic -g basic.c
gcc --std=c11 -O3 -o strassen -g strassen.c

echo "n,program,instructions,CPI,l1-cache-hit ratio,last-cache-hit ratio,time" > out.csv

arg=16
sudo su -c "echo 0 > /proc/sys/kernel/nmi_watchdog"
for i in {4..6}
do
    echo -n "$arg,basic," >> out.csv

    perf stat -e instructions,cycles,cache-references,cache-misses,LLC-loads,LLC-load-misses -r 5 -o temp.txt ./basic $arg
    python3 process.py temp.txt >> out.csv

    echo -e -n "$arg,strassen," >> out.csv

    perf stat -e instructions,cycles,cache-references,cache-misses,LLC-loads,LLC-load-misses -r 5 -o temp.txt ./strassen $arg
    python3 process.py temp.txt >> out.csv

    arg=$((arg*2))
done

sudo su -c "echo 1 > /proc/sys/kernel/nmi_watchdog"

rm temp.txt basic strassen
printf "Done writing to out.csv\n"