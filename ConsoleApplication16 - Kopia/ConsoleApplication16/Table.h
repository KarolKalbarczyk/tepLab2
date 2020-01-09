#pragma once


#ifndef TABLE_H
#define TBE_H
#include <string>


const std::string DEFAULT_NAME = "name";
const int DEFAULT_SIZE = 5;

class Table {
public:
	Table(std::string name, int arraySize);
	Table(int names);
	Table(Table &table);
	bool setNewArraySize(int newSize);
	Table* clone();
	bool setAt(double value, int index);
	~Table();
	int getArraySize();
	void printArray();
	void fillArray(int toAdd);
	Table operator+(Table &table);
	void operator=(Table &table);
	double getAt(int index);

private:
	int names;
	double* copyArray(double* arrayToCopy, int size);
	void copyContents(double** array, double* arrayToCopy, int size);
	std::string name;
	double* array;
	int arraySize;
	double* concat(double* array, int arraySize);
};

#endif