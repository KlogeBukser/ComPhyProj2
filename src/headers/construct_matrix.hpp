#ifndef CONSTRUCT_MATRIX_HPP
#define CONSTRUCT_MATRIX_HPP

arma::mat create_tridiagonal(int, double, double, double);
arma::mat create_tridiagonal_symmetric(int, double, double);
arma::mat create_tridiagonal_buckling_beam(int);
arma::mat create_symmetric_dense(int);

#endif
