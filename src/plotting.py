import matplotlib.pyplot as plt
import pandas as pd
import numpy as np

def read_plot(filenames, outfilename, labels, title, xlab, ylab, compare = ""):
    """
    Plots a set of filenames, with the option of also plotting 2x^2 for comparison
    """

    # Collects values from files
    n = len(filenames)
    filenames = ["textfiles/" + name for name in filenames]
    data = [pd.read_csv(filenames[i], header = None) for i in range(n)]
    x_vals = [np.asarray(data[i][0]) for i in range(n)]
    y_vals = [np.asarray(data[i][1]) for i in range(n)]

    # Title and labels from input
    plt.title(title)
    plt.xlabel(xlab)
    plt.ylabel(ylab)

    # Makes plots
    for i in range(n):
        plt.plot(x_vals[i],y_vals[i], label = labels[i])
        if (compare == "2x_squared"):
            """ Optional comparison """
            plt.plot(x_vals[i], 2*x_vals[i]**2, label = "2x^2")
    plt.legend()
    plt.savefig(outfilename)
    plt.close()


def plot_eigvecs(filename, outfilename):
    """
    Plots the 3 eigenvectors with smallest eigenvalues as well as their analytical counterparts
    """

    # Collects data from files
    data = pd.read_csv("textfiles/" + filename, header = None)
    data_ana = pd.read_csv("textfiles/" + "ana100.txt", header = None)
    n = len(data[0]) + 2
    x = np.linspace(0,1,n)
    x_ana = np.linspace(0,1,102)

    # Same colors for related graphs
    colors = ["r","b","g"]
    for i in range(3):
        """
        Adds boundary Values
        Uses 100 (102) steps for analytical every time
        Plots
        """
        vector = np.zeros(n)
        analytic = np.zeros(102)
        vector[1:-1] = data[i]
        analytic[1:-1] = data_ana[i]
        plt.plot(x, vector, colors[i], label = "Jacobi " + str(i+1))
        plt.plot(x_ana, analytic, colors[i], label = "Analytic " + str(i+1))

    # Labels and title
    plt.title("Eigenvectors from Jacobi method (%d) compared to analytical values" % (n - 2))
    plt.xlabel("x")
    plt.ylabel("u(x)")
    plt.legend()
    plt.savefig(outfilename)
    plt.close()
