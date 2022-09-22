
#include <iostream>
#include <armadillo>
#include <string>
#include <cmath>
#include "headers/algorithm.hpp"
#include "headers/construct_matrix.hpp"
#include "headers/find_results.hpp"

void write_analytical(const std::string filename, const int n){
    // Saves the analytical values to file
    arma::mat vecs(n,n);
    arma::vec vals(n);
    find_analytical(n,vecs,vals);
    vecs.save(filename,arma::csv_ascii);
}

void find_analytical(const int& n, arma::mat& eig_vecs, arma::vec& eig_vals){
    // Finds the analytical eigenvectors and eigenvalues
    // Normalises the eigenvectors
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            eig_vecs(i,j) = sin(((i+1)*(j+1)*M_PI) / (n+1));
        }
        eig_vals(i) = 2*pow(n,2)*(1 - cos(((i+1) * M_PI) / (n+1)));
    }
    eig_vecs = arma::normalise(eig_vecs);
}

void solve_n_rotations(const std::string& filename, const arma::uword start, const arma::uword end, bool dense){
    // Overload function where only start and end of interval is given
    solve_n_rotations(filename, start, end, 1, dense);
}

void solve_n_rotations(const std::string& filename, const arma::uword start, const arma::uword end, const int step, bool dense){
    // Overload function where only start,end and stepsize is given
    arma::uvec dims = arma::regspace<arma::uvec>(start,step,end);
    solve_n_rotations(filename, dims, dense);
}


arma::uword req_rotations(const int& n, const double& tol, bool& convergence, bool dense){
    // Uses the eigensolver to find how many rotations are needed for a given matrix size
    // has opton of using either a specific matrix for the buckling problem, or a random symmetric matrix
    arma::mat matrix;
    if (dense){
        matrix = create_symmetric_dense(n);
    } else {
        matrix = create_tridiagonal_buckling_beam(n);
    }

    arma::vec eigvals(n);
    arma::mat eigvecs(n,n);
    int maxiter = 100000;
    int iterations;

    jacobi_eigensolver(matrix, tol, eigvals,
    eigvecs, maxiter, iterations, convergence);

    return iterations;
}

void solve_n_rotations(const std::string& filename, const arma::uvec& mat_dimensions, bool dense){
    // Takes a set of integers, and computes how many rotations are needed to find
    // the eigenvalues of a square tridiagonal matrix of those dimensions
    // setting dense = true gives a random symmetric dense matrix instead

    // Values for the jacobi functions
    double tol = 1e-8;
    bool convergence;
    int n = mat_dimensions.n_elem;

    // Containers for the values of interest
    arma::uvec iterations(n);
    arma::umat vectors(n,2);
    vectors.col(0) = mat_dimensions;

    for (int i = 0; i < n; i++){
        // Finds amount of iterations for a given dimension matrix
        // Stop when a given value is too large to be found
        // Resizes if stopped early to avoid writing any wring data
        convergence = false;
        iterations(i) = req_rotations(mat_dimensions(i),tol,convergence, dense);
        if (!convergence){
            // stops when convergence is no longer reached
            vectors.resize(i,2);
            iterations.resize(i);
            break;
        }
    }
    // Saves data to file
    vectors.col(1) = iterations;
    vectors.save(filename, arma::csv_ascii);
}

void collect_eigen_vectors(const std::string& filename, int n){
    // Finds the 3 eigenvectors with smallest eigenvalues from the jacobi rotation method
    // Writes these vectors to file
    arma::vec eigvals(n);
    arma::mat eigvecs(n,n);

    if(jacobi_eigensolver(n, eigvals, eigvecs)){
        eigvecs.resize(n,3);
        eigvecs.save(filename, arma::csv_ascii);
    }
}
