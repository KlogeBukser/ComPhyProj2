import os
from plotting import read_plot

os.system("g++ -o main.out main.cpp construct_matrix.cpp tests.cpp algorithm.cpp find_results.cpp -larmadillo -std=c++17")
os.system("./main.out")
filenames = (("rot_even.txt", "rot_odd.txt"))
labels = (("Even","Odd"))
read_plot(filenames,labels)
