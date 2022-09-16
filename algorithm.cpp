#include <armadillo>
#include <cmath>
#include "algorithm.hpp"

using namespace std;


void jacobi_eigensolver(arma::mat& A, double eps, arma::vec& eigenvalues,
arma::mat& eigenvectors, const int maxiter, int& iterations, bool& converged){
    // Lots of stuff

    // Declarations for largest off-diagonal value, and the corresponding indeces
    // max_val is initialized to make sure the while function works
    double max_val = 2*eps;
    int k,l;

    // Rotation matrix + dimension of matrices
    int n = A.n_cols;
    arma::mat R(n,n,arma::fill::eye);

    // Start at 0 iterations, and without convergence
    iterations = 0;
    converged = false;

    while (iterations < maxiter || max_val > eps){
        max_val = max_offdiag_symmetric(A, k, l);
        if (max_val == 0) {
            converged = true;
            break;
        }
        jacobi_rotate(A, R, k, l);
        iterations++;
    }

    eigenvectors = R;
    eigenvalues = arma::diagvec(A);

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
    // the variable tau is recycled
    // method 1:
    // 18 FlOPs
    tau = A(k,k);
    A(k,k) = tau*pow(c,2) - 2 * A(k,l)*c*s + A(l,l)*pow(s,2);
    A(l,l) = A(l,l)*pow(c,2) + 2* A(k,l)*c*s + tau*pow(s,2);

    /*
    // Alternative method for the previous section that might reduce computation speed,
    // but lose readability
    // 7 FlOPs
    tau = A(k,k);
    double temp3 = pow(c,2)*temp1 + temp2*c*s;
    A(k,k) = A(l,l) - temp3;
    A(l,l) = tau + temp3;
    */

    // Updates off-diagonal elements of A
    A(k,l) = 0;
    A(l,k) = 0;
    int n = A.n_cols;
    for (int i = 0; i < n-1; i++){
        // Updates the intersection of row i and columns k and l for the rotations matrix R
        // Recycles tau
        tau = R(i,k);
        R(i,k) = R(i,k)*c - R(i,l)*s;
        R(i,l) = R(i,l)*c + tau*s;


        // Updates the intersection of row i and columns k and l for the matrix A
        // Updates corresponding intersections to keep it symmetric
        // Skips if i is equal to k or l, as this would would update the diagonal, and A(k,l)
        if (i == k || i == l){
            continue;
        }
        A(i,k) = A(i,k)*c - A(i,l)*s;
        A(i,l) = A(i,l)*c + A(k,i)*s;
        A(k,i) = A(i,k);
        A(l,i) = A(i,l);
    }

    return;
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
