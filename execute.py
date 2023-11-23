import os
import matplotlib.pyplot as plt
import numpy as np

L1_sizes = range(16, 64, 16)
L2_sizes = range(512, 2048, 512)
line_size = 64

x = list()
y = list()
z = list()

os.system("gcc -g -o 3 3.c")

for each_l1_size in L1_sizes:
    for each_l2_size in L2_sizes:

        cachegrind_command = f"valgrind --cache-sim=yes --tool=cachegrind --D1={each_l1_size*1024},{each_l1_size*1024//line_size},line_size --LL={each_l2_size*1024},{each_l2_size*1024//line_size},line_size ./3 > cachegrind_output_temp 2>&1"
        print(cachegrind_command)

        os.system(cachegrind_command)

        f = open("cachegrind_output_temp", "r")
        cachegrind_out_lines = f.readlines()
        
        for each_line in cachegrind_out_lines:
            if "D" in each_line and "refs" in each_line:
                refs_num = int(each_line.split()[3].replace(',',''))
            elif "D1" in each_line and "misses" in each_line:
                l1_misses_num = int(each_line.split()[3].replace(',',''))
            elif "LLd" in each_line and "misses" in each_line:
                ll_misses_num = int(each_line.split()[3].replace(',',''))
        

        x.append(each_l1_size)
        y.append(each_l2_size)
        z.append((l1_misses_num+ll_misses_num)/refs_num)

        for file in os.listdir("."):
            if "cachegrind.out" in file:
                cachegrind_file = f"./{file}"
                break
        os.remove(cachegrind_file)
        
        f.close()


x = np.array(x)
y = np.array(y)
z = np.array(z)

best_index = np.argmin(z)
best_l1_size = x[best_index]
best_l2_size = y[best_index]

print(f"Best L1 Size: {best_l1_size}")
print(f"Best L2 Size: {best_l2_size}")
print(f"Best Miss Ratio: {z[best_index]}")


fig, ax = plt.subplots(subplot_kw={"projection": "3d"})
ax.scatter(x, y, z)

ax.set_title('L1 and L2 Cache Sizes Miss Ratios')
ax.set_xlabel('L1 Size')
ax.set_ylabel('L2 Size')
ax.set_zlabel('Miss Ratio')

plt.show()
