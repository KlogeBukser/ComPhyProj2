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
    // Creates a symmetric tridiagonal matrix
    // Uses create_tridiagonal as parent function
    return create_tridiagonal(n,a,d,a);
}

arma::mat create_tridiagonal_buckling_beam(int n){
    // Creates the initial matrix of dimension n*n for the buckling beam problem
    // Uses create_tridiagonal_symmetric as parent function
    double scale = pow(n,2);
    return create_tridiagonal_symmetric(n, -scale, 2*scale);
}

arma::mat create_symmetric_dense(int n){
    arma::mat dense = arma::mat(n,n).randn();
    return arma::symmatu(dense);
}
