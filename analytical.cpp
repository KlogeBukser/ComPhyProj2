#include <armadillo>
#include <cmath>

void analytical_eig_vals_vecs(arma::vec& eig_val, arma::mat& eig_vec, const double& a, const double& d){

    int n = eig_vec.n_cols;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            eig_vec(i,j) = sin(((i+1)*(j+1)*M_PI) / (n+1));
        }
        eig_val(i) = d + 2*a * cos(((i+1) * M_PI) / (n+1));
    }
    eig_vec = arma::normalise(eig_vec);
}
