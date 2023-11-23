import sys

if len(sys.argv) != 4:
    print("Usage: python3 process.py <filename> <block_size> <runtime>")
    sys.exit()

filename = sys.argv[1]
block_size = int(sys.argv[2])
time = float(sys.argv[3])

with open(filename, "r") as file:
    lines = file.readlines()

for line in lines:
    if "D" in line and "refs" in line:
        refs_num = int(line.split()[3].replace(',',''))
    elif "D1" in line and "misses" in line:
        l1_misses_num = int(line.split()[3].replace(',',''))
    elif "LLd" in line and "misses" in line:
        ll_misses_num = int(line.split()[3].replace(',',''))

print(f"{time},{block_size},{(l1_misses_num+ll_misses_num)/refs_num}")