## ABOUT
This program is an implementation and test of the decision tree learning algorithm (see Mitchell Chapter 3).   
 
This uses the following datasets to test the code:  
Dataset  1. It’s  divided  into  3  parts: training  (for  learning  the model), validation  (for  pruning),  test(for testing performance). 
Dataset  2. It’s  divided  into  3  parts: training  (for  learning the  model), validation  (for  pruning),  test(for testing performance). 

When implementing the decision tree learning algorithm the main step is choosing the next attribute to split on. In this example I use the information gain heuristic (see Mitchell Chapter 3). 

Also implemented is a post pruning algorithm (see Mitchell Chapter 3).  

The program includes a function to print the decision tree to standard output.  
I use the following format.  

Wesley = 0 :  
| honor = 0 :  
| | barclay = 0 : 1  
| | barclay = 1 : 0  
| honor > 0 :  
| | tea = 0 : 0  
| | tea = 1 : 1  
wesley = 1 : 0  

According to this tree, if wesley = 0 and honor = 0 and barclay = 0, then the class value of the corresponding instance should be 1.  In other words, the value appearing before a colon is an attribute value, and the value appearing after a colon is a class value.  

Program was written in c++  

## COMPILING, INSTALLATION AND RUNNING  
Program files are decision_trees.cpp, ID3.cpp and ID3.hpp 

# Compiling:  

Easy to compile with g++. Just include the main <decision_trees.cpp>, header <ID3.hpp> and class <ID3.cpp> files.  

Example compile command:  
g++ decision_trees.cpp ID3.cpp ID3.hpp -o runID3.out  

# How to run the code and a genric run command statement along with an example test cases below the general statement.  

Assume the executable is runID3.out as shown in Compiling: section.  

Run the code on a Linux command line.  

Generic run command:  
./runID3.out <L> <K> <training-set> <validation-set> <test-set> <to-print>  
L: integer (used in the post-pruning algorithm)  
K: integer (used in the post-pruning algorithm)  
training-set: path to training data csv file  
validation-set: path to validation data csv file  
test-set: path to test data csv file  
to-print:{yes,no}  

Examples of run command using directory structure as unpacked:  
$ ./runID3.out 100 10 data_sets1/training_set.csv data_sets1/validation_set.csv data_sets1/test_set.csv YES  
$ ./runID3.out 100 10 data_sets2/training_set.csv data_sets2/validation_set.csv data_sets2/test_set.csv NO  
$ ./runID3.out 10 10 data_sets2/training_set.csv data_sets2/validation_set.csv data_sets2/test_set.csv YES  

## RESULTS  

Results are shown in the RESULTS.pdf file  

## LICENSE  
[MIT License](https://github.com/shoeloh/decision-trees/blob/master/LICENSE)  

