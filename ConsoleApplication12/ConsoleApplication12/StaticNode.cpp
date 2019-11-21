#include "pch.h"
#include "StaticNode.h"

void StaticNode::addNewChild() {
	StaticNode node;
	node.parent = this;
	children.push_back(node);
}

StaticNode::StaticNode(const StaticNode &node) {
	this->value = node.value;
	this->parent = node.parent;
	for (size_t i = 0; i < node.children.size(); i++)
	{
		StaticNode child(node.children.at(i));
		child.parent = this;
		this->children.push_back(child);
	}
}

StaticNode* StaticNode::getChildOfNumber(int offset) {
	if (children.size() > offset && offset >= 0) {
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

void StaticNode::addNewChild(StaticNode &node) {
	node.setParent(this);
	children.push_back(node);
}

StaticNode::~StaticNode() {}


bool StaticNode::removeChild(StaticNode* node) {
	for (int i = 0; i < children.size(); i++)
	{
		if ((&children.at(i)) == node) { 
			children.erase(children.begin()+i);
			return true; 
		}
	}
	return false;
}

StaticNode* StaticNode::getRoot() {
	if (parent != NULL) {
		return (*parent).getRoot();
	}
	else {
		return this;
	}
}


StaticTree::StaticTree() {
	StaticNode root;
	this->root = root;
}

StaticTree::~StaticTree() {

}

void StaticTree::printTree() {
	this->root.printAllBelow();
}

bool  StaticTree::moveSubTree(StaticNode* parentNode, StaticNode* subTree) {
	if (parentNode->getRoot() != (&this->root)) return false;
	if (parentNode->getRoot() == subTree->getRoot()) return false;
	StaticNode newTree(*subTree);
	parentNode->addNewChild(newTree);
	subTree->getParent()->removeChild(subTree);
	return true;
}