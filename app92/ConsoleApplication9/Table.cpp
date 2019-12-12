#include "pch.h"
#include "table.h"
#include <iostream>
using namespace std;






Table::Table(string name, int arraySize) {
	this->name = name;
	this->array = new int[arraySize];
	this->arraySize = arraySize;
	cout << "parametr: " << name << " ";
}

Table::Table() {
	//Table(DEFAULT_NAME, DEFAULT_SIZE);
	this->name = DEFAULT_NAME;
	this->array = new int[DEFAULT_SIZE];
	this->arraySize = DEFAULT_SIZE;
	cout << "bezp: " << this->name << " ";
}

Table::Table(Table &table) {
	this->name = table.name;
	this->array = copyArray(table.array, table.arraySize);
	this->arraySize = table.arraySize;
	cout << "kopiuj: " << this->name << " ";
}

Table::Table(Table &&table) {
	this->name = table.name;
	this->array = table.array;
	table.array = NULL;
	this->arraySize = table.arraySize;
	cout << "move";

}

int* Table::copyArray(int *originalArray, int arraySize) {
	int *array;
	array = new int[arraySize];
	copyContents(&array, originalArray, arraySize);
	return array;
}

void Table::copyContents(int** array, int* arrayToCopy, int arraySize) {
	for (int i = 0; i < arraySize; i++)
	{
		*(*(array)+i) = arrayToCopy[i];
	}
}

bool Table::setNewArraySize(int newSize) {
	if (newSize <= 0) return false;
	int* newArray;
	newArray = new int[newSize];
	copyContents(&newArray, array, (this->arraySize) > newSize ? newSize : arraySize);
	delete[] array;
	array = newArray;
	this->arraySize = newSize;
	return true;

}

void Table::printArray() {
	if (array == NULL) return;
	for (int i = 0; i < this->arraySize; i++)
	{
		cout << this->array[i] << " ";
	}
}

void Table::fillArray(int toAdd) {
	for (int i = 0; i < this->arraySize; i++)
	{
		this->array[i] = i+toAdd;
	}
}

Table* Table::clone() {
	Table* clone = new Table(*this);
	return clone;
}

int* Table::concat(int* otherArray, int otherArraySize) {
	int size = this->arraySize + otherArraySize;
	int* newArray = new int[size];
	for (size_t i = 0; i < this->arraySize; i++)
	{
		newArray[i] = (this->array)[i];
	}
	for (size_t i = this->arraySize; i < size; i++)
	{
		newArray[i] = (otherArray)[i-this->arraySize];
	}
	return newArray;
}

Table Table::operator+(Table &table) {
	int size = this->arraySize + table.arraySize;
	Table newTable(this->name + table.name, size);
	delete[] newTable.array;
	newTable.array = this->concat(table.array, table.arraySize);
	return std::move(newTable);
}

void Table::operator=(Table &table) {
	this->name = table.name;
	delete[] this->array;
	this->array = copyArray(table.array, table.arraySize);
	this->arraySize = table.arraySize;
}


void Table::operator=(Table &&table) {
	this->name = table.name;
	delete[] this->array;
	this->array = table.array;
	table.array = NULL;
	this->arraySize = table.arraySize;
}

int Table::getArraySize() { return this->arraySize; }

Table::~Table() {
	cout << "usuwam " << name << " ";
	if (array != NULL) delete[] array;
}

