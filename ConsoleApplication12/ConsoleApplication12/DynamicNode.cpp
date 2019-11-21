#include "pch.h"
#include "DynamicNode.h"

void DynamicNode::addNewChild() {
	DynamicNode* node = new DynamicNode();
	node->parent = this;
	children.push_back(node);
}

DynamicNode* DynamicNode::getChildOfNumber(int offset) {
	if (children.size() > offset && offset>=0) {
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

bool DynamicNode::removeChild(DynamicNode* node){
	for (size_t i = 0; i < children.size(); i++)
	{
		if (children.at(i) == node) {
			children.erase(children.begin() + i); return true;
		}
	}
	return false;
}


bool  DynamicTree::moveSubTree(DynamicNode* parentNode, DynamicNode* subTree) {
	if (parentNode->getRoot() != (this->root)) return false;
	if (parentNode->getRoot() == subTree->getRoot()) return false;
	subTree->getParent()->removeChild(subTree);
	parentNode->addNewChild(subTree);
	return true;
}

void DynamicTree::printTree() {
	this->root->printAllBelow();
}

DynamicNode* DynamicNode::getRoot() {
	if (parent != NULL) {
		return (*parent).getRoot();
	}
	else  return this; 
}

DynamicNode::~DynamicNode() {
	for (size_t i = 0; i < children.size(); i++)
	{
		delete children.at(i);
	}
}

void DynamicNode::addNewChild(DynamicNode* node) {
	node->parent = this;
	children.push_back(node);
}

DynamicTree::DynamicTree() {
	DynamicNode* root = new DynamicNode();
	this->root = root;
}

DynamicTree::~DynamicTree(){
	delete root;
}

