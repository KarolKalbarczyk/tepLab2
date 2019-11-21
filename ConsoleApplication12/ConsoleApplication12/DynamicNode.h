#pragma once


#include <iostream>
#include <vector>
using namespace std;


class DynamicNode {
public:
	DynamicNode() { int value = 0; parent = NULL; }
	~DynamicNode();
	void setValue(int value) { this->value = value; }
	int getNumberOfChildren() { return children.size(); }
	void addNewChild();
	void addNewChild(DynamicNode *node);
	DynamicNode* getChildOfNumber(int offset);
	void  print() { cout << " " << value; };
	void printAllBelow();
	void printAllUp();
	DynamicNode* getRoot();
	void setParent(DynamicNode *parent) { this->parent = parent; }
	DynamicNode* getParent() { return parent; }
	bool removeChild(DynamicNode* node);
private:
	vector<DynamicNode*> children;
	DynamicNode *parent;
	int value;
};


class DynamicTree {
public:
	DynamicTree();
	~DynamicTree();
	DynamicNode* getRoot() { return root; };
	void printTree();
	bool moveSubTree(DynamicNode* parentNode, DynamicNode* subTree);
private:
	DynamicNode* root;
};