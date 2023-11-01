import sys

if len(sys.argv) != 2:
    print("Usage: python3 instructions.py <filename>")
    sys.exit()

filename = sys.argv[1]

file = open(filename, "r")
lines = file.readlines()

for line in lines:
    if "instructions" in line:
        words = line.split()
        inst = int(words[0].replace(",", ""))
        cpi = float(words[3].replace(",", ""))

print(f'{inst},{cpi:.2f},', end='')