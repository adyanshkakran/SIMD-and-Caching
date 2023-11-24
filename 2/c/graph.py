import matplotlib.pyplot as plt
import seaborn as sns
import pandas as pd
        
data = pd.read_csv('out.csv')

sns.set_style('darkgrid')

sns.lineplot(x=data.block_size, y=data.miss_rate)
plt.xlabel('block_size')
plt.xticks(data.block_size)
plt.ylabel('miss_rate')
plt.title('Block size vs Miss Rate')
plt.savefig('block_size_vs_miss_rate.png')
plt.show()