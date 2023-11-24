import matplotlib.pyplot as plt
import pandas as pd
        
data = pd.read_csv('out.csv')

# plot a 3d plot of l1 size vs l2 size vs miss rate
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
ax.scatter(data.l1_size, data.l2_size, data.miss_rate)
ax.set_xlabel('l1_size')
ax.set_ylabel('l2_size')
ax.set_zlabel('miss_rate')
# set title of graph
ax.set_title('L1 size vs L2 size vs Miss rate')
ax.set_xticks(data.l1_size)
ax.set_yticks(data.l2_size)
plt.savefig('l1_size_vs_l2_size_vs_miss_rate.png')
plt.show()