// ConsoleApplication12.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "StaticNode.h"
#include "DynamicNode.h"

int main()
{
	/*StaticTree tree;
	tree.getRoot()->setValue(0);
	tree.getRoot()->addNewChild();
	tree.getRoot()->addNewChild();
	tree.getRoot()->getChildOfNumber(0)->setValue(1);
	tree.getRoot()->getChildOfNumber(1)->setValue(2);
	tree.getRoot()->getChildOfNumber(0)->addNewChild();
	tree.getRoot()->getChildOfNumber(0)->getChildOfNumber(0)->setValue(3);
	tree.getRoot()->printAllBelow();
	cout << tree.getRoot()->getNumberOfChildren();
	tree.getRoot()->getChildOfNumber(0)->getChildOfNumber(0)->printAllUp();
	tree.printTree();*/

	StaticTree* tree = new StaticTree();
	tree->getRoot()->setValue(0);
	tree->getRoot()->addNewChild();
	tree->getRoot()->addNewChild();
	tree->getRoot()->getChildOfNumber(0)->setValue(1);
	tree->getRoot()->getChildOfNumber(1)->setValue(2);
	tree->getRoot()->getChildOfNumber(0)->addNewChild();
	tree->getRoot()->getChildOfNumber(0)->getChildOfNumber(0)->setValue(3);

	StaticTree* tree2 = new StaticTree();
	tree2->getRoot()->setValue(6);
	tree2->getRoot()->addNewChild();
	tree2->getRoot()->addNewChild();
	tree2->getRoot()->getChildOfNumber(0)->setValue(7);
	tree2->getRoot()->getChildOfNumber(1)->setValue(8);
	tree2->getRoot()->getChildOfNumber(0)->addNewChild();
	tree2->getRoot()->getChildOfNumber(0)->getChildOfNumber(0)->setValue(9);
	StaticNode* parent = tree->getRoot()->getChildOfNumber(0)->getChildOfNumber(0);
	StaticNode* subTree = tree2->getRoot()->getChildOfNumber(0);
	StaticNode* wrongSubTree = tree->getRoot()->getChildOfNumber(1);
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

	/*DynamicTree* tree = new DynamicTree();
	tree->getRoot()->setValue(0);
	tree->getRoot()->addNewChild();
	tree->getRoot()->addNewChild();
	tree->getRoot()->getChildOfNumber(0)->setValue(1);
	tree->getRoot()->getChildOfNumber(1)->setValue(2);
	tree->getRoot()->getChildOfNumber(0)->addNewChild();
	tree->getRoot()->getChildOfNumber(0)->getChildOfNumber(0)->setValue(3);

	DynamicTree* tree2 = new DynamicTree();
	tree2->getRoot()->setValue(6);
	tree2->getRoot()->addNewChild();
	tree2->getRoot()->addNewChild();
	tree2->getRoot()->getChildOfNumber(0)->setValue(7);
	tree2->getRoot()->getChildOfNumber(1)->setValue(8);
	tree2->getRoot()->getChildOfNumber(0)->addNewChild();
	tree2->getRoot()->getChildOfNumber(0)->getChildOfNumber(0)->setValue(9);
	DynamicNode* parent = tree->getRoot()->getChildOfNumber(0)->getChildOfNumber(0);
	DynamicNode* subTree = tree2->getRoot()->getChildOfNumber(0);
	DynamicNode* wrongSubTree = tree->getRoot()->getChildOfNumber(1);
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
	delete tree;*/

	/*DynamicTree* tree = new DynamicTree;
	tree->getRoot()->setValue(0);
	tree->getRoot()->addNewChild();
	tree->getRoot()->addNewChild();
	tree->getRoot()->getChildOfNumber(0)->setValue(1);
	tree->getRoot()->getChildOfNumber(1)->setValue(2);
	tree->getRoot()->getChildOfNumber(0)->addNewChild();
	tree->getRoot()->getChildOfNumber(0)->getChildOfNumber(0)->setValue(3);
	tree->getRoot()->printAllBelow();
	cout << tree->getRoot()->getNumberOfChildren();
	tree->getRoot()->getChildOfNumber(0)->getChildOfNumber(0)->printAllUp();
	tree->printTree();
	delete tree;*/
	
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
