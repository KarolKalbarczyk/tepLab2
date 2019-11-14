#include "pch.h"
#include "StaticNode.h"

void StaticNode::addNewChild() {
	StaticNode node;
	children.push_back(node);
}

StaticNode* StaticNode::getChildOfNumber(int offset) {
	if (children.size() <= offset) {
		return &children.at(offset);
	}
	return NULL;
}

void StaticNode::printAllBelow() {
	cout << this->value;
	for (size_t i = 0; i < children.size(); i++)
	{
		children.at(i).printAllBelow();
	}
}

void StaticNode::printAllUp() {
	cout << this->value;
	if (parent != NULL) {
		(*parent).printAllUp();
	}
}

void StaticTree::printTree() {
	this->root.printAllBelow();
}

