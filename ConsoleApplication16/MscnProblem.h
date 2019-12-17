#pragma once

#ifndef MSCN_PROBLEM_H
#define MSCN_PROBLEM_H

#include "Table.h"
#include <vector>
#include <string>
#include "Enums.h"
const int NUMBER_OF_MATRICES = 6;
const int NUMBER_OF_TABLES = 8;

const int spaceCode = 32;
const int nCode = 10;
const int rCode = 13;
using namespace std;

template <typename T> class Response {
public:
	Response(T value,bool success) { 
		this->succes = success;
		this->value = new T*;
		this->value* = value;
	};
	Response(T* value, bool success) {
		this->succes = success;
		this->value = value;
	};
	T* getValue() { return value; };
	bool getSuccess() { return success; };
	~Response() { delete value; };
private:
	T* value;
	bool succes;
};

class Matrix {
public:
	Matrix(int name);
	bool setMatrix(double*** matrix, int sizeX, int sizeY);
	~Matrix();
	double getAt(int indexX, int indexY, bool* success = NULL);
	int getsizeX() { return sizeX; };
	int getsizeY() { return sizeY; };
	bool setAt(double value, int indexX, int indexY);
	bool changeSize(int sizeX, int sizeY);
	int getSize() { return sizeX * sizeY; };
	bool outOfBounds(int indexX, int indexY);
private:
	int name;
	double ***matrix;
	int sizeX;
	int sizeY;
	void deleteMatrix();
};

class MscnProblem {
public:
	MscnProblem();
	bool changeSizeOF(Objects object,int newSize);
	int getNumberOf(Objects object);
	bool setAtMatrix(Matrices matrixNumber, double value,int indexX, int indexY );
	bool setAtTable(Tables tableNumber, double value,int index);
	Response<pair<double, double>>* checkConstraintAt(Matrices matrix, int indexX, int indexY);
	Response<double>* getQuality(double* solution,int size);
	Response<bool>* constaintSatisfied(double* solution, int size);
	Matrix*** getMatrices() { return &matrices; };
	Table*** getTables() { return &tables; };
private:
	Table **tables;
	Matrix **matrices;
	double calcKU();
	double calcKT();
	double calcP();
	double calcIncome();
	bool checkConstraints();
	bool checkConstraint(double(*sumFunction)(Matrix* matrix, int index), Matrices matrixNumber, Tables tableNumber, bool horizontal);
	bool checkConstraintMatrices(Matrices matrix1Num, Matrices matrix2Num);
	bool arrayToXMatrices(double *array,int size);
	int epsilonFunc(double value);
	bool arrayToSingleXMatrix(double *array, int startIndex, Matrices matrixNumber);
	bool changeSizeOF(Matrices matrix1, Matrices matrix2, Tables table, int newSize);
	double sum(Matrices matrix1, Matrices matrix2);
	double sum(Matrices matrix, Tables table);
	
};

#endif