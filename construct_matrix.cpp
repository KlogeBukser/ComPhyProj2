#include <armadillo>

arma::mat create_tridiagonal(int n, double a, double d, double e) {
    // Makes n*n matrix and fills the diagonal with input value d
    arma::mat A = arma::mat(n, n, arma::fill::eye)*d;

    // Loop that sill the sub- and superdiagonals with a,e respectively
    for (int i = 0; i < n - 1; i++){
        A(i,i+1) = e;
        A(i+1,i) = a;
    }

    return A;
}

arma::mat create_tridiagonal_symmetric(int n, double a, double d) {
    // Creates a symmetric tridiagonal matrix with create_tridiagonal as a 'parent' function
    return create_tridiagonal(n,a,d,a);
}
