import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt

"""
n,operation,time,cpu_consumption,cache-misses
100,dot,0.000001,0.503,22443
100,vector_dot,0.000001,0.529,18159
100,even_vector,0.000001,0.553,21834
1000,dot,0.000003,0.59,19001
1000,vector_dot,0.000002,0.568,18914
1000,even_vector,0.000002,0.594,22584
10000,dot,0.000046,0.808,24045
10000,vector_dot,0.000010,0.709,32695
10000,even_vector,0.000011,0.714,24081

If data is of the form, make graphs between n and time, n and cpu_consumption, n and cache-misses where n should be in log scale. Each graph should have three lines for dot, vector_dot and even_vector.
"""

data = pd.read_csv('out.csv')

sns.set_style('darkgrid')

sns.lineplot(x=data.n, y=data.time, hue=data.operation)
plt.xlabel('n')
plt.xscale('log')
plt.ylabel('time')
plt.yscale('log')
plt.title('n vs time')
plt.savefig('n_vs_time.png')
plt.show()

sns.lineplot(x=data.n, y=data['cpu_consumption'], hue=data.operation)
plt.xlabel('n')
plt.xscale('log')
plt.ylabel('CPU consumption')
plt.title('n vs CPU consumption')
plt.savefig('n_vs_cpu.png')
plt.show()

sns.lineplot(x=data.n, y=data.time, hue=data.operation)
plt.xlabel('n')
plt.xscale('log')
plt.ylabel('Cache misses')
plt.yscale('log')
plt.title('n vs Cache misses')
plt.savefig('n_vs_cache.png')
plt.show()