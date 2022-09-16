#include <armadillo>
#include <cmath>

#include "construct_matrix.hpp"
#include "algorithm.hpp"
#include "tests.hpp"
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

    jacobi_eigensolver(test_matrix, tol, test_eigvals,
    test_eigvecs, maxiter, iterations, converged);

    cout << test_eigvecs;

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
        cout << "The algorithm was unable to find the largest off diagonal element \n";
        cout << "max_val = " << max_val << endl;
        return false;
    }

    return true;
}

bool test_tridiagonal_construction(){

    // Makes 6*6 dimensional tridiagonal matrix and compares the eigenvalues
    // and vectors from armadillo with the analytical ones
    // returns true if they are sufficiently close, otherwise false

    // Tolerance
    double tol = 1e-12;

    // Defines specific values for this matrix
    int n = 6;
    double scale = pow(n+1,2);
    double a = -1;
    double d = 2;

    // Defines matrix for the test
    // Finds eigenvalues and vectors with the armadillo function eig_sym
    arma::mat test_matrix = create_tridiagonal(n,a,d,a);
    arma::vec test_eigvals;
    arma::mat test_eigvecs;
    eig_sym(test_eigvals, test_eigvecs, test_matrix);

    return compare_with_analytical(test_eigvecs,test_eigvals, tol, tol);
}

bool compare_with_analytical(const arma::mat& vecs, const arma::vec& vals, const double& vec_tol, const double& val_tol){

    double abs_prod, diff_vals;

    int n = vecs.n_cols;
    arma::mat eig_vecs(n,n);
    arma::vec eig_vals(n);

    double scale = pow(n+1,2);
    double a = -scale;
    double d = -2*scale;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            eig_vecs(i,j) = sin(((i+1)*(j+1)*M_PI) / (n+1));
        }
        eig_vals(i) = d + 2*a * cos(((i+1) * M_PI) / (n+1));
    }
    eig_vecs = arma::normalise(eig_vecs);
    for (int i = 0; i < n; i++){
        abs_prod = abs(arma::dot(vecs.col(i),eig_vecs.col(i)));
        diff_vals = abs(vals(i) - eig_vals(i));
        if (diff_vals > val_tol || abs_prod < 1 - vec_tol){
            cout << "The eigenvectors or eigenvalues are wrong! \n";
            return false;
        }
    }
    return true;
}
