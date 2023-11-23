import sys

if len(sys.argv) != 5:
    print("Usage: python3 process.py <filename> <l1_size> <l2_size> <runtime>")
    sys.exit()

filename = sys.argv[1]
l1_size = int(sys.argv[2])
l2_size = int(sys.argv[3])
time = float(sys.argv[4])

with open(filename, "r") as file:
    lines = file.readlines()

for line in lines:
    if "D" in line and "refs" in line:
        refs_num = int(line.split()[3].replace(',',''))
    elif "D1" in line and "misses" in line:
        l1_misses_num = int(line.split()[3].replace(',',''))
    elif "LLd" in line and "misses" in line:
        ll_misses_num = int(line.split()[3].replace(',',''))

print(f"{time},{l1_size},{l2_size},{(l1_misses_num+ll_misses_num)/refs_num}")