//  Abdullah Wali - 21402793 - Section 3

#pragma once

#ifndef DICTIONARYBST
#define DICTIONARYBST
#include <string>
using namespace std;


typedef string TreeItemType;
class TreeNode { 	// a node in the tree
private:
	TreeNode() { }
	TreeNode(const TreeItemType& nodeItem, TreeNode *left = NULL,
		TreeNode *right = NULL)
		: item(nodeItem), leftChildPtr(left), rightChildPtr(right) { };


	TreeItemType item; 		// a data item in the tree
	TreeNode *leftChildPtr;	// pointers to children 
	TreeNode *rightChildPtr;


	// friend class - can access private parts
	friend class BinarySearchTree;
};

class BinarySearchTree {

public:
	BinarySearchTree() :root(NULL) {};
	~BinarySearchTree();

	bool isEmpty() const {	return root == NULL;};

	void Retrieve(string searchKey, int& numComparisons, bool& found);
	void Insert(const TreeItemType& newItem);

	
private:
	void retrieveItem(TreeNode *treePtr, string searchKey,
		 int& numComparisons, bool& found);
	void insertItem(TreeNode * &treePtr, const TreeItemType& item);
	void destroyTree(TreeNode *& treePtr);

	TreeNode * root;
};


//Binary search tree implementation for the dictionary
class DictionaryBST {
public:
	//Constructor that constructs the dictionary from the input file
	DictionaryBST(string dictionaryFile);
	//Destructor
	~DictionaryBST() {};
	//Inserts the given word into the dictionary
	void insert(string word);
	//Searches the given word in the dictionary, and returns the number
	//of comparisons made and whether the word is found or not
	void search(string word, int& numComparisons, bool& found);
	//Searches all words in the query file in the dictionary, and
	//summarizes the results in the output file
	void search(string queryFile, string outputFile);
private:
	BinarySearchTree tree;
};
#endif // !DICTIONARYBST
