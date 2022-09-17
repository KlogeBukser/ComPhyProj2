import matplotlib.pyplot as plt
import pandas as pd
import numpy as np

def read_plot(filenames,labels):

    n = len(filenames)
    filenames = ["textfiles/" + name for name in filenames]
    datas = [pd.read_csv(filenames[i], header = None) for i in range(n)]
    x_vals = [np.asarray(datas[i][0]) for i in range(n)]
    y_vals = [np.asarray(datas[i][1]) for i in range(n)]

    for i in range(n):
        x = x_vals[i]
        y = y_vals[i]
        plt.plot(x,y, label = labels[i])
    plt.legend()
    plt.show()
