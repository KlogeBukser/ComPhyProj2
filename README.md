#Computational Physics Project 2

#TO DO:
**Important
- Find scaling relation between matrix size and required amount of Jacobi transformations
- Plot scaling relation
- Consider how scaling would be affected by dense matrices

- Plot eigenvectors from the algorithm against the corresponding positions.
Include analytical eigenvectors for comparison (for N = 10 and N = 100)

- Look over error handling for test functions
- Consider what libraries are necessary to run the program on mac vs linux,
and if any can be used to speed up program

**Not that important
- Consider reasonable tolerance for test functions, i.e. 'is 1e12 too small/big?'
- Consider using .at() to find elements in armadillo containers to skip boundary checks
- Consider uword as replacement for int when iteration through armadillo objects
- Consider compilation methods to decrease time used by armadillo

#ISSUES:
- Code is super slow due to the armadillo library. Including it adds several seconds to compiling even when not used. It is unclear how much time the armadillo function calls take.

#CODE STRUCTURE:
- Project is compiled and executed by running main.py from the command line.
- Functions for matrix construction are in construct_matrix.cpp
- Functions for the algorithm are put in algorithm.cpp
- Functions for testing are put in the tests.cpp file
- All function files have corresponding header files of the same name, with suffix hpp
- Main.cpp uses the other function-/class-files to solve problems

#CONVENTIONS:
- snake_case (lower case letters separated by an underscore) is for most variable- and function-names, but uppercase letters are occasionally used for matrices
- PascalCase (first letter of every word is capitalized, including the very first word) is used for class names
