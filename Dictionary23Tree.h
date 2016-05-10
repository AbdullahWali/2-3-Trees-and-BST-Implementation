//  Abdullah Wali - 21402793 - Section 3


#pragma once
#ifndef DICTIONARY23
#define DICTIONARY23
using namespace std;
#include <string>

typedef string TreeItemType;
class TreeNode23{
private:
	TreeNode23():smallItem(""),largeItem(""), temp1(""), leftChildPtr(NULL), midChildPtr(NULL)
		, rightChildPtr(NULL), parent(NULL), tempRightmost(NULL) { };

	TreeNode23(const TreeItemType& small, const TreeItemType& large, TreeNode23 *left = NULL,
		TreeNode23 *right = NULL, TreeNode23 *mid = NULL)
		: smallItem(small), largeItem(large),  leftChildPtr(left), rightChildPtr(right), midChildPtr(mid), parent(NULL) ,temp1(""), tempRightmost(NULL) { };

	TreeItemType smallItem, largeItem, temp1;
	TreeNode23 *leftChildPtr, *midChildPtr, *rightChildPtr, *tempRightmost; //2-Node uses left and mid   //Temp Child is used for splitting
	TreeNode23* parent;

	// friend class-can access private class members
	friend class Tree23;
};


class Tree23 {
public:
	Tree23() : root(NULL) {}
	~Tree23() { destroyTree(root); };

	void Retrieve(string searchKey, int& numComparisons, bool& found);
	void Insert(const TreeItemType& newItem);

private:
	void retrieveItem(TreeNode23 *treePtr, string searchKey,
		int& numComparisons, bool& found);
	void insertItem(TreeNode23 * &treePtr, const TreeItemType& item);
	void split(TreeNode23 *& treePtr);
	void destroyTree(TreeNode23 *& treePtr);

	TreeNode23* root;
};


class Dictionary23Tree {
public:
	//Constructor that constructs the dictionary from the input file
	Dictionary23Tree(string dictionaryFile);
	//Destructor
	~Dictionary23Tree() {};
	//Inserts the given word into the dictionary
	void insert(string word);
	//Searches the given word in the dictionary, and returns the number
	//of comparisons made and whether the word is found or not
	void search(string word, int& numComparisons, bool& found);
	//Searches all words in the query file in the dictionary, and
	//summarizes the results in the output file
	void search(string queryFile, string outputFile);

private:
	Tree23 tree;
};


#endif // !DICTIONARY23
