#include <armadillo>
#include <cmath>
#include "algorithm.hpp"
#include "construct_matrix.hpp"

using namespace std;

bool jacobi_eigensolver(int dim, arma::vec& eigenvalues, arma::mat& eigenvectors){
    // Simpler version of the Eigensolver for when you only care about the eigenvalues and vectors.
    // Returns convergence to make sure the algorithm finished
    double tol = 1e-8;
    bool converged;
    int maxiter = 100000;
    int iterations;
    arma::mat A = create_tridiagonal_buckling_beam(dim);
    jacobi_eigensolver(A,tol,eigenvalues, eigenvectors, maxiter, iterations, converged);

    return converged;
}

void jacobi_eigensolver(arma::mat& A, double eps, arma::vec& eigenvalues,
arma::mat& eigenvectors, const int maxiter, int& iterations, bool& converged){

    // Declarations for largest off-diagonal value, and the corresponding indices
    double max_val;
    int k,l;

    // Rotation matrix + dimension of matrices
    int n = A.n_cols;
    arma::mat R(n,n,arma::fill::eye);

    // Start at 0 iterations, and without convergence
    iterations = 0;
    converged = false;

    while (iterations < maxiter){
        // Updates the matrix up to a maxiter times, or until convergence is reached

        // Finds the largest off-diagonal element, and checks if it is small enough
        // If it is, convergence is reached, and the program is terminated
        max_val = max_offdiag_symmetric(A, k, l);
        if (max_val < eps) {
            converged = true;
            break;
        }

        // Rotates away the largest off-diagonal element with the jacobi algorithm
        jacobi_rotate(A, R, k, l);
        iterations++;
    }

    // Collects eigenvalues and eigenvectors from the diagonalised metrix, and the rotation matrix respectively
    eigenvalues = arma::diagvec(A);
    eigenvectors = R;

    // Sorts eigenvalues in ascending order, and eigenvectors in the same order
    arma::uvec indices = arma::sort_index(eigenvalues);
    eigenvectors = eigenvectors.cols(indices);
    eigenvalues = eigenvalues.elem(indices);

    // Makes sure the first element in positive by flipping some vectors
    for (int i = 0; i < n; i++){
        if (eigenvectors(0,i) < 0){
            eigenvectors.col(i) *= -1;
        }
    }
}

void jacobi_rotate(arma::mat& A, arma::mat& R, const int& k, const int& l){
    // Rotates the matrix A once to set A_(kl) = A_(lk) = 0
    // Updates the rotation matric R with the rotation that was just used
    // Assumes that A(k,l) != 0

    // Temporary values used to reduce number of FLOPs
    double temp1 = A(l,l) - A(k,k);
    double temp2 = 2*A(k,l);
    double tau = temp1/temp2;

    // Finds cosine (c) and sine (s) for the required rotation angle
    // Tangent (t) is only used to find these
    double t = (tau > 0) ? -tau + sqrt(1 + pow(tau,2)) : -tau - sqrt(1 + pow(tau,2));
    double c = 1/sqrt(1 + pow(t,2));
    double s = c*t;


    // Updates affected diagonal elements of A
    // Temporary values are used to reduce amount of FlOPs
    // Does the same as the two lines of code in a comment below
    // Recycles tau
    // 7 FlOPs
    tau = A(k,k);
    double temp3 = pow(c,2)*temp1 + temp2*c*s;
    A(k,k) = A(l,l) - temp3;
    A(l,l) = tau + temp3;

    /* // Alternative method with 18 FLOPs
    A(k,k) = tau*pow(c,2) - 2 * A(k,l)*c*s + A(l,l)*pow(s,2);
    A(l,l) = A(l,l)*pow(c,2) + 2* A(k,l)*c*s + tau*pow(s,2);
    */


    // Updates affected off-diagonal elements of A
    A(k,l) = 0;
    A(l,k) = 0;
    int n = A.n_cols;
    for (int i = 0; i < n; i++){
        // Updates the intersection of row i and columns k and l for the rotations matrix R
        // Recycles tau
        tau = R(i,k);
        R(i,k) = R(i,k)*c - R(i,l)*s;
        R(i,l) = R(i,l)*c + tau*s;


        // Updates the intersection of row i and columns k and l for the matrix A
        // Updates corresponding intersections to keep it symmetric
        // Skips if i is equal to k or l, as this would would update the diagonal, and A(k,l)
        // Order of the block below is chosen to avoid extra temporary variables
        if (i == k || i == l){
            continue;
        }
        A(i,k) = A(i,k)*c - A(i,l)*s;
        A(i,l) = A(i,l)*c + A(k,i)*s;
        A(k,i) = A(i,k);
        A(l,i) = A(i,l);
    }
}

double max_offdiag_symmetric(const arma::mat& A, int& k, int& l){
    // Updates the indices k and l so they become the indices of the largest
    // off diagonal element in a symmetric matrix
    // Returns the largest off- diagonal value

    // Finds dimension of matrix
    // Sets max_val to -1 to make sure k,l are given values
    int n = A.n_cols;
    double max_val = -1.;

    // Checks every element above the diagonal
    for (int i = 0; i < n - 1; i++){
        for (int j = i + 1; j < n; j++){
            if (abs(A(i,j)) > max_val){
                // Updates value if condition is met
                max_val = abs(A(i,j));
                k = i;
                l = j;
            }
        }
    }
    return max_val;
}
