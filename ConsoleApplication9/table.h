#pragma once


#ifndef TABLE_H
#define TBE_H
#include <string>


const std::string DEFAULT_NAME = "name";
const int DEFAULT_SIZE = 5;

class Table {
public:
	Table(std::string name, int arraySize);
	Table();
	Table(Table &table);
	bool setNewArraySize(int newSize);
	Table* clone();
	void setName(std::string newName) { name = newName; }
	~Table();
	int getArraySize();
	void printArray();
	void fillArray(int toAdd);
	Table operator+(Table &table);
	void operator=(Table &table);

private:
	int* copyArray(int* arrayToCopy, int size);
	void copyContents(int** array,int* arrayToCopy, int size);
	std::string name;
	int* array;
	int arraySize;
	int* concat(int* array, int arraySize);
};

#endif