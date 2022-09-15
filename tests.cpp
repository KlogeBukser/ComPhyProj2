#include <armadillo>
#include <cmath>

#include "construct_matrix.hpp"
using namespace std;

bool test_tridiagonal_construction(){

    // Makes 6*6 dimensional tridiagonal matrix and compares the eigenvalues
    // and vectors from armadillo with the analytical ones
    // returns true if they are sufficiently close, otherwise false

    // Tolerance and comparison values for test
    double tol = 1e-12;
    double diff_vals;
    double diff_vecs;


    // Defines specific values for this matrix
    int n = 6;
    double a = -1*pow(n+1,2);
    double d = 2*pow(n+1,2);

    // Defines matrix for the test
    // Finds eigenvalues and vectors with the armadillo function eig_sym
    arma::mat test_matrix = create_tridiagonal(n,a,d,a);
    arma::vec test_eigvals;
    arma::mat test_eigvecs;
    eig_sym(test_eigvals, test_eigvecs, test_matrix);
    for (int i = 0; i < n; i++){
        if(test_eigvecs(0,i) < 0){
            // Flip sign of vector if first element is negative
            test_eigvecs.col(i) *= (-1);
        }
    }

    // Makes analytical eigen-values and eigen-vectors
    // Scales eigen-vectors to unit length
    arma::vec anal_eigvals(n);
    arma::mat anal_eigvecs_unscaled(n,n);
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            anal_eigvecs_unscaled(i,j) = sin(((i+1)*(j+1)*M_PI) / (n+1));
        }
        anal_eigvals(i) = d + 2*a * cos(((i+1) * M_PI) / (n+1));
    }
    arma::mat anal_eigvecs = arma::normalise(anal_eigvecs_unscaled);

    // Tests every eigenvalue and eigenvector
    // Return false if their difference is larger than the tolerance, otherwise true
    for (int i = 0; i < n; i++){
        diff_vals = abs(test_eigvals(i) - anal_eigvals(i));
        diff_vecs = max(abs(test_eigvecs.col(i) - anal_eigvecs.col(i)));
        if (diff_vals > tol || diff_vecs > tol){
            cout << "Tridiagonal matrix construction failed \n";
            return false;
        }
    }
    return true;
}
