#ifndef FIND_RESULTS_HPP
#define FIND_RESULTS_HPP

void solve_n_rotations(const std::string&, const arma::uword, const arma::uword, bool);
void solve_n_rotations(const std::string&, const arma::uword, const arma::uword, const int, bool);
void solve_n_rotations(const std::string&, const arma::uvec&, bool);

arma::uword find_req_rotations(const int&, const double&, bool);

void collect_eigen_vectors(const std::string&, int);

void find_analytical(const int&, arma::mat&, arma::vec&);

void write_analytical(const std::string, const int);
#endif
