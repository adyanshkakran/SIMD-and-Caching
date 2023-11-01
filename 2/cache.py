import sys

if len(sys.argv) != 2:
    print("Usage: python3 cache.py <filename>")
    sys.exit()

filename = sys.argv[1]

file = open(filename, "r")
lines = file.readlines()

for line in lines:
    if "cache-references" in line or "LLC-loads" in line:
        ref = int(line.split()[0].replace(",", ""))
    elif "cache-misses" in line or "LLC-load-misses" in line:
        miss = int(line.split()[0].replace(",", ""))

ratio = (ref - miss) / ref
print("{:.2f}%".format(ratio * 100),end='')