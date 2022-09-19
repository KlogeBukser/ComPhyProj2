#include <armadillo>
#include <cmath>

#include "construct_matrix.hpp"
#include "algorithm.hpp"
#include "tests.hpp"
#include "find_results.hpp"
using namespace std;

bool test_jacobi_eigensolver(){
    // Tests whether the eigenvalues, and eigenvectors found using the
    // jacobi_eigensolver function are the same as the analytical ones

    // Constructs the test matrix
    // Makes empty containers for eigenvalues and eigenvectors
    // Declares convergence condition and number of iterations
    // Chooses tolerance and maximum number of iterations
    int n = 6;
    arma::mat test_matrix = create_tridiagonal_buckling_beam(n);
    double tol = 1e-12;
    arma::vec test_eigvals(n);
    arma::mat test_eigvecs(n,n);
    int maxiter = 100;
    int iterations;
    bool converged;

    // calls the eigensolver function to find eigenvalues and eigenvectors
    jacobi_eigensolver(test_matrix, tol, test_eigvals,
    test_eigvecs, maxiter, iterations, converged);

    // Calls comparison function, and returns the boolean output
    return compare_with_analytical(test_eigvecs,test_eigvals, tol, tol);
}

bool test_max_offdiag_symmetric(){
    // Tests whether the function max_offdiag_symmetric can find the indices of
    // the largest off-diagonal element of a symmetric matrix, and its value

    // makes a test matrix
    arma::mat test_mat(4,4,arma::fill::eye);
    test_mat(0,3) = 0.5;
    test_mat(3,0) = 0.5;
    test_mat(1,2) = -0.7;
    test_mat(2,1) = -0.7;

    // Indices that are supposed to be updated
    // Function call to get max value
    int k,l;
    double max_val = max_offdiag_symmetric(test_mat,k,l);

    // Comparison between expected and computed values
    if (max_val != 0.7 || k != 1 || l != 2){
        return false;
    }

    return true;
}

bool test_tridiagonal_construction(){

    // Makes 6*6 dimensional tridiagonal matrix and compares the eigenvalues
    // and vectors from armadillo with the analytical ones
    // returns true if they are sufficiently close, otherwise false

    // Tolerance
    double tol = 1e-8;

    // Defines specific values for this matrix
    int n = 6;
    double scale = pow(n,2);
    double a = -1*scale;
    double d = 2*scale;

    // Defines matrix for the test
    // Finds eigenvalues and vectors with the armadillo function eig_sym
    arma::mat test_matrix = create_tridiagonal(n,a,d,a);
    arma::vec test_eigvals(n);
    arma::mat test_eigvecs(n,n);
    eig_sym(test_eigvals, test_eigvecs, test_matrix);

    return compare_with_analytical(test_eigvecs, test_eigvals, tol, tol);
}

bool compare_with_analytical(const arma::mat& vecs, const arma::vec& vals, const double& vec_tol, const double& val_tol){
    // Takes references to a set of eigenvectors and eigenvalues, and two doubles for tolerance
    // Compares these with the analytical solutions to the buckling beam problem
    // Note that this function is specific for the buckling beam problem


    // Declares relational values
    double abs_prod, diff_vals;

    // Finds number of iterations used for the problem,
    // and makes empty containers to hold analytic results
    int n = vecs.n_cols;
    arma::mat eig_vecs(n,n);
    arma::vec eig_vals(n);

    // Computes analytical eigenvalues and eigenvectors in a loop, then normalizes the vectors
    find_analytical(n,eig_vecs,eig_vals);

    // Compares the absolute difference of the two sets of eigenvalues
    // Uses the inner product of the vectors to check how much they deviate from being paralell
    // Uses separate tolerances for values and vectors
    for (int i = 0; i < n; i++){
        abs_prod = abs(arma::dot(vecs.col(i),eig_vecs.col(i)));
        diff_vals = abs(vals(i) - eig_vals(i));
        if (diff_vals > val_tol || abs_prod < 1 - vec_tol){
            return false;
        }
    }
    return true;
}
