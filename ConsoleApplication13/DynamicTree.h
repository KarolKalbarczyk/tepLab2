#pragma once



#ifndef TREE_H
#define TR_H

#include <iostream>
#include <vector>
#include <string>
using namespace std;


template <typename T> class DynamicNode {
public:
	DynamicNode() { parent = NULL; }
	~DynamicNode();
	void setValue(T value) { this->value = value; }
	int getNumberOfChildren() { return children.size(); }
	void addNewChild();
	void addNewChild(DynamicNode<T> *node);
	DynamicNode<T>* getChildOfNumber(int offset);
	void  print() { cout << " " << value; };
	void printAllBelow();
	void printAllUp();
	DynamicNode<T>* getRoot();
	void setParent(DynamicNode<T> *parent) { this->parent = parent; }
	DynamicNode<T>* getParent() { return parent; }
	bool removeChild(DynamicNode<T>* node);
private:
	vector<DynamicNode<T>*> children;
	DynamicNode<T> *parent;
	T value;
};


template <typename T> class DynamicTree {
public:
	DynamicTree();
	~DynamicTree();
	DynamicNode<T>* getRoot() { return root; };
	void printTree();
	bool moveSubTree(DynamicNode<T>* parentNode, DynamicNode<T>* subTree);
private:
	DynamicNode<T>* root;
};

template <typename T>
void DynamicNode<T>::addNewChild() {
	DynamicNode<T>* node = new DynamicNode<T>();
	node->parent = this;
	children.push_back(node);
}
template <typename T>
DynamicNode<T>* DynamicNode<T>::getChildOfNumber(int offset) {
	if (children.size() > offset && offset >= 0) {
		return children.at(offset);
	}
	return NULL;
}

template <typename T>
void DynamicNode<T>::printAllBelow() {
	cout << this->value;
	for (size_t i = 0; i < children.size(); i++)
	{
		(*children.at(i)).printAllBelow();
	}
}

template <typename T>
void DynamicNode<T>::printAllUp() {
	cout << this->value;
	if (parent != NULL) {
		(*parent).printAllUp();
	}
}

template <typename T>
bool DynamicNode<T>::removeChild(DynamicNode<T>* node) {
	for (size_t i = 0; i < children.size(); i++)
	{
		if (children.at(i) == node) {
			children.erase(children.begin() + i); return true;
		}
	}
	return false;
}


template <typename T>
bool  DynamicTree<T>::moveSubTree(DynamicNode<T>* parentNode, DynamicNode<T>* subTree) {
	if (parentNode->getRoot() != (this->root)) return false;
	if (parentNode->getRoot() == subTree->getRoot()) return false;
	subTree->getParent()->removeChild(subTree);
	parentNode->addNewChild(subTree);
	return true;
}

template <typename T>
void DynamicTree<T>::printTree() {
	this->root->printAllBelow();
}

template <typename T>
DynamicNode<T>* DynamicNode<T>::getRoot() {
	if (parent != NULL) {
		return (*parent).getRoot();
	}
	else  return this;
}

template <typename T>
DynamicNode<T>::~DynamicNode() {
	for (size_t i = 0; i < children.size(); i++)
	{
		delete children.at(i);
	}
}

template <typename T>
void DynamicNode<T>::addNewChild(DynamicNode<T>* node) {
	node->parent = this;
	children.push_back(node);
}

template <typename T>
DynamicTree<T>::DynamicTree() {
	DynamicNode<T>* root = new DynamicNode<T>();
	this->root = root;
}

template <typename T>
DynamicTree<T>::~DynamicTree() {
	delete root;
};

#endif TREE_H