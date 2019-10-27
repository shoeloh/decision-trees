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
#include <list>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <time.h>

#include "ID3.hpp"

using namespace std;

/*****************************************************************
Main program
*****************************************************************/
int main(int argc, char** argv) {
	  //Check that input arguments were valid
	  if(argc != 7) {
	    cout << argv[0] << ": " << "got " << argc-1 << " arguments. Expecting six: L K training-set validation-set test-set to-print." << endl;
	    return(-1);
	  }

	  //Set variables from input arguments
	  int L = atoi(argv[1]);
	  int K = atoi(argv[2]);
	  char* trainingSet = argv[3];
	  char* validationSet = argv[4];
	  char* testSet = argv[5];
	  char* toPrint = argv[6];

	  //Set verbose print variable
	  bool verbose=true;

	  //Printout variables
	  cout << "Input parameters:" << endl;
	  cout << "L K training-set validation-set test-set to-print" << endl;
	  cout << L << " " << K << " " << trainingSet << " " << validationSet << " " << testSet << " " << toPrint << "\n" << endl;

	  //Seed the random number generator
	  srand(time(NULL));

/*****************************************************************
Read in the training, validation and test data from files
*****************************************************************/
	  //Training Data
	  data trainingData;
	  trainingData=readData(trainingSet);
	  //Validation Data
	  data validationData;
	  validationData=readData(validationSet);
	  //Test Data
	  data testData;
	  testData=readData(testSet);

/*****************************************************************
Initialize starting attributes and target attribute
*****************************************************************/
	 //Set the initial attributes for the root node
	 int targetAttribute=20;
	 attribute_state startingAttributes[21];
	 //Initialize startingAttributes;
	 for(int i=0;i<21;i++){
		 startingAttributes[i].selected=false;
		 startingAttributes[i].value=-1;
	 }
	 startingAttributes[targetAttribute].selected=true;

/*****************************************************************
Run ID3 on trainingData, targetAttribute and startingAttributes
*****************************************************************/
	  //Create the root node and run ID3 using the training data
	  node treeNode=ID3(trainingData, targetAttribute, startingAttributes);

	  //Set the node depths
	  setDepth(&treeNode,0);
	  //Set the pointers to the node parents
	  setParents(&treeNode);
	  //Set the node IDs
	  setIDs(&treeNode,1);

/*****************************************************************
Print decision tree
*****************************************************************/
	  //Print tree info if toPrint is YES.
	  if(strcmp(toPrint,"Yes")==0||strcmp(toPrint,"yes")==0||strcmp(toPrint,"YES")==0||strcmp(toPrint,"Y")==0||strcmp(toPrint,"y")==0){
		  cout << "Decision Tree values:" << endl;
		  if(verbose==true){
			  cout << "nodeID) [entropy] {n} split : classification" << endl;
			  preorderPrintVerbose( &treeNode );
		  }else{
			  cout << "nodeID) splitAttrib = splitValue : classification" << endl;
			  preorderPrint( &treeNode );
		  }
	  }

/*********************************************************************
Calculate the accuracy of the decision tree against the validation data
*********************************************************************/
	  //Calculate the accuracy of the decision tree against the validation data
	  double accuracyBest=calcAccuracy(&treeNode,validationData);
	  cout << "\n\nAccuracy of unpruned tree against validation data is : " << accuracyBest << endl;

/*****************************************************************
Prune Tree
*****************************************************************/
	  //Make best tree = decision tree
	  node bestTree;
	  bestTree=treeNode;
	  copyTree(&treeNode,&bestTree);
	  //Set the node depths
	  setDepth(&bestTree,0);
	  //Set the pointers to the node parents
	  setParents(&bestTree);
	  //Set the node IDs
	  setIDs(&bestTree,1);

	  //Iterate L times (input arg) creating randomly pruned trees
	  for(int i=0;i<L;i++){
		  //Copy decision tree into primeTree
		  node* primeTree = new node;
		  *primeTree=treeNode;
		  copyTree(&treeNode,primeTree);
		  //Set the node depths
		  setDepth(primeTree,0);
		  //Set the pointers to the node parents
		  setParents(primeTree);
		  //Set the node IDs
		  setIDs(primeTree,1);

		  //M = a random number between 1 and K
		  //Generate a random number between 1 and K: */
		  int M = rand() % K + 1;

		  //Pruned M interior nodes
		  for(int j=0;j<M;j++){
			  //Create a list of ID's of interior nodes
			  vector<int>* nonLeafList = new vector<int>;
			  findNonLeafs(primeTree, nonLeafList);

			  //If there is only one interior node left, stop pruning
			  if(nonLeafList->size()<2){
				  break;
			  }

			  //Calculate number of interior nodes
			  int N=nonLeafList->size();

			  //Generate a random number between 1 and N
			  int P = rand() % N + 1;

			  /*
			  *Replace subtree rooted at P in primeTree by a leaf node
			  *Assign the majority class of the subset of the data at P to the leaf node
			  */
			  //Set ID of node to prune
			  int locationID=nonLeafList->at(P-1);

			  //Replace subtree rooted at selected ID with most common value
			  replaceSubtree(primeTree,locationID);
			  //Reset the node ID's
			  setIDs(primeTree,1);
		  }
		  //Evaluate the accuracy of the primeTree against the validation data
		  double accuracyPrime=calcAccuracy(primeTree,validationData);

		  //If primeTree is more accurate, copy it to bestTree
		  if(accuracyPrime>accuracyBest){
			  cout << "Found pruned tree with accuracy : " << accuracyPrime << endl;
			  bestTree=*primeTree;
			  copyTree(primeTree,&bestTree);
			  accuracyBest=accuracyPrime;
		  }
		  //Memory management
		  deleteTree(primeTree);
	  }

	  //Update best tree
	  //Set the node depths
	  setDepth(&bestTree,0);
	  //Set the pointers to the node parents
	  setParents(&bestTree);
	  //Set the node IDs
	  setIDs(&bestTree,1);

/*****************************************************************
Print best pruned tree
Uncomment to print
*****************************************************************/
	  /*
	  Print tree info if toPrint is YES.
	  if(strcmp(toPrint,"Yes")==0||strcmp(toPrint,"yes")==0||strcmp(toPrint,"YES")==0||strcmp(toPrint,"Y")==0||strcmp(toPrint,"y")==0){
	  	  cout << "Best Pruned Tree values:" << endl;
	  	  if(verbose==true){
	  	  	  cout << "nodeID) [entropy] {n} split : classification" << endl;
	  	  	  preorderPrintVerbose( &bestTree );
		  }else{
	  	  	  cout << "nodeID) splitAttrib = splitValue : classification" << endl;
	  	  	  preorderPrint( &bestTree);
	  	  }
	  }
	  */

/*****************************************************************
Calculate and print accuracies
*****************************************************************/
	  //Evaluate the accuracy of the bestTree against the test data
	  double accuracyFinal=calcAccuracy(&bestTree,testData);

	  //Calculate the accuracy of the decision tree against the test data
	  double accuracyUnpruned=calcAccuracy(&treeNode,testData);

	  //Print results
	  cout << "\n\nAccuracy of decision tree against test data is : " << accuracyUnpruned << endl;
	  cout << "Accuracy of best pruned tree against test data is : " << accuracyFinal << endl;
	  cout << "Number of nodes pruned = " << countNodes(&treeNode)-countNodes(&bestTree) << " out of " << countNodes(&treeNode) << endl << endl;

	  //Done
	  cout << "\nEnd Program." << endl;
	  return(0);
}
