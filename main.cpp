// HW4.cpp : Defines the entry point for the console application.
//


#include "DictionaryBST.h"
#include "Dictionary23Tree.h"

int main()
{
	DictionaryBST dictBST("dictionary.txt");
	dictBST.search("query.txt", "outputBST.txt");
	Dictionary23Tree dict23Tree("dictionary.txt");
	dict23Tree.search("query.txt", "output23Tree.txt");
}

