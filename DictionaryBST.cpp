//  Abdullah Wali - 21402793 - Section 3

#include "DictionaryBST.h"

#include <iostream>
#include <fstream>
#include <string>

void BinarySearchTree::Retrieve(string searchKey,
	 int& numComparisons, bool& found)  {
	retrieveItem(root, searchKey, numComparisons, found);
}

void BinarySearchTree::retrieveItem(TreeNode *treePtr, string searchKey,
	 int& numComparisons, bool& found)  {

	if (treePtr == NULL) {
		found = false;
	}
	else if (searchKey == treePtr->item){
		numComparisons++;
		return;
		}
	else if (searchKey < treePtr->item) {
		retrieveItem(treePtr->leftChildPtr, searchKey,  numComparisons, found);
		numComparisons++;
	}
	else {
		retrieveItem(treePtr->rightChildPtr, searchKey, numComparisons, found);
		numComparisons++;
	}
}

// Destructor
BinarySearchTree::~BinarySearchTree() {
	destroyTree(root);
}


// Uses postorder traversal for the destroy operation
// (Visits first the left and right children and then the node)
void BinarySearchTree::destroyTree(TreeNode *& treePtr) {

	if (treePtr != NULL) {
		destroyTree(treePtr->leftChildPtr);
		destroyTree(treePtr->rightChildPtr);
		delete treePtr;
		treePtr = NULL;
	}
}

void BinarySearchTree::Insert(const TreeItemType& newItem) {
	insertItem(root, newItem);
}


void BinarySearchTree::insertItem(TreeNode *& treePtr,
	const TreeItemType& newItem) {

	// Position of insertion found; insert after leaf
	if (treePtr == NULL) {
		treePtr = new TreeNode(newItem, NULL, NULL);
	}
	// Else search for the insertion position
		else if (newItem < treePtr->item)
		insertItem(treePtr->leftChildPtr, newItem);
	else
		insertItem(treePtr->rightChildPtr, newItem);
}

DictionaryBST::DictionaryBST(string dictionaryFile)
{
	ifstream is;
	is.open(dictionaryFile.c_str());
	string input;
	while (is >> input) tree.Insert(input);
	is.close();
}

void DictionaryBST::insert(string word)
{
	tree.Insert(word);
}

void DictionaryBST::search(string word, int & numComparisons, bool & found)
{
	tree.Retrieve(word, numComparisons, found);
}

void DictionaryBST::search(string queryFile, string outputFile)
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
		of << query<< "\t\t" << (found? "1\t" : "0\t") << numComparisons << endl;

		//Collect Data
		queryCount++;
		totalComparisons += numComparisons;
		if (numComparisons > maxComparisons) maxComparisons = numComparisons;
	}

	of << "# of queries: " << queryCount<< endl;
	of << "Maximum # of comparisons: " << maxComparisons << endl;
	of << "Average # of comparisons: " << ((double)totalComparisons) / queryCount << endl;

	of.close();
	is.close();

}
