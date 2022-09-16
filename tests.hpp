#ifndef TESTS_HPP
#define TESTS_HPP

bool test_max_offdiag_symmetric();
bool test_tridiagonal_construction();
bool test_jacobi_eigensolver();
bool compare_with_analytical(const arma::mat&, const arma::vec&, const double&, const double&);

#endif
