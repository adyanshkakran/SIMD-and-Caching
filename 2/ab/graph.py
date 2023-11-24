import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt

data = pd.read_csv('out.csv')

sns.set_style('darkgrid')

sns.lineplot(x=data.n, y=data['l1-cache-hit ratio'], hue=data.program)
plt.xlabel('n')
plt.xscale('log')
plt.ylabel('L1 Cache Hit Ratio')
plt.title('n vs L1 Cache Hit Ratio')
plt.savefig('n_vs_l1.png')
plt.show()

sns.lineplot(x=data.n, y=data['l2-cache-hit ratio'], hue=data.program)
plt.xlabel('n')
plt.xscale('log')
plt.ylabel('L2 Cache Hit Ratio')
plt.title('n vs L2 Cache Hit Ratio')
plt.savefig('n_vs_l2.png')
plt.show()

sns.lineplot(x=data.n, y=data['l3-cache-hit ratio'], hue=data.program)
plt.xlabel('n')
plt.xscale('log')
plt.ylabel('L3 Cache Hit Ratio')
plt.title('n vs L3 Cache Hit Ratio')
plt.savefig('n_vs_l3.png')
plt.show()