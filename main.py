# block 1: Imports
import os
from plotting import *

# Block 2: Compilation and execution of c++ code
os.system("g++ -o main.out main.cpp construct_matrix.cpp tests.cpp algorithm.cpp find_results.cpp -larmadillo -std=c++17")
os.system("./main.out")

# Block 3: Produce plot of relation between matrix dimension and number of rotations.
# Compares with quadratic function
#"""
# Produces comparison plot with quadratic function
filenames = ["sparse.txt"]
labels = ["Jacobi"]
title = "How many rotations are necessary for a square matrix"
read_plot(filenames, "n_ro_SR.pdf", labels, title, "Dimension", "Jacobi Rotations","2x_squared")
#"""

# Block 4: Produce plot relation between matrix dimension and number of rotations.
# Compares results for for sparse tridiagonal matrix, and random dense matrix
#"""
# Produces comparison between dense and sparse matrix
filenames = ["sparse.txt","dense.txt"]
labels = ["Sparse","Dense"]
title = "Comparison of rotation method for dense and sparse matrices"
read_plot(filenames,"comp_dense.pdf", labels, title, "Dimension", "Jacobi Rotations")
#"""

# Block 5: produce two plots, each comparing eigenvectors from the jacobi method with the analytical values
#"""
# Produces plots of the 3 eigenvectors with lowest eigenvalues, and compares with the analytical values
plot_eigvecs("vecs10.txt","vecs10.pdf")
plot_eigvecs("vecs100.txt","vecs100.pdf")
#"""
