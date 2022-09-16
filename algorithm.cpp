#include <armadillo>
#include <cmath>

using namespace std;

double max_offdiag_symmetric(const arma::mat& A, int& k, int& l){
    // Updates the indices k and l so they become the indices of the largest
    // off diagonal element in a symmetric matrix
    // Returns the largest off diagonal value
    int n = A.n_cols;
    double max_val = 0.;
    // Checks every element above the diagonal
    for (int i = 0; i < n - 1; i++){
        for (int j = i + 1; j < n; j++){
            if (abs(A(i,j)) > abs(max_val)){
                // Updates value if condition is met
                max_val = abs(A(i,j));
                k = i;
                l = j;
            }
        }
    }
    return max_val;
}
