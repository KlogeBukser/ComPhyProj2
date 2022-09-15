#include <armadillo>

// Create a tridiagonal matrix tridiag(a,d,e) of size n*n,
// from scalar input a, d, and e. That is, create a matrix where
// - all n-1 elements on the subdiagonal have value a
// - all n elements on the diagonal have value d
// - all n-1 elements on the superdiagonal have value e
arma::mat create_tridiagonal(int n, double a, double d, double e)
{
    // Makes n*n matrix and fills diagonal
    arma::mat A = arma::mat(n, n, arma::fill::eye)*d;

    // Loop that sub- and superdiagonals
    for (int i = 0; i < n - 1; i++){
        A(i,i+1) = e;
        A(i+1,i) = a;
    }

    return A;
}
