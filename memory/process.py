import sys

if len(sys.argv) != 2:
    print("Usage: python3 cache.py <filename>")
    sys.exit()

filename = sys.argv[1]

file = open(filename, "r")
lines = file.readlines()

for line in lines:
    if "cache-references" in line:
        ref_cache = int(line.split()[0].replace(",", ""))
    elif "cache-misses" in line:
        miss_cache = int(line.split()[0].replace(",", ""))
    elif "LLC-loads" in line:
        ref_llc = int(line.split()[0].replace(",", ""))
    elif "LLC-load-misses" in line:
        miss_llc = int(line.split()[0].replace(",", ""))
    elif "elapsed" in line:
        time = float(line.split()[0].replace(",", ""))
    elif "instructions" in line:
        words = line.split()
        inst = int(words[0].replace(",", ""))
        cpi = 1/float(words[3].replace(",", ""))

ratio_cache = (ref_cache - miss_cache) / ref_cache * 100
ratio_llc = (ref_llc - miss_llc) / ref_llc * 100
print(f"{inst},{cpi:.2f},{ratio_cache:.2f}%,{ratio_llc:.2f}%,{time:.4f}")