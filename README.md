# Computational Physics Project 2

## PRODUCE RESULTS
- Project is compiled and executed by running "python3 src/main.py" from the command line.
- main.py has 5 blocks of code, each with comments describing what they do. The second block need to be run once, and can be commented out after. Block 3,4,5 all produce specific results, and can be commented out if they're not of interest.
- Block 2 takes up quite of lot of time to run, it is advised to only run this once.

## TO DO:
- Look over error handling for test functions
- Look over labels and titles for plots

## CODE STRUCTURE:
- header files are situated in the "headers" folder and plots are saved to "plots" folder.
- txt files are put in folder "textfiles"
- Source code is placed in "src" folder.
- Functions for matrix construction are in construct_matrix.cpp
- Functions for the algorithm are put in algorithm.cpp
- Functions for testing are put in the tests.cpp file
- Functions for collecting results (writing to file etc) are put in find_results.cpp
- All function files have corresponding header files of the same name, with suffix hpp
- Main.cpp uses the other functions to solve problems
- All 3 tests are currently executed every time main.cpp is run

## CONVENTIONS:
- snake_case (lower case letters separated by an underscore) is for most variable- and function-names, but uppercase letters are occasionally used for matrices
- PascalCase (first letter of every word is capitalized, including the very first word) is used for class names
