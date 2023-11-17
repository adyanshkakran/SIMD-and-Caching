import sys

if len(sys.argv) != 2:
    print("Usage: python3 cache.py <filename>")
    sys.exit()

filename = sys.argv[1]

file = open(filename, "r")
lines = file.readlines()

time = 0
for line in lines:
    if "L1-dcache-loads" in line:
        l1_refs = int(line.split()[0].replace(',',''))
    elif "L1-dcache-load-misses" in line:
        l1_misses = int(line.split()[0].replace(',',''))
    elif "l2_rqsts.all_demand_references" in line:
        l2_refs = int(line.split()[0].replace(',',''))
    elif "l2_rqsts.all_demand_miss" in line:
        l2_misses = int(line.split()[0].replace(',',''))
    elif "LLC-stores" in line:
        llc_refs = int(line.split()[0].replace(',',''))
    elif "LLC-store-misses" in line:
        llc_misses = int(line.split()[0].replace(',',''))
    elif "LLC-loads" in line:
        llc_refs += int(line.split()[0].replace(',',''))
    elif "LLC-load-misses" in line:
        llc_misses += int(line.split()[0].replace(',',''))
    elif "instructions" in line:
        instrs = int(line.split()[0].replace(',',''))
    elif "cycles" in line:
        cycles = int(line.split()[0].replace(',',''))
    elif "seconds time elapsed" in line:
        time += float(line.split()[0].replace(',',''))

time = time / 4 
l1_miss_rate = 1 - l1_misses / l1_refs
l2_miss_rate = 1 - l2_misses / l2_refs
llc_miss_rate = 1 - llc_misses / llc_refs
cpi = cycles / instrs

print(f'{instrs},{cpi:.2f},{l1_miss_rate:.2f},{l2_miss_rate:.2f},{llc_miss_rate:.2f},{time:.4f}')