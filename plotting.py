import matplotlib.pyplot as plt
import pandas as pd
import numpy as np

def read_plot(filenames, labels, title, xlab, ylab, compare = ""):


    n = len(filenames)
    filenames = ["textfiles/" + name for name in filenames]
    data = [pd.read_csv(filenames[i], header = None) for i in range(n)]
    x_vals = [np.asarray(data[i][0]) for i in range(n)]
    y_vals = [np.asarray(data[i][1]) for i in range(n)]

    plt.title(title)
    plt.xlabel(xlab)
    plt.ylabel(ylab)
    for i in range(n):
        plt.plot(x_vals[i],y_vals[i], label = labels[i])
        if (compare == "2x_squared"):
            plt.plot(x_vals[i], 2*x_vals[i]**2, label = "2x^2")
    plt.legend()
    plt.show()
