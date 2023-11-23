import matplotlib.pyplot as plt
import pandas as pd
        
data = pd.read_csv('out.csv')

plt.plot(data.block_size, data.miss_rate)
plt.xlabel('block_size')
plt.xticks(data.block_size)
plt.ylabel('miss_rate')
plt.title('block_size vs. miss_rate')
plt.savefig('block_size_vs_miss_rate.png')
plt.show()