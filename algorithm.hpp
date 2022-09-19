#ifndef ALGORITHM_HPP
#define ALGORITHM_HPP

bool jacobi_eigensolver(int, arma::vec&, arma::mat&);
void jacobi_eigensolver(arma::mat&, double, arma::vec&, arma::mat&, const int, int&, bool&);
double max_offdiag_symmetric(const arma::mat&, int&, int&);
void jacobi_rotate(arma::mat&, arma::mat&, const int&, const int&);

#endif
