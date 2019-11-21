#pragma once

#include <iostream>
#include <vector>
using namespace std;




class StaticNode {
public:
	StaticNode() { int value = 0; parent = NULL; }
	StaticNode(const StaticNode &node);
	~StaticNode();
	void setValue(int value) { this->value = value; }
	int getNumberOfChildren() { return children.size(); }
	void addNewChild();
	void addNewChild(StaticNode &node);
	StaticNode* getChildOfNumber(int offset);
	void  print() { cout << " " << value; };
	void printAllBelow();
	void printAllUp();
	StaticNode* getRoot();
	void setParent(StaticNode *parent) { this->parent = parent; }
	StaticNode* getParent() { return parent; }
	bool removeChild(StaticNode* node);
private:
	vector<StaticNode> children;
	StaticNode *parent;
	int value;
};

class StaticTree {
public:
	StaticTree();
	~StaticTree();
	StaticNode* getRoot() { return &root; };
	void printTree();
	bool moveSubTree(StaticNode* parentNode, StaticNode* subTree);
private:
	StaticNode root;
};