## ABOUT
This program is an implementation and test of the decision tree learning algorithm (see Mitchell Chapter 3).  

This uses the following datasets to test the code:
–Dataset  1. It’s  divided  into  3  parts: training  (for  learning  the model), validation  (for  pruning),  test(for testing performance).
–Dataset  2. It’s  divided  into  3  parts: training  (for  learning the  model), validation  (for  pruning),  test(for testing performance).

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

According to this tree, if wesley = 0 and honor = 0 and barclay = 0,then the class value of the corresponding instance should be 1.  In other words, the value appearing before a colon is an attribute value, and the value appearing after a colon is a class value.

Program was written in c++

## COMPILING, INSTALLATION AND RUNNING
Program files are decision_trees.cpp, ID3.cpp and ID3.hpp

------------------------
Compiling:
------------------------
Easy to compile with g++. Just include the main <decision_trees.cpp>, header <ID3.hpp> and class <ID3.cpp> files.

Example compile command:
g++ decision_trees.cpp ID3.cpp ID3.hpp -o runID3.out

--------------------------------------------------------------------------------------------------------------------
How to run the code and a genric run command statement along with an example test cases below the general statement.
--------------------------------------------------------------------------------------------------------------------
Assume the executable is runID3.out as shown in Compiling: section.

Run the code on a Linux command line.

Generic run command: ./runID3.out <L> <K> <training-set> <validation-set> <test-set> <to-print>
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
-------------------------------------------------
Using Information Gain Heuristic for all datasets
-------------------------------------------------
Results for data_sets1:

Accuracy for the Decision Tree on the test set is: 0.7585 

Post pruned decision tree table:
L
M
Post pruned decision tree accuracy against test data
100
1
.7605
100
3
.7695
100
5
.7630
100
10
.7610
100
15
.7640
100
20
.7725
100
25
.7760
100
30
.7655
100
35
.7715
10
25
.7680

-------------------------------------------------
Results for data_sets2:

Accuracy for the Decision Tree on the test set is: 0.7233 

Post pruned decision tree table:
L
M
Post pruned decision tree accuracy against test data
100
1
.7333
100
3
.7383
100
5
.7350
100
10
.7267
100
15
.7417
100
20
.7283
100
25
.7317
100
30
.7283
100
35
.7500
10
15
.7250

---------------------------------------------------------------------------
Example Console Output
---------------------------------------------------------------------------
Input parameters:
L K training-set validation-set test-set to-print
100 25 data_sets2/training_set.csv data_sets2/validation_set.csv data_sets2/test_set.csv YES

Decision Tree values:
nodeID) splitAttrib = splitValue : classification
1) [1] {600} 
| 2) XI = 1 : 
| | 4) XK = 1 : 
| | | 8) XD = 1 : 0 *
| | | 9) XD = 0 : 
| | | | 16) XT = 1 : 
| | | | | 28) XB = 1 : 0 *
| | | | | 29) XB = 0 : 
| | | | | | 50) XC = 1 : 
| | | | | | | 86) XH = 1 : 
| | | | | | | | 134) XL = 1 : 
| | | | | | | | | 186) XN = 1 : 0 *
| | | | | | | | | 187) XN = 0 : 1 *
| | | | | | | | 135) XL = 0 : 1 *
| | | | | | | 87) XH = 0 : 1 *
| | | | | | 51) XC = 0 : 
| | | | | | | 88) XM = 1 : 
| | | | | | | | 136) XJ = 1 : 
| | | | | | | | | 188) XE = 1 : 1 *
| | | | | | | | | 189) XE = 0 : 0 *
| | | | | | | | 137) XJ = 0 : 0 *
| | | | | | | 89) XM = 0 : 1 *
| | | | 17) XT = 0 : 
| | | | | 30) XF = 1 : 
| | | | | | 52) XO = 1 : 
| | | | | | | 90) XH = 1 : 
| | | | | | | | 138) XE = 1 : 
| | | | | | | | | 190) XL = 1 : 0 *
| | | | | | | | | 191) XL = 0 : 1 *
| | | | | | | | 139) XE = 0 : 1 *
| | | | | | | 91) XH = 0 : 
| | | | | | | | 140) XL = 1 : 1 *
| | | | | | | | 141) XL = 0 : 
| | | | | | | | | 192) XE = 1 : 
| | | | | | | | | | 230) XG = 1 : 0 *
| | | | | | | | | | 231) XG = 0 : 1 *
| | | | | | | | | 193) XE = 0 : 0 *
| | | | | | 53) XO = 0 : 1 *
| | | | | 31) XF = 0 : 
| | | | | | 54) XB = 1 : 
| | | | | | | 92) XO = 1 : 1 *
| | | | | | | 93) XO = 0 : 0 *
| | | | | | 55) XB = 0 : 
| | | | | | | 94) XR = 1 : 
| | | | | | | | 142) XO = 1 : 
| | | | | | | | | 194) XL = 1 : 0 *
| | | | | | | | | 195) XL = 0 : 1 *
| | | | | | | | 143) XO = 0 : 1 *
| | | | | | | 95) XR = 0 : 0 *
| | 5) XK = 0 : 
| | | 10) XC = 1 : 
| | | | 18) XD = 1 : 
| | | | | 32) XF = 1 : 
| | | | | | 56) XO = 1 : 
| | | | | | | 96) XP = 1 : 1 *
| | | | | | | 97) XP = 0 : 0 *
| | | | | | 57) XO = 0 : 0 *
| | | | | 33) XF = 0 : 0 *
| | | | 19) XD = 0 : 
| | | | | 34) XS = 1 : 
| | | | | | 58) XJ = 1 : 
| | | | | | | 98) XO = 1 : 
| | | | | | | | 144) XR = 1 : 1 *
| | | | | | | | 145) XR = 0 : 
| | | | | | | | | 196) XB = 1 : 1 *
| | | | | | | | | 197) XB = 0 : 
| | | | | | | | | | 232) XH = 1 : 1 *
| | | | | | | | | | 233) XH = 0 : 0 *
| | | | | | | 99) XO = 0 : 
| | | | | | | | 146) XF = 1 : 1 *
| | | | | | | | 147) XF = 0 : 
| | | | | | | | | 198) XE = 1 : 1 *
| | | | | | | | | 199) XE = 0 : 0 *
| | | | | | 59) XJ = 0 : 
| | | | | | | 100) XM = 1 : 
| | | | | | | | 148) XQ = 1 : 0 *
| | | | | | | | 149) XQ = 0 : 
| | | | | | | | | 200) XB = 1 : 
| | | | | | | | | | 234) XF = 1 : 1 *
| | | | | | | | | | 235) XF = 0 : 
| | | | | | | | | | | 262) XH = 1 : 1 *
| | | | | | | | | | | 263) XH = 0 : 0 *
| | | | | | | | | 201) XB = 0 : 1 *
| | | | | | | 101) XM = 0 : 0 *
| | | | | 35) XS = 0 : 
| | | | | | 60) XF = 1 : 
| | | | | | | 102) XP = 1 : 
| | | | | | | | 150) XH = 1 : 
| | | | | | | | | 202) XL = 1 : 0 *
| | | | | | | | | 203) XL = 0 : 
| | | | | | | | | | 236) XJ = 1 : 
| | | | | | | | | | | 264) XN = 1 : 1 *
| | | | | | | | | | | 265) XN = 0 : 0 *
| | | | | | | | | | 237) XJ = 0 : 1 *
| | | | | | | | 151) XH = 0 : 1 *
| | | | | | | 103) XP = 0 : 1 *
| | | | | | 61) XF = 0 : 
| | | | | | | 104) XB = 1 : 
| | | | | | | | 152) XE = 1 : 1 *
| | | | | | | | 153) XE = 0 : 0 *
| | | | | | | 105) XB = 0 : 0 *
| | | 11) XC = 0 : 
| | | | 20) XS = 1 : 
| | | | | 36) XR = 1 : 
| | | | | | 62) XG = 1 : 0 *
| | | | | | 63) XG = 0 : 
| | | | | | | 106) XM = 1 : 
| | | | | | | | 154) XD = 1 : 1 *
| | | | | | | | 155) XD = 0 : 0 *
| | | | | | | 107) XM = 0 : 
| | | | | | | | 156) XH = 1 : 
| | | | | | | | | 204) XB = 1 : 
| | | | | | | | | | 238) XF = 1 : 0 *
| | | | | | | | | | 239) XF = 0 : 1 *
| | | | | | | | | 205) XB = 0 : 1 *
| | | | | | | | 157) XH = 0 : 0 *
| | | | | 37) XR = 0 : 
| | | | | | 64) XN = 1 : 
| | | | | | | 108) XH = 1 : 
| | | | | | | | 158) XT = 1 : 
| | | | | | | | | 206) XF = 1 : 1 *
| | | | | | | | | 207) XF = 0 : 0 *
| | | | | | | | 159) XT = 0 : 0 *
| | | | | | | 109) XH = 0 : 
| | | | | | | | 160) XJ = 1 : 1 *
| | | | | | | | 161) XJ = 0 : 
| | | | | | | | | 208) XM = 1 : 1 *
| | | | | | | | | 209) XM = 0 : 
| | | | | | | | | | 240) XD = 1 : 1 *
| | | | | | | | | | 241) XD = 0 : 0 *
| | | | | | 65) XN = 0 : 1 *
| | | | 21) XS = 0 : 
| | | | | 38) XG = 1 : 
| | | | | | 66) XO = 1 : 
| | | | | | | 110) XH = 1 : 
| | | | | | | | 162) XL = 1 : 0 *
| | | | | | | | 163) XL = 0 : 1 *
| | | | | | | 111) XH = 0 : 0 *
| | | | | | 67) XO = 0 : 1 *
| | | | | 39) XG = 0 : 
| | | | | | 68) XM = 1 : 
| | | | | | | 112) XT = 1 : 
| | | | | | | | 164) XL = 1 : 
| | | | | | | | | 210) XP = 1 : 
| | | | | | | | | | 242) XQ = 1 : 
| | | | | | | | | | | 266) XB = 1 : 0 *
| | | | | | | | | | | 267) XB = 0 : 1 *
| | | | | | | | | | 243) XQ = 0 : 1 *
| | | | | | | | | 211) XP = 0 : 0 *
| | | | | | | | 165) XL = 0 : 
| | | | | | | | | 212) XP = 1 : 
| | | | | | | | | | 244) XB = 1 : 0 *
| | | | | | | | | | 245) XB = 0 : 1 *
| | | | | | | | | 213) XP = 0 : 1 *
| | | | | | | 113) XT = 0 : 1 *
| | | | | | 69) XM = 0 : 1 *
| 3) XI = 0 : 
| | 6) XU = 1 : 
| | | 12) XG = 1 : 0 *
| | | 13) XG = 0 : 
| | | | 22) XS = 1 : 
| | | | | 40) XO = 1 : 
| | | | | | 70) XL = 1 : 0 *
| | | | | | 71) XL = 0 : 
| | | | | | | 114) XN = 1 : 1 *
| | | | | | | 115) XN = 0 : 
| | | | | | | | 166) XJ = 1 : 0 *
| | | | | | | | 167) XJ = 0 : 1 *
| | | | | 41) XO = 0 : 0 *
| | | | 23) XS = 0 : 
| | | | | 42) XB = 1 : 
| | | | | | 72) XO = 1 : 
| | | | | | | 116) XJ = 1 : 1 *
| | | | | | | 117) XJ = 0 : 
| | | | | | | | 168) XC = 1 : 
| | | | | | | | | 214) XD = 1 : 1 *
| | | | | | | | | 215) XD = 0 : 0 *
| | | | | | | | 169) XC = 0 : 0 *
| | | | | | 73) XO = 0 : 0 *
| | | | | 43) XB = 0 : 
| | | | | | 74) XF = 1 : 
| | | | | | | 118) XQ = 1 : 
| | | | | | | | 170) XC = 1 : 
| | | | | | | | | 216) XH = 1 : 
| | | | | | | | | | 246) XJ = 1 : 1 *
| | | | | | | | | | 247) XJ = 0 : 
| | | | | | | | | | | 268) XN = 1 : 0 *
| | | | | | | | | | | 269) XN = 0 : 1 *
| | | | | | | | | 217) XH = 0 : 
| | | | | | | | | | 248) XD = 1 : 1 *
| | | | | | | | | | 249) XD = 0 : 0 *
| | | | | | | | 171) XC = 0 : 1 *
| | | | | | | 119) XQ = 0 : 0 *
| | | | | | 75) XF = 0 : 0 *
| | 7) XU = 0 : 
| | | 14) XQ = 1 : 
| | | | 24) XB = 1 : 
| | | | | 44) XO = 1 : 
| | | | | | 76) XM = 1 : 0 *
| | | | | | 77) XM = 0 : 
| | | | | | | 120) XF = 1 : 0 *
| | | | | | | 121) XF = 0 : 
| | | | | | | | 172) XP = 1 : 1 *
| | | | | | | | 173) XP = 0 : 
| | | | | | | | | 218) XL = 1 : 0 *
| | | | | | | | | 219) XL = 0 : 
| | | | | | | | | | 250) XC = 1 : 
| | | | | | | | | | | 270) XK = 1 : 1 *
| | | | | | | | | | | 271) XK = 0 : 
| | | | | | | | | | | | 280) XE = 1 : 0 *
| | | | | | | | | | | | 281) XE = 0 : 
| | | | | | | | | | | | | 284) XD = 1 : 1 *
| | | | | | | | | | | | | 285) XD = 0 : 
| | | | | | | | | | | | | | 286) XG = 1 : 1 *
| | | | | | | | | | | | | | 287) XG = 0 : 
| | | | | | | | | | | | | | | 288) XH = 1 : 
| | | | | | | | | | | | | | | | 290) XJ = 1 : 
| | | | | | | | | | | | | | | | | 292) XN = 1 : 1 *
| | | | | | | | | | | | | | | | | 293) XN = 0 : 
| | | | | | | | | | | | | | | | | | 294) XR = 1 : 1 *
| | | | | | | | | | | | | | | | | | 295) XR = 0 : 
| | | | | | | | | | | | | | | | | | | 296) XS = 1 : 1 *
| | | | | | | | | | | | | | | | | | | 297) XS = 0 : 
| | | | | | | | | | | | | | | | | | | | 298) XT = 0 : 1 *
| | | | | | | | | | | | | | | | 291) XJ = 0 : 1 *
| | | | | | | | | | | | | | | 289) XH = 0 : 1 *
| | | | | | | | | | 251) XC = 0 : 1 *
| | | | | 45) XO = 0 : 0 *
| | | | 25) XB = 0 : 
| | | | | 46) XT = 1 : 
| | | | | | 78) XO = 1 : 
| | | | | | | 122) XM = 1 : 0 *
| | | | | | | 123) XM = 0 : 
| | | | | | | | 174) XH = 1 : 1 *
| | | | | | | | 175) XH = 0 : 
| | | | | | | | | 220) XL = 1 : 
| | | | | | | | | | 252) XC = 1 : 1 *
| | | | | | | | | | 253) XC = 0 : 
| | | | | | | | | | | 272) XD = 1 : 1 *
| | | | | | | | | | | 273) XD = 0 : 0 *
| | | | | | | | | 221) XL = 0 : 0 *
| | | | | | 79) XO = 0 : 1 *
| | | | | 47) XT = 0 : 
| | | | | | 80) XL = 1 : 
| | | | | | | 124) XF = 1 : 
| | | | | | | | 176) XC = 1 : 
| | | | | | | | | 222) XJ = 1 : 
| | | | | | | | | | 254) XK = 1 : 
| | | | | | | | | | | 274) XM = 1 : 0 *
| | | | | | | | | | | 275) XM = 0 : 1 *
| | | | | | | | | | 255) XK = 0 : 1 *
| | | | | | | | | 223) XJ = 0 : 0 *
| | | | | | | | 177) XC = 0 : 
| | | | | | | | | 224) XH = 1 : 
| | | | | | | | | | 256) XE = 1 : 0 *
| | | | | | | | | | 257) XE = 0 : 1 *
| | | | | | | | | 225) XH = 0 : 1 *
| | | | | | | 125) XF = 0 : 0 *
| | | | | | 81) XL = 0 : 
| | | | | | | 126) XR = 1 : 1 *
| | | | | | | 127) XR = 0 : 
| | | | | | | | 178) XN = 1 : 0 *
| | | | | | | | 179) XN = 0 : 
| | | | | | | | | 226) XG = 1 : 
| | | | | | | | | | 258) XP = 1 : 
| | | | | | | | | | | 276) XC = 1 : 0 *
| | | | | | | | | | | 277) XC = 0 : 
| | | | | | | | | | | | 282) XE = 1 : 1 *
| | | | | | | | | | | | 283) XE = 0 : 0 *
| | | | | | | | | | 259) XP = 0 : 1 *
| | | | | | | | | 227) XG = 0 : 1 *
| | | 15) XQ = 0 : 
| | | | 26) XF = 1 : 0 *
| | | | 27) XF = 0 : 
| | | | | 48) XO = 1 : 
| | | | | | 82) XB = 1 : 
| | | | | | | 128) XH = 1 : 1 *
| | | | | | | 129) XH = 0 : 
| | | | | | | | 180) XL = 1 : 
| | | | | | | | | 228) XS = 1 : 0 *
| | | | | | | | | 229) XS = 0 : 
| | | | | | | | | | 260) XJ = 1 : 1 *
| | | | | | | | | | 261) XJ = 0 : 
| | | | | | | | | | | 278) XC = 1 : 1 *
| | | | | | | | | | | 279) XC = 0 : 0 *
| | | | | | | | 181) XL = 0 : 1 *
| | | | | | 83) XB = 0 : 
| | | | | | | 130) XD = 1 : 0 *
| | | | | | | 131) XD = 0 : 
| | | | | | | | 182) XM = 1 : 0 *
| | | | | | | | 183) XM = 0 : 1 *
| | | | | 49) XO = 0 : 
| | | | | | 84) XB = 1 : 0 *
| | | | | | 85) XB = 0 : 
| | | | | | | 132) XJ = 1 : 
| | | | | | | | 184) XG = 1 : 1 *
| | | | | | | | 185) XG = 0 : 0 *
| | | | | | | 133) XJ = 0 : 0 *

Accuracy of unpruned tree against validation data is : 0.773333
Found pruned tree with accuracy : 0.791667


Accuracy of decision tree against test data is : 0.723333
Accuracy of best pruned tree against test data is : 0.751667
Number of nodes pruned = 105 out of 298

## LICENSE 
[Apache 2.0 License](https://github.com/shoeloh/craps/blob/master/LICENSE)

