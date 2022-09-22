#include <iostream>
#include <string>
#include <armadillo>

#include "headers/tests.hpp"
#include "headers/find_results.hpp"

using namespace std;

int main(int argc, char * argv[]){

    if (!test_tridiagonal_construction()){
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

    solve_n_rotations("textfiles/sparse.txt", 10, 60, false);
    solve_n_rotations("textfiles/dense.txt", 10, 60, true);

    collect_eigen_vectors("textfiles/vecs10.txt", 10);
    collect_eigen_vectors("textfiles/vecs100.txt", 100);
    write_analytical("textfiles/ana100.txt", 100);

    return 0;
}
