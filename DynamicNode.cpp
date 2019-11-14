#include "pch.h"
#include "DynamicTree.h"

void DynamicNode::addNewChild() {
	DynamicNode* node = new DynamicNode();
	children.push_back(node);
}

DynamicNode* DynamicNode::getChildOfNumber(int offset) {
	if (children.size() <= offset) {
		return children.at(offset);
	}
	return NULL;
}

void DynamicNode::printAllBelow() {
	cout << this->value;
	for (size_t i = 0; i < children.size(); i++)
	{
		(*children.at(i)).printAllBelow();
	}
}

void DynamicNode::printAllUp() {
	cout << this->value;
	if (parent != NULL) {
		(*parent).printAllUp();
	}
}

void DynamicTree::printTree() {
	this->root.printAllBelow();
}

