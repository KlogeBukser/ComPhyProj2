import os

os.system("g++ -o main.out main.cpp construct_matrix.cpp tests.cpp algorithm.cpp -larmadillo -std=c++17")
os.system("./main.out")
