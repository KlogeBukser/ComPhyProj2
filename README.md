#Computational Physics Project 2

#TO DO:
- Look over error handling for test functions
- Consider reasonable tolerance for test functions, i.e. 'is 1e12 too small/big?'

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
