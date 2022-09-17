
#include <iostream>
#include <armadillo>
#include <string>
#include "algorithm.hpp"
#include "construct_matrix.hpp"
#include "find_results.hpp"


arma::uword req_rotations(const int& n, const double& tol, bool& convergence){
    arma::mat matrix = create_tridiagonal_buckling_beam(n);
    arma::vec eigvals(n);
    arma::mat eigvecs(n,n);
    int maxiter = 100000;
    int iterations;

    jacobi_eigensolver(matrix, tol, eigvals,
    eigvecs, maxiter, iterations, convergence);

    return iterations;
}

void solve_n_rotations(const arma::uvec& mat_dimensions){

    double tol = 1e-8;
    bool convergence;
    int n = mat_dimensions.n_elem;
    arma::uvec iterations(n);
    arma::umat vectors(n,2);
    vectors.col(0) = mat_dimensions;

    for (int i = 0; i < n; i++){
        convergence = false;
        iterations(i) = req_rotations(mat_dimensions(i),tol,convergence);
        if (!convergence){
            vectors.resize(i,2);
            iterations.resize(i);
            break;
        }
    }
    vectors.col(1) = iterations;
    std::string filename = "textfiles/req_rotations.txt";
    if (vectors.save(filename,arma::csv_ascii)){
        std::cout << "File was written \n";
    }
}
