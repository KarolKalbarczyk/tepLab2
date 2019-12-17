#include "pch.h"
#include "table.h"
#include <iostream>
using namespace std;






Table::Table(string name, int arraySize) {
	this->name = name;
	this->array = new double[arraySize];
	this->arraySize = arraySize;
}

Table::Table(int name) {
	this->names = name;
	//Table(DEFAULT_NAME, DEFAULT_SIZE);
	this->name = DEFAULT_NAME;
	this->array = new double[DEFAULT_SIZE];
	this->arraySize = DEFAULT_SIZE;
}

Table::Table(Table &table) {
	this->name = table.name;
	this->array = copyArray(table.array, table.arraySize);
	this->arraySize = table.arraySize;
}

double* Table::copyArray(double* originalArray, int arraySize) {
	double *array;
	array = new double[arraySize];
	copyContents(&array, originalArray, arraySize);
	return array;
}


bool Table::setAt(double value, int index) {
	if (index < 0 || index >= arraySize) return false;
	array[index] = value;
	return true;
}


void Table::copyContents(double** array, double* arrayToCopy, int arraySize) {
	for (int i = 0; i < arraySize; i++)
	{
		*(*(array)+i) = arrayToCopy[i];
	}
}

bool Table::setNewArraySize(int newSize) {
	if (newSize == arraySize) return true;
	if (newSize <= 0) return false;
	double* newArray;
	newArray = new double[newSize];
	copyContents(&newArray, array, (this->arraySize) > newSize ? newSize : arraySize);
	delete[] array;
	array = newArray;
	this->arraySize = newSize;
	return true;
}

double Table::getAt(int index) {
	if (index < 0 || index >= arraySize) return -1;
	else return array[index];
}

void Table::printArray() {
	for (int i = 0; i < this->arraySize; i++)
	{
		cout << this->array[i] << " ";
	}
}

void Table::fillArray(int toAdd) {
	for (int i = 0; i < this->arraySize; i++)
	{
		this->array[i] = i + toAdd;
	}
}

Table* Table::clone() {
	Table* clone = new Table(*this);
	return clone;
}

double* Table::concat(double* otherArray, int otherArraySize) {
	int size = this->arraySize + otherArraySize;
	double* newArray = new double[size];
	for (size_t i = 0; i < this->arraySize; i++)
	{
		newArray[i] = (this->array)[i];
	}
	for (size_t i = this->arraySize; i < size; i++)
	{
		newArray[i] = (otherArray)[i - this->arraySize];
	}
	return newArray;
}

Table Table::operator+(Table &table) {
	int size = this->arraySize + table.arraySize;
	Table newTable(this->name + table.name, size);
	delete[] newTable.array;
	newTable.array = this->concat(table.array, table.arraySize);
	return newTable;
}

void Table::operator=(Table &table) {
	this->name = table.name;
	delete[] this->array;
	this->array = copyArray(table.array, table.arraySize);
	this->arraySize = table.arraySize;
}

int Table::getArraySize() { return this->arraySize; }

Table::~Table() {
	delete[] array;
}

