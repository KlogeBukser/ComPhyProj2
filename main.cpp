#include <iostream>
//#include <cmath>
//#include <iomanip>
//#include <fstream>
//#include <vector>
#include <string>
#include <armadillo>

#include "construct_matrix.hpp"
#include "tests.hpp"
#include "algorithm.hpp"
#include "find_results.hpp"

using namespace std;

int main(int argc, char * argv[]){

    if (!test_tridiagonal_construction()){
        //This is just a test, it isn't needed for the program to work.
        cout << "Construction failed \n";
        return 1;
    }

    if (!test_max_offdiag_symmetric()){
        cout << "Failed to find proper max_values \n";
        return 1;
    }
    if (!test_jacobi_eigensolver()){
        cout << "Eigensolver failed \n";
        return 1;
    }

    solve_n_rotations("textfiles/sparse.txt", 10, 200, false);
    solve_n_rotations("textfiles/dense.txt", 10, 200, true);



    return 0;
}
