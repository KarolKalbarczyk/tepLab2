// ConsoleApplication13.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "DynamicTree.h"

int main()
{
	DynamicTree<string>* tree = new DynamicTree<string>();
	tree->getRoot()->setValue("a");
	tree->getRoot()->addNewChild();
	tree->getRoot()->addNewChild();
	tree->getRoot()->getChildOfNumber(0)->setValue("b");
	tree->getRoot()->getChildOfNumber(1)->setValue("c");
	tree->getRoot()->getChildOfNumber(0)->addNewChild();
	tree->getRoot()->getChildOfNumber(0)->getChildOfNumber(0)->setValue("d");

	DynamicTree<string>* tree2 = new DynamicTree<string>();
	tree2->getRoot()->setValue("y");
	tree2->getRoot()->addNewChild();
	tree2->getRoot()->addNewChild();
	tree2->getRoot()->getChildOfNumber(0)->setValue("e");
	tree2->getRoot()->getChildOfNumber(1)->setValue("f");
	tree2->getRoot()->getChildOfNumber(0)->addNewChild();
	tree2->getRoot()->getChildOfNumber(0)->getChildOfNumber(0)->setValue("g");
	DynamicNode<string>* parent = tree->getRoot()->getChildOfNumber(0)->getChildOfNumber(0);
	DynamicNode<string>* subTree = tree2->getRoot()->getChildOfNumber(0);
	DynamicNode<string>* wrongSubTree = tree->getRoot()->getChildOfNumber(1);
	cout << tree->moveSubTree(subTree, parent);
	cout << tree->moveSubTree(parent, wrongSubTree);
	tree->printTree();
	cout << " ";
	tree2->printTree();
	cout << " ";
	tree->moveSubTree(parent, subTree);
	tree->printTree();
	cout << " ";
	tree2->printTree();
	delete tree2;
	cout << "up";
	tree->getRoot()->getChildOfNumber(0)->getChildOfNumber(0)->getChildOfNumber(0)->getChildOfNumber(0)->printAllUp();
	cout << " ";
	tree->printTree();
	delete tree;

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
