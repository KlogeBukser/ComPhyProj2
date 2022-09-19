#Computational Physics Project 2

#PRODUCE RESULTS
- Project is compiled and executed by running "python3 main.py" from the command line.
- main.py has 5 blocks of code, each with comments describing what they do. The second block need to be run once, and can be commented out after. Block 3,4,5 all produce specific results, and can be commented out if they're not of interest.
- Block 2 takes up quite of lot of time to run, it is advised to only run this once.

#TO DO:
** Important
- Consider if we should write about how to produce other results, beyond those asked for
- Make it so plotting functions save a plot instead of showing it
- Restructure files into folders (cpp,hpp,py,txt,pdf) and make sure code still works after
- Consider if it makes sense for dense and sparse matrices to need same number of rotations
- Write detailed how to for using this program. Ideally every relevant file is made from one run of main.cpp
- Look over error handling for test functions
- Look over labels and titles for plots


#ISSUES:
- Code is super slow due to the armadillo library. Including it adds several seconds to compiling even when not used. It is unclear how much time the armadillo function calls take.

#CODE STRUCTURE:
- Functions for matrix construction are in construct_matrix.cpp
- Functions for the algorithm are put in algorithm.cpp
- Functions for testing are put in the tests.cpp file
- Functions for collecting results (writing to file etc) are put in find_results.cpp
- All function files have corresponding header files of the same name, with suffix hpp
- Main.cpp uses the other function-/class-files to solve problems
- txt files are put in folder "textfiles"
- All 3 tests are currently executed every time main.cpp is run

#CONVENTIONS:
- snake_case (lower case letters separated by an underscore) is for most variable- and function-names, but uppercase letters are occasionally used for matrices
- PascalCase (first letter of every word is capitalized, including the very first word) is used for class names
