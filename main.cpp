#include <iostream>
//#include <cmath>
//#include <iomanip>
//#include <fstream>
//#include <vector>
//#include <string>
#include <armadillo>

#include "construct_matrix.hpp"
#include "test_functions.hpp"

using namespace std;

int main(int argc, char * argv[]){

    if (test_tridiagonal_construction()){
        //This is just a test, it isn't needed for the program to work.
        cout << "It works \n";

    }
    return 0;
}
