import sys

if len(sys.argv) != 2:
    print("Usage: python3 cache.py <filename>")
    sys.exit()

filename = sys.argv[1]

file = open(filename, "r")
lines = file.readlines()

for line in lines:
    if "cache-misses" in line:
        misses = int(line.split()[0].replace(',',''))
    elif "CPUs" in line:
        cpus = float(line.split()[4].replace(',',''))

print(f',{cpus},{misses}')