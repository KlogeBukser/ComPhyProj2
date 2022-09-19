import os
from plotting import *

os.system("g++ -o main.out main.cpp construct_matrix.cpp tests.cpp algorithm.cpp find_results.cpp -larmadillo -std=c++17")
os.system("./main.out")

"""
# Produces comparison between dense and sparse matrix
filenames = ["sparse.txt","dense.txt"]
labels = ["Sparse","Dense"]
title = "Comparison of rotation method for dense and sparse matrices"
read_plot(filenames,labels, title, "Dimension", "Jacobi Rotations")
"""


# Produces comparison plot withh quadratic function
filenames = ["sparse.txt"]
labels = ["Sparse"]
title = "Comparison with x^2"
read_plot(filenames,labels, title, "Dimension", "Jacobi Rotations","2x_squared")
