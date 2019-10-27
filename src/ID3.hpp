/* MIT License
 
 Copyright (c) 2019 shoeloh

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 =============================================================================

 Simulation of the decision tree learning algorithm (ID3 algorithm) 
*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <queue>
#include <cstring>
#include <cstdlib>
#include <cmath>

using namespace std;

#ifndef ID3_HPP_
#define ID3_HPP_

/****************************************************************
Structure for storing data
*****************************************************************/
struct data {
    //Number of lines of data read in
    int numLines;
    //Number of columns the state has.
    int numColumns;
    //The header row
    string dataHeader[21];
    //The data. Assumes no more than 2000 lines
    bool dataValues[2000][21];
};

/****************************************************************
Structure for storing the state of an attribute for a node
*****************************************************************/
struct attribute_state {
	//Field to identify if the attribute has already been selected
	bool selected;
	//Field to identify the class value selected if the attribute was selected
	//-1 if not selected. 0 or 1 if selected
	int value;
};

/****************************************************************
Structure for storing node data
*****************************************************************/
struct node {
	//Node id.
	int id;
	//Depth of the node in the tree
	int depth;
	//Number of class values in the data of value zero and one
	int zeroNum, oneNum;
	//Entropy of the node
	double entropy;
	// The attribute that the node splits on to create its children. -1 if a leaf node
	int splitAttribute;
	// The value the attribute took when split
	int splitValue;
	// The targetAttribute
	int targetAttribute;
	// The label for the node
	int label;
	//Array containing the state of all 21 attributes
	attribute_state attributeState[21];
	//Data examples available to the nodes
	data examples;
	//Pointer to parent node
	node *parentNode;
	//Pointer to left child node
	node *leftNode;
	//Pointer to right child node
	node *rightNode;
};

// ID3 Algorithm
node ID3(data examples, int targetAttribute, attribute_state attributes[20]);

//Pruner
void replaceSubtree(node* rootNode,int ID);

//Readers and Initializers and Destructors
data readData(char* fileName);
void initNode(node* testNode, data examples, int targetAttribute, attribute_state attributes[21]);
void deleteTree(node* rootNode);

//Copiers
void copyTree(node* oldTree, node* newTree);

//Setters
void setDepth(node* rootNode, int count);
void setIDs(node* rootNode, int count);
void setParents(node* rootNode);

//Printers
void printData( data* tempData );
void printNode( node* tempNode );
void printNodeByID(node* rootNode, int ID);
void preorderPrint(node* rootNode);
void preorderPrintVerbose(node* rootNode);
void preorderPrintNode(node* rootNode);

//Calculators
int countNodes( node* rootNode );
double calcInfoGain (node* testNode, int splitAttribute);
int calcSplitAttribute(node* testNode);
double calcNodeEntropy(int z, int o);
double calcAccuracy(node* decisionTree, data dataset);
void findNonLeafs(node* rootNode,vector<int>* leafList);

//Testers
bool hasAttributes(attribute_state attribs[21], bool lineOfData[21], int targetAttribute);
bool allPos(data* examples, int targetAttribute);
bool allNeg(data* examples, int targetAttribute);
bool searchSolution(node* rootNode, bool lineOfData[21], bool* answer);

#endif
