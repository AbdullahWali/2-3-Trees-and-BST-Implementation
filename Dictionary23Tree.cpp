//  Abdullah Wali - 21402793 - Section 3

#include "Dictionary23Tree.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;


void Tree23::Retrieve(string searchKey,
	int& numComparisons, bool& found) {
	retrieveItem(root, searchKey, numComparisons, found);
}

void Tree23::retrieveItem(TreeNode23 *treePtr, string searchKey,
	int& numComparisons, bool& found) {

	//Not Found
	if (treePtr == NULL) {
		found = false;
	}

	//Found
	else if (searchKey == treePtr->smallItem) {
		numComparisons++;
		return;
	}
	else if (searchKey == treePtr->largeItem) {
		numComparisons+=2;
		return;
	}

	//Searching

	//3 Node
	else if (treePtr->largeItem != "") {
		if (searchKey < treePtr->smallItem) {
			retrieveItem(treePtr->leftChildPtr, searchKey, numComparisons, found);
			numComparisons++;
		}
		else if (searchKey < treePtr->largeItem) {
			retrieveItem(treePtr->midChildPtr, searchKey, numComparisons, found);
			numComparisons+= 2;
		}
		else {
			retrieveItem(treePtr->rightChildPtr, searchKey, numComparisons, found);
			numComparisons+=2;
		}
	}

	//If it is a 2 Node
	else {
			if (searchKey < treePtr->smallItem) {
				retrieveItem(treePtr->leftChildPtr, searchKey, numComparisons, found);
				numComparisons++;
			}
			else {
				retrieveItem(treePtr->midChildPtr, searchKey, numComparisons, found);
				numComparisons++;
			}
	}
}



void Tree23::Insert(const TreeItemType& newItem) {
	insertItem(root, newItem);
}

void Tree23::insertItem(TreeNode23*& treePtr, const TreeItemType& item) {

	//root
	if (treePtr == NULL) {
		treePtr = new TreeNode23(item, "");
	}

	//Find Leaf:

	//Leaf Case:
	else if (treePtr->leftChildPtr == NULL) {

		//2 Node
		if (treePtr->largeItem == "") {
			//Set new item in correct position
			if (item < treePtr->smallItem) {
				treePtr->largeItem = treePtr->smallItem;
				treePtr->smallItem = item;
			}
			else treePtr->largeItem = item;
		}

		// 3 Node
		else {
			//Set the middle element in temp1 
			if (item < treePtr->smallItem) {
				treePtr->temp1 = treePtr->smallItem;
				treePtr->smallItem = item;
			}
			else if (item < treePtr->largeItem) {
				treePtr->temp1 = item;
			}
			else {
				treePtr->temp1 = treePtr->largeItem;
				treePtr->largeItem = item;
			}
			//Split the 3 Node
			split(treePtr);
			return;
		}
	}
	
	// If not Leaf:
	//If 3 node
	else if (treePtr->largeItem != "") {
		if (item < treePtr->smallItem) insertItem(treePtr->leftChildPtr, item);
		else if (item < treePtr->largeItem) insertItem(treePtr->midChildPtr, item);
		else insertItem(treePtr->rightChildPtr, item);
	}
	//2 Node
	else {
		if (item < treePtr->smallItem) insertItem(treePtr->leftChildPtr, item);
		else insertItem(treePtr->midChildPtr, item);
	}
}

void Tree23::split(TreeNode23 * &treePtr) {
	//Precondition: treePtr is a 3 node, and has 1-2 extra items in temp


		TreeNode23* toDelete = treePtr;//Preserve a reference to delete later
		
		bool newRoot = false; //Keep track if a new root was created
		TreeNode23* p = treePtr->parent;
		//if treePtr is root, 
		if (p == NULL) {
			p = new TreeNode23();
			newRoot = true;
		}

		//Replace node treePtr with two nodes, n1 and n2, so that p is their paremt
		TreeNode23* n1 = new TreeNode23(treePtr->smallItem, "");
		n1->parent = p;

		TreeNode23* n2 = new TreeNode23(treePtr->largeItem, "");
		n2->parent = p;


		//if treePtr was not a leaf: n1 becomes parent of Treeptr's two leftmost children and n2 becomes parent 
		// of the 2 rightmost children
		if (treePtr->leftChildPtr != NULL) {
			n1->leftChildPtr = treePtr->leftChildPtr;	treePtr->leftChildPtr->parent = n1;
			n1->midChildPtr = treePtr->midChildPtr;		treePtr->midChildPtr->parent = n1;
			n2->leftChildPtr = treePtr->rightChildPtr;	treePtr->rightChildPtr->parent = n2;
			n2->midChildPtr = treePtr->tempRightmost;	treePtr->tempRightmost->parent = n2;
		}

		//Move item from temp1 in treePtr to p

		//Case 0: if p is a new root
		if (newRoot) {
			p->smallItem = treePtr->temp1;
			p->leftChildPtr = n1;
			p->midChildPtr = n2;
		}

		//case 1: p is 2 Node: 
		else if (p->largeItem == "") {
			//If treePtr was left Child:
			if (p->leftChildPtr == treePtr) {
				p->largeItem = p->smallItem; //Shift Data to right
				p->rightChildPtr = p->midChildPtr; //Shift mid child to right

				//Insert the new elements
				p->smallItem = treePtr->temp1;
				p->leftChildPtr = n1;
				p->midChildPtr = n2;
			}
			else {
				//Insert the new elements at the right side of the tree if treePtr was a right child
				p->largeItem = treePtr->temp1;
				p->midChildPtr = n1;
				p->rightChildPtr = n2;
			}
		}

		//Case 2: ( aka hell): if p is 3 node
		//
		else {
			//In each case we must do the following, set temp1 to correct value and shift small/Large Item to correct position
			// order the children correctly
			//At the end: Split node

			//If treePtr was left Child:
			if (p->leftChildPtr == treePtr) {
				p->temp1 = p->smallItem; //The small item becomes the middle element
				p->smallItem = treePtr->temp1;

				//Shift children to left and set n1 and n2 as new children
				p->tempRightmost = p->rightChildPtr;
				p->rightChildPtr = p->midChildPtr;
				p->midChildPtr = n2;
				p->leftChildPtr = n1;
			}
			if (p->midChildPtr == treePtr) { //Case where treePtr was the middle child
				//Redistribute the Children
				p->temp1 = treePtr->temp1;
				p->tempRightmost = p->rightChildPtr;
				p->midChildPtr = n1;
				p->rightChildPtr = n2;
			}
			else { //Case where treePTr was right child
				p->temp1 = p->largeItem;
				p->largeItem = treePtr->temp1;
				//No need to shift
				p->rightChildPtr = n1;
				p->tempRightmost = n2;
			}
			//Split p:
			split(p);
		}
		//Free Memory
		delete toDelete;  //if (newRoot) 
 		if (newRoot) root = p; //Preserve the reference to root
}



// Uses postorder traversal for the destroy operation
// (Visits first the left and right children and then the node)
void Tree23::destroyTree(TreeNode23 *& treePtr) {

	if (treePtr != NULL) {
		destroyTree(treePtr->leftChildPtr);
		destroyTree(treePtr->midChildPtr);
		destroyTree(treePtr->rightChildPtr);
		delete treePtr;
		treePtr = NULL;
	}
}



Dictionary23Tree::Dictionary23Tree(string dictionaryFile)
{
	ifstream is;
	is.open(dictionaryFile.c_str());
	string input;
	while (is >> input) tree.Insert(input);
	is.close();
}

void Dictionary23Tree::insert(string word)
{
	tree.Insert(word);
}

void Dictionary23Tree::search(string word, int & numComparisons, bool & found)
{
	tree.Retrieve(word, numComparisons, found);
}

void Dictionary23Tree::search(string queryFile, string outputFile)
{
	int maxComparisons = 0;
	int totalComparisons = 0;
	int queryCount = 0;

	ofstream of;
	of.open(outputFile.c_str());
	ifstream is;
	is.open(queryFile.c_str());

	string query;
	while (is >> query) {
		int numComparisons = 0;
		bool found = true;
		search(query, numComparisons, found);
		of << query << "\t\t" << (found ? "1\t" : "0\t") << numComparisons << endl;

		//Collect Data
		queryCount++;
		totalComparisons += numComparisons;
		if (numComparisons > maxComparisons) maxComparisons = numComparisons;
	}

	of << "# of queries: " << queryCount << endl;
	of << "Maximum # of comparisons: " << maxComparisons << endl;
	of << "Average # of comparisons: " << ((double)totalComparisons) / queryCount << endl;

	of.close();
	is.close();

}
