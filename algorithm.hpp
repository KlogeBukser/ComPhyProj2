#ifndef ALGORITHM_HPP
#define ALGORITHM_HPP

void jacobi_eigensolver(arma::mat&, double, arma::vec&, arma::mat&, const int, int&, bool&);
double max_offdiag_symmetric(const arma::mat&, int&, int&);
void jacobi_rotate(arma::mat&, arma::mat&, const int&, const int&);

#endif
