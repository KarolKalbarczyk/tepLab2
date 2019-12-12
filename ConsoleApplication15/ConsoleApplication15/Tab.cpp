#include "pch.h"
#include "Tab.h"
#include <iostream>

Tab::Tab(const Tab &other)
{
	copy(other);
	std::cout << "Copy ";
}
Tab::~Tab()
{
	if (tab != NULL) {
		delete tab;
	}
	std::cout << "Destr ";
}
Tab Tab::operator=(const Tab &other)
{
	if (tab != NULL) delete tab;
	copy(other);
	std::cout << "op= ";
	return(*this);
}
void Tab::copy(const Tab &other)
{
	tab = new int[other.size];
	size = other.size;
	for (int ii = 0; ii < other.size; ii++)
		tab[ii] = other.tab[ii];
}

Tab::Tab(Tab &&other)
{
	this->tab = other.tab;
	this->size = other.size;
	other.tab = NULL;
	std::cout << "MOVE ";
}

Tab Tab::operator=(Tab &&other) {
	if (tab != NULL) delete tab;
	this->tab = other.tab;
	this->size = other.size;
	other.tab = NULL;
    std::cout << "MOVE=";
	return (*this);
}

void Tab::fillArray(int toAdd) {
	if (tab == NULL) return;
	for (size_t i = 0; i < size; i++)
	{
		tab[i] = i + toAdd;
	}
}

void Tab::printArray() {
	if (tab == NULL) return;
	for (size_t i = 0; i < size; i++)
	{
		std::cout << tab[i] << " ";
	}
}