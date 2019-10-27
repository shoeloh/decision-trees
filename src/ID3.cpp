# MIT License
#
# Copyright (c) 2019 shoeloh
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
# =============================================================================
#
# Simulation of the decision tree learning algorithm (ID3 algorithm) 
#
###############################################################################

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <queue>
#include <cstring>
#include <cstdlib>
#include <cmath>

using namespace std;

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

/****************************************************************
Function for reading a file into a data struct
*****************************************************************/
data readData(char* fileName){
	//Initialize variables
	data tempData;
	ifstream tempFile;
	string csvLine, csvElement, tempValue;

	//Open file for reading
	tempFile.open(fileName);

	//Set the number of columns
	tempData.numColumns=21;
	//Initialize number of lines
	tempData.numLines=0;

	//Get the header line
	getline( tempFile, csvLine );

	//Parse the header line into header elements
	istringstream csvStream(csvLine);
	for(int i=0;i<tempData.numColumns;i++){
		getline( csvStream, tempData.dataHeader[i], ',' );
	}

	//Get the data
	while( tempFile.good() && !tempFile.eof() ){
		//Get a line of data
		getline( tempFile, csvLine );
		//Parse the data line into data elements
		istringstream csvStream(csvLine);
		for(int i=0;i<tempData.numColumns;i++){
			getline( csvStream, csvElement, ',' );
			if(csvElement=="0"){tempData.dataValues[tempData.numLines][i]=false;}
			if(csvElement=="1"){tempData.dataValues[tempData.numLines][i]=true;}
		}
		//Add one to the line counter
		tempData.numLines++;
	}

	//Count is one too many
	tempData.numLines--;
	//Close file
	tempFile.close();
	//Return the data structure
	return tempData;
}

/*******************************************************
Function to count the number of nodes in a tree
*******************************************************/
int countNodes( node* rootNode ){
	//Don't count NULL nodes
	if(rootNode==NULL){
		return 0;
	}else{
		//Initialize counter
		int count=1;
		//Recursively count all non-NULL nodes
		count+=countNodes(rootNode->leftNode);
		count+=countNodes(rootNode->rightNode);
		//Return count
		return count;
	}
}

/*******************************************************
Function to set the depth of all nodes in a tree
*******************************************************/
void setDepth(node* rootNode, int count){
	if(rootNode != NULL){
		//Set root depth to counter
		rootNode->depth=count;
		//Recursively set all depths in tree
		setDepth(rootNode->leftNode, count+1);
		setDepth(rootNode->rightNode, count+1);
	}
}

/**************************************************************************
Function to set the ID's of all nodes in a tree using level order traversal
**************************************************************************/
void setIDs(node* rootNode, int count){
	//Initialize variables
	node* tempNode;

	//Initialize a queue. No recursive method exists.
	queue<node*> frontier;
	//Push root node into queue
	frontier.push(rootNode);

	//Iterate through queue as breadth first search (BFS)
	while(!frontier.empty()){
		//Pop front of queue into temp node
		tempNode=frontier.front();
		frontier.pop();
		//Set id according to counter
		tempNode->id=count;
		//Iterate counter
		count++;
		//Add child nodes to queue if they exist
		if(tempNode->rightNode!=NULL){
			frontier.push(tempNode->rightNode);
		}
		if(tempNode->leftNode!=NULL){
			frontier.push(tempNode->leftNode);
		}
	}
}

/*******************************************************
Function to set the parent pointers for all nodes in a tree
*******************************************************/
void setParents(node* rootNode){
	if(rootNode != NULL){
		//If left child node exists, set its parent to root node
		//Recursively set the whole left tree
		if(rootNode->leftNode!=NULL){
			rootNode->leftNode->parentNode=rootNode;
			setParents(rootNode->leftNode);
		}
		//If right child node exists, set its parent to root node
		//Recursively set the whole right tree
		if(rootNode->rightNode!=NULL){
			rootNode->rightNode->parentNode=rootNode;
			setParents(rootNode->rightNode);
		}
	}
}

/*******************************************************
Function to print data
*******************************************************/
void printData( data* tempData ){
	cout << "Number of data lines = " << tempData->numLines << endl;
	//Print header line
	for(int n=0;n<21;n++){
		cout << setw(2) << tempData->dataHeader[n] << " " ;
	}
	cout << endl;
	//Print data
	for(int i=0;i<tempData->numLines;i++){
		for(int j=0;j<21;j++){
			cout << setw(2) << tempData->dataValues[i][j] << " ";
		}
	 cout << endl;
	}
}

/*******************************************************
Function to print a node
*******************************************************/
void printNode( node* tempNode ){
	cout << "\nNode id = " << tempNode->id << endl;
	cout << "Target attribute = " << tempNode->targetAttribute << endl;
	cout << "depth = " << tempNode->depth << endl;
	cout << "Number of zeros and ones = " << tempNode->zeroNum << "," << tempNode->oneNum << endl;
	cout << "entropy = " << tempNode->entropy <<endl;
	cout << "Split attribute = " << tempNode->splitAttribute << endl;
	cout << "Split value = " << tempNode->splitValue << endl;
	cout << "Label = " << tempNode->label << endl;
	cout << "attributeState = " << endl;
	for(int i=0;i<21;i++){
		cout << setw(6) << i << " ";
	}
	cout << endl;
	for(int i=0;i<21;i++){
		cout << setw(6) << tempNode->attributeState[i].selected << " ";
	}
	cout << endl;
	for(int i=0;i<21;i++){
		cout << setw(6) << tempNode->attributeState[i].value << " ";
	}
	cout << "\nParent node address = " << tempNode->parentNode << endl;
	cout << "Node address = " << tempNode << endl;
	cout << "Left child node address = " << tempNode->leftNode << endl;
	cout << "Right child node address = " << tempNode->rightNode << endl;
}

/*******************************************************
Function to print a tree in preorder traversal
*******************************************************/
void preorderPrint(node* rootNode){
	//Only print if node is not NULL
	if(rootNode != NULL ){
		//If splitAttribute!=-1 and label=-1 then its a root or interior node
		if(rootNode->splitAttribute!=-1&&rootNode->label==-1){
			//If root, print root info
			if(rootNode->parentNode==NULL){
				cout << rootNode->id << ") " << "[" << rootNode->entropy << "] " << "{" << rootNode->oneNum+rootNode->zeroNum << "} ";
			}
			//If interior node then print desired output
			if(rootNode->parentNode!=NULL){
				//Print trailing markers
				cout << "\n";
				for(int i=0;i<rootNode->depth;i++){
					cout << "| ";
				}
			//Print splitAttribute and value from node
			cout << rootNode->id << ") " << rootNode->examples.dataHeader[rootNode->parentNode->splitAttribute] << " = " << rootNode->splitValue << " : ";
			}
		}

		//If splitAttribute=-1 and label!=-1 then its a leaf node
		if(rootNode->splitAttribute==-1&&rootNode->label!=-1){
			//Print trailing markers
			cout << "\n";
			for(int i=0;i<rootNode->depth;i++){
				cout << "| ";
			}
			//Print splitAttribute and value from node
			cout << rootNode->id << ") "  << rootNode->examples.dataHeader[rootNode->parentNode->splitAttribute] << " = " << rootNode->splitValue << " : ";
			//Print the label
			cout << rootNode->label << " *";
		}

		//Recursively print the whole tree
		preorderPrint(rootNode->rightNode);
		preorderPrint(rootNode->leftNode);

	}else{
		//Null node. Do nothing
	}
}

/*******************************************************
Function to verbose print a tree in preorder traversal
*******************************************************/
void preorderPrintVerbose(node* rootNode){
	//Only print if node is not NULL
	if(rootNode != NULL ){
		//If splitAttribute!=-1 and label=-1 then its a root or interior node
		if(rootNode->splitAttribute!=-1&&rootNode->label==-1){
			//If root, print root info
			if(rootNode->parentNode==NULL){
				cout << rootNode->id << ") " << "[" << rootNode->entropy << "] " << "{" << rootNode->oneNum+rootNode->zeroNum << "} ";
			}
			//If interior node then print desired output
			if(rootNode->parentNode!=NULL){
				//Print trailing markers
				cout << "\n";
				for(int i=0;i<rootNode->depth;i++){
					cout << "| ";
				}
			//Print splitAttribute and value from node
			cout << rootNode->id << ") " << "[" << rootNode->entropy << "] " << "{" << rootNode->oneNum+rootNode->zeroNum << "} "<< rootNode->examples.dataHeader[rootNode->parentNode->splitAttribute] << " = " << rootNode->splitValue << " : ";
			}
		}

		//If splitAttribute=-1 and label!=-1 then its a leaf node
		if(rootNode->splitAttribute==-1&&rootNode->label!=-1){
			//Print trailing markers
			cout << "\n";
			for(int i=0;i<rootNode->depth;i++){
				cout << "| ";
			}
			//Print splitAttribute and value from node
			cout << rootNode->id << ") " << "[" << rootNode->entropy << "] " << "{" << rootNode->oneNum+rootNode->zeroNum << "} "<< rootNode->examples.dataHeader[rootNode->parentNode->splitAttribute] << " = " << rootNode->splitValue << " : ";
			//Print the label
			cout << rootNode->label << " * [" << rootNode->entropy << "] ";
		}

		//Recursively print the whole tree
		preorderPrintVerbose(rootNode->rightNode);
		preorderPrintVerbose(rootNode->leftNode);

	}else{
		//Null node. Do nothing
	}
}

/**********************************************************
Function to print the nodes of a tree in preorder traversal
**********************************************************/
void preorderPrintNode(node* rootNode){
	if(rootNode != NULL){
		//Print node
		printNode(rootNode);
		//Recursively print the whole tree
		preorderPrintNode(rootNode->leftNode);
		preorderPrintNode(rootNode->rightNode);
	}
}

/*******************************************************
Function to print a node of a tree given its ID
*******************************************************/
void printNodeByID(node* rootNode, int ID){
	if(rootNode != NULL){
		//If node id is target ID
		if(rootNode->id==ID){
			//Print node
			printNode(rootNode);
		}
		//Recursive search
		printNodeByID(rootNode->leftNode, ID);
		printNodeByID(rootNode->rightNode, ID);
	}
}

/*********************************************************************
Function to calculate entropy of a node given number of zeros and ones
*********************************************************************/
double calcNodeEntropy(int z, int o){
	//Initialize variables
	double entropy=0.0;
	double zeros=z, ones=o;

	//Calculate P0 and P1
	double p0=zeros/(zeros+ones);
	double p1=ones/(zeros+ones);

	//Exception handling. Should not happen.
	if( (z==0)&(o==0)){
		//cout << "Warning! All zero's and one's in calculating node entropy!";
		return 0.0;
	}

	//Calculate entropy
	//If either zeros or ones are 0 then its a pure state and entropy is zero
	if(z==0||o==0){
		return 0.0;
	}
	//Else calculate and return entropy for non-pure state
	entropy=-p0*log10(p0)/log10(2.0) - p1*log10(p1)/log10(2.0);
	return entropy;
}

/*****************************************************************************
Function to determine if a line of data has the attributes selected for a node
*****************************************************************************/
bool hasAttributes(attribute_state attribs[21], bool lineOfData[21], int targetAttribute){
	//Initialize variables
	bool answer=true;

	//Compare the data values to the selected attributes
	//Iterate over all attributes
	for(int i=0;i<21;i++){
		//Only compare if the attribute has been selected and is not targetAttribute
		if(attribs[i].selected==true&&i!=targetAttribute){
			//Set answer to false if line of data does not compare to selected attribute
			if(attribs[i].value!=lineOfData[i]){
				answer=false;
			}
		}
	}
	//Return the answer
	return answer;
}

/*******************************************************
Function to initialize a node
*******************************************************/
void initNode(node* testNode, data examples, int targetAttribute, attribute_state attributes[21]){
	//Initialize variables
	int counter=0;

	//Set default node parameters
	testNode->parentNode=NULL;
	testNode->leftNode=NULL;
	testNode->rightNode=NULL;
	testNode->targetAttribute=targetAttribute;
	testNode->id=-1;
	testNode->depth=-1;
	testNode-> splitAttribute=-1;
	testNode->label=-1;

	//Calculate and initialize the number of classes with zero and one values in the examples
	testNode->zeroNum=0;
	testNode->oneNum=0;
	for(int i=0;i<examples.numLines;i++){
		if(examples.dataValues[i][targetAttribute]==0){testNode->zeroNum++;}
		if(examples.dataValues[i][targetAttribute]==1){testNode->oneNum++;}
	}

	//Calculate and initialize the node entropy
	testNode->entropy=calcNodeEntropy(testNode->zeroNum,testNode->oneNum);

	//Initialize the node state of all 21 attributes
	for(int i=0;i<21;i++){
		testNode->attributeState[i].selected=attributes[i].selected;
		testNode->attributeState[i].value=attributes[i].value;
	}

	//Initialize node example data
	testNode->examples.numColumns=21;
	for(int i=0;i<testNode->examples.numColumns;i++){
		testNode->examples.dataHeader[i]=examples.dataHeader[i];
	}
	//Calculate and initialize the number of examples
	for(int i=0;i<examples.numLines;i++){
		for(int j=0;j<examples.numColumns;j++){
			testNode->examples.dataValues[i][j]=examples.dataValues[i][j];
		}
		counter++;
	}
	testNode->examples.numLines=counter;
}

/************************************************************************
Function to calculate the info gain from splitting a node on an attribute
************************************************************************/
double calcInfoGain (node* testNode, int splitAttribute){
	//Initialize variables
	int leftCount=0, rightCount=0;
	int lZeros=0, lOnes=0, rZeros=0, rOnes=0;
	double pEntropy, lEntropy, rEntropy;
	double gain=0.0;

	//Iterate through all the data
	for(int i=0;i<testNode->examples.numLines;i++){
		//Calculate the class counts and number of zeros/ones for each example
		//Calculate for left child node
		if(testNode->examples.dataValues[i][splitAttribute]==0){
			leftCount++;
			if(testNode->examples.dataValues[i][testNode->targetAttribute]==0){
				lZeros++;
			}
			if(testNode->examples.dataValues[i][testNode->targetAttribute]==1){
				lOnes++;
			}
		}
		//Calculate for right child node
		if(testNode->examples.dataValues[i][splitAttribute]==1){
			rightCount++;
			if(testNode->examples.dataValues[i][testNode->targetAttribute]==0){
				rZeros++;
			}
			if(testNode->examples.dataValues[i][testNode->targetAttribute]==1){
				rOnes++;
			}
		}
	}

	//Get entropies
	pEntropy=testNode->entropy;
	lEntropy=calcNodeEntropy(lZeros,lOnes);
	rEntropy=calcNodeEntropy(rZeros,rOnes);

	//Convert counts to doubles
	double lC=leftCount, rC=rightCount;

	//Calculate the information gain by splitting on the attribute
	gain=pEntropy-(lC*lEntropy/(lC+rC)+rC*rEntropy/(lC+rC));

	//Return the information gain
	return gain;
}

/*****************************************************************
Function to determine which attribute to split on
*****************************************************************/
int calcSplitAttribute(node* testNode){
	//Initialize variables
	double maxInfoGain=-1.0, tempGain=-1.0;
	int splitAttribute=-1;

	//Loop through all attributes states and determine max value of infoGain
	for(int i=0;i<21;i++){
		//Do not count attributes that have already been selected
		if(testNode->attributeState[i].selected==false){
			//Calculate information gain by splitting on attribute
			tempGain=calcInfoGain(testNode, i);
			//Update maxInfoGain if infoGain for splitting on attribute is largest
			//Update split attribute value corresponding to max gain
			if(tempGain>maxInfoGain){
				maxInfoGain=tempGain;
				splitAttribute=i;
			}
		}
	}
	//Return attribute that has maximal info gain from splitting on.
	//Return -1 if no attribute split provides info gain.
	if(maxInfoGain<0.000001){
		return -1;
	}else{
		return splitAttribute;
	}
}

/*****************************************************************
Function to determine if all examples are positive
*****************************************************************/
bool allPos(data* examples, int targetAttribute){
	//Initialize variables
	int counter=0;
	//Iterate through all examples
	for(int i=0;i<examples->numLines;i++){
		//If target attribute is positive (true) iterate counter
		if(examples->dataValues[i][targetAttribute]==1){
			counter++;
		}
	}
	//If all examples have positive target attribute return true
	if(counter==examples->numLines){
		return true;
	}
	//If not all examples have positive target attribute return false
	return false;
}

/*****************************************************************
Function to determine if all examples are negative
*****************************************************************/
bool allNeg(data* examples, int targetAttribute){
	//Initialize variables
	int counter=0;
	//Iterate through all examples
	for(int i=0;i<examples->numLines;i++){
		//If target attribute is negative (false) iterate counter
		if(examples->dataValues[i][targetAttribute]==0){
			counter++;
		}
	}
	//If all examples have negative target attribute return true
	if(counter==examples->numLines){
		return true;
	}
	//If not all examples have negative target attribute return false
	return false;
}

/*****************************************************************
Function to use ID3 to create a tree
*****************************************************************/
node ID3(data examples, int targetAttribute, attribute_state attributes[20]){
	//Create new root node and initialize to default values
	node* rootNode = new node;
	initNode(rootNode, examples, targetAttribute, attributes);

	//If all examples are positive, return single-node tree rootNode with label = +
	if(allPos(&examples, targetAttribute)==true){
		rootNode->label=1;
		return *rootNode;
	}

	//If all examples are negative, return single-node tree rootNode with label = -
	if(allNeg(&examples, targetAttribute)==true){
		rootNode->label=0;
		return *rootNode;
	}

	//If attributes is empty, return the single-node tree rootNode with label = most common value of targetAttribute in examples
	int newCounter=0;
	//Calculate the number of unselected attributes
	for(int i=0;i<21;i++){
		if(rootNode->attributeState[i].selected==false){
			newCounter++;
		}
	}

	//Initialize variables
	int zeroCount=0, oneCount=0;
	//If attributes is empty calculate most common label
	if(newCounter==0){
		//Calculate most common value
		for(int i=0;i<rootNode->examples.numLines;i++){
			if(rootNode->examples.dataValues[i][targetAttribute]==0){
				zeroCount++;
			}
			if(rootNode->examples.dataValues[i][targetAttribute]==1){
				oneCount++;
			}
		}
		//If most common label is 0, set it as the rootNode label and return rootNode. Else set to 1 and return.
		if(zeroCount>oneCount){
			rootNode->label=0;
			return *rootNode;
		}else{
			rootNode->label=1;
			return *rootNode;
		}
	}

	/*****************************************************************
	Other wise begin loop
	*****************************************************************/
	//Find the attribute from the list of attributes that best classifies examples
	int splitAttribute=calcSplitAttribute(rootNode);

	//If splitAttribute is -1 then multiple examples with the same attributes give different classifications.
	//Calculate the most common attribute and
	//Return the single-node tree rootNode with label = most common value of targetAttribute in examples
	if(splitAttribute==-1){
		int zeroCount=oneCount=0;
		//Calculate most common value
		for(int i=0;i<rootNode->examples.numLines;i++){
			if(rootNode->examples.dataValues[i][targetAttribute]==0){
				zeroCount++;
			}
			if(rootNode->examples.dataValues[i][targetAttribute]==1){
				oneCount++;
			}
		}
		//If most common label is 0, set it as the rootNode label and return rootNode. Else set to 1 and return.
		if(zeroCount>oneCount){
			rootNode->label=0;
			return *rootNode;
		}else{
			rootNode->label=1;
			return *rootNode;
		}
	}

	//Set the decision attribute for the rootNode to the splitAttribute
	rootNode->splitAttribute=splitAttribute;

	//Loop for each possible value of splitAttribute ... 0 or 1
	//Add a new tree branch below rootNode corresponding to the test attribute = i
	for(int splitValue=0;splitValue<2;splitValue++){
		//Calculate examples and attribute_state for the new tree branch

		//Initialize variables
		attribute_state newAttributes[21];
		data newExamples;
		//Set data header
		for(int i=0;i<examples.numColumns;i++){
			newExamples.dataHeader[i]=examples.dataHeader[i];
		}
		//Set the examples number of columns
		newExamples.numColumns=examples.numColumns;

		//Update attribute state
		//Iterate over all columns
		for(int j=0;j<examples.numColumns;j++){
			//If attribute is the split attribute mark as selected with splitValue
			if(j==splitAttribute){
				newAttributes[j].selected=true;
				newAttributes[j].value=splitValue;
			//Else copy parent value
			}else{
				newAttributes[j].selected=rootNode->attributeState[j].selected;
				newAttributes[j].value=rootNode->attributeState[j].value;
			}
		}

		//Update newExamples.dataValues
		//Initialize counter
		int nCounter=0;
		//Iterate through all examples
		for(int i=0;i<examples.numLines;i++){
			//If line of data has the node attributes
			if(hasAttributes(newAttributes,examples.dataValues[i],rootNode->targetAttribute)){
				//Add the line of data to the node examples
				for(int k=0;k<examples.numColumns;k++){
					newExamples.dataValues[nCounter][k]=examples.dataValues[i][k];
				}
				//Iterate line count
				nCounter++;
			}
		}
		//Set the examples line count
		newExamples.numLines=nCounter;

		//If examples in branch is empty, add a leaf node below branch with most common label
		//Initialize variables
		int newCounter=0;
		//Determine if attributes is empty. If empty newCounter==0
		for(int i=0;i<newExamples.numColumns;i++){
			//Count the number of unselected attributes
			if(newAttributes[i].selected==0){
				newCounter++;
			}
		}

		//Initialize variables
		int zeroCount=0, oneCount=0;
		//If attributes is empty calculate most common label and add a leaf node
		if(newCounter==0){
			//Create a leaf node below this new branch with label = most common value
			node* leafNode = new node;
			initNode(leafNode,newExamples,targetAttribute,newAttributes);
			//Update pointer
			rootNode->leftNode=leafNode;
			//Calculate most common value
			for(int i=0;i<leafNode->examples.numLines;i++){
				if(leafNode->examples.dataValues[i][targetAttribute]==0){
					zeroCount++;
				}
				if(leafNode->examples.dataValues[i][targetAttribute]==1){
					oneCount++;
				}
			}
			//If most common label is 0, set it as the leafNode label. Else set to 1.
			if(zeroCount>oneCount){
				leafNode->label=0;
			}else{
				leafNode->label=1;
			}

		//Else below this branch add the subtree with the selected splitValue
		}else{
			//Create new subtree
			node* subTree = new node;
			//Recursively call ID3
			*subTree = ID3(newExamples,targetAttribute,newAttributes);
			//Update pointers and splitValue
			if(splitValue==0){
				rootNode->leftNode=subTree;
				subTree->splitValue=0;
			}else{
				rootNode->rightNode=subTree;
				subTree->splitValue=1;
			}
		}
	}
	//Return value of root node
	return *rootNode;
}

/******************************************************************
Function to search a tree for a solution to a line of data.
Updates answer pointer to true if there was a target attribute match
*******************************************************************/
void searchSolution(node* rootNode, bool lineOfData[21], bool* answer){
	if(rootNode != NULL){
		//If node attributes matches data attributes and is a leaf node
		if(hasAttributes(rootNode->attributeState ,lineOfData, rootNode->targetAttribute)&&rootNode->leftNode==NULL&&rootNode->rightNode==NULL){
			//If leaf node label matches target attribute of line of data
			if(rootNode->label==lineOfData[rootNode->targetAttribute]){
				//Update pointer to true
				*answer=true;
			}
		}
		//Recursive search
		searchSolution(rootNode->leftNode, lineOfData, answer);
		searchSolution(rootNode->rightNode, lineOfData, answer);
	}
}

/**********************************************************************
Function to calculate the accuracy of a decision tree against a dataset
**********************************************************************/
double calcAccuracy(node* decisionTree, data dataset){
	//Initialize variables
	double accuracy=0.0;
	int count=0;
	bool answer=false;

	//Iterate through all the data
	for(int i=0;i<dataset.numLines;i++){
		//Preorder traverse tree looking for leafs.
		//If line of data has attributes of a leaf, target attribute values of node to data
		//Keep track of number of matches
		answer=false;
		searchSolution(decisionTree,dataset.dataValues[i],&answer);
		if(answer==true){
			count++;
		}
	}
	//Return number of positive matches
	accuracy=double(count)/double(dataset.numLines);
	return accuracy;
}

/*****************************************************************
Function to copy a tree
*****************************************************************/
void copyTree(node* oldTree, node* newTree){
	if(oldTree != NULL){
		//If left child is not NULL
		if(oldTree->leftNode!=NULL){
			//Create new left child node and copy value
			node* newLeftNode = new node;
			*newLeftNode=*oldTree->leftNode;
			newTree->leftNode=newLeftNode;
		}
		//If right child is not NULL
		if(oldTree->rightNode!=NULL){
			//Create new right child node and copy value
			node* newRightNode = new node;
			*newRightNode=*oldTree->rightNode;
			newTree->rightNode=newRightNode;
		}
		//Recursive search
		copyTree(oldTree->leftNode,newTree->leftNode);
		copyTree(oldTree->rightNode,newTree->rightNode);
	}else{
		//NULL node
		newTree = NULL;
	}
}

/********************************************************************
Function to generate a list of node id's for non-leaf nodes in a tree
********************************************************************/
void findNonLeafs(node* rootNode,vector<int>* leafList){
	if(rootNode != NULL){
		//If not leaf node a
		if( (rootNode->leftNode!=NULL||rootNode->rightNode!=NULL) && rootNode->parentNode!=NULL ){
			//Add node id to list
			leafList->push_back(rootNode->id);
		}
		//Recursive search
		findNonLeafs(rootNode->leftNode,leafList);
		findNonLeafs(rootNode->rightNode,leafList);
	}
}

/*****************************************************************
Function to delete a tree
*****************************************************************/
void deleteTree(node* rootNode){
	if(rootNode != NULL){
		node* lNode=rootNode->leftNode;
		node* rNode=rootNode->rightNode;
		delete(rootNode);
		deleteTree(lNode);
		deleteTree(rNode);
	}
}

/*******************************************************************
Function to replace the subtree rooted at rootNode by a leaf node
Assign the majority class of the subset of the data to the leaf node
*******************************************************************/
void replaceSubtree(node* rootNode,int ID){
	if(rootNode != NULL){
		//If node id is the target ID
		if(rootNode->id==ID){deleteTree(rootNode->leftNode);
			int zeroCount=0, oneCount=0;
			//Calculate most common value
			for(int i=0;i<rootNode->examples.numLines;i++){
				if(rootNode->examples.dataValues[i][rootNode->targetAttribute]==0){
					zeroCount++;
				}
				if(rootNode->examples.dataValues[i][rootNode->targetAttribute]==1){
					oneCount++;
				}
			}
			//If most common label is 0, set it as the leafNode label. Else set to 1.
			if(zeroCount>oneCount){
				rootNode->label=0;
				rootNode->splitAttribute=-1;
			}else{
				rootNode->label=1;
				rootNode->splitAttribute=-1;
			}
			//Remove child pointers to make a leaf node
			rootNode->leftNode=rootNode->rightNode=NULL;
			//Memory management
			deleteTree(rootNode->leftNode);
			deleteTree(rootNode->rightNode);
		}
	//Recursive search
	replaceSubtree(rootNode->leftNode,ID);
	replaceSubtree(rootNode->rightNode,ID);
	}
}
