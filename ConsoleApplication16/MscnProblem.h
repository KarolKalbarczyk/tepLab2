#pragma once

#ifndef MSCN_PROBLEM_H
#define MSCN_PROBLEM_H

#include "Table.h"
#include <vector>
#include <string>
#include "Enums.h"
const int NUMBER_OF_MATRICES = 12;
const int NUMBER_OF_TABLES = 8;

const int spaceCode = 32;
const int nCode = 10;
const int rCode = 13;
using namespace std;

template <typename T> class Response {
public:
	Response(T value,bool success) { 
		this->success = success;
		this->value = new T;
		*(this->value) = value;
	};
	Response(T* value, bool success) {
		this->success = success;
		this->value = value;
	};
	Response(Response &&other) {
		this->success = other.success;
		this->value = other.value;
		other.value = NULL;
	}
	T* getValue() { return value; };
	bool getSuccess() { return success; };
	~Response() { if(value!=NULL) delete value; };
private:
	T* value;
	bool success;
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
	int getSize() { return sizeX*sizeY; };
	bool outOfBounds(int indexX, int indexY);
private:
	int name;
	double **matrix;
	int sizeX;
	int sizeY;
	void deleteMatrix();
};

class MscnProblem {
public:
	MscnProblem();
	bool changeSizeOF(Subjects object,int newSize);
	int getNumberOf(Subjects object);
	bool setAtMatrix(Matrices matrixNumber, double value,int indexX, int indexY );
	bool setAtTable(Tables tableNumber, double value,int index);
	Response<pair<double, double>> checkConstraintAt(Matrices matrix, int indexX, int indexY);
	Response<double> getQuality(double* solution,int size);
	Response<bool> constaintSatisfied(double* solution, int size);
	Matrix*** getMatrices() { return &matrices; };
	Table*** getTables() { return &tables; };
	double calcIncome();
	bool checkConstraints();
	~MscnProblem();
private:
	Table **tables;
	Matrix **matrices;
	Response<pair<double, double>> MscnProblem::doubleGetAt(Matrices minMatrix, Matrices maxMatrix, int indexX, int indexY);
	double calcKU();
	double calcKT();
	double calcP();
	bool checkConstraint(double(*sumFunction)(Matrix* matrix, int index), Matrices matrixNumber, Tables tableNumber, bool horizontal);
	bool checkConstraintMatrices(Matrices matrix1Num, Matrices matrix2Num);
	bool arrayToXMatrices(double *array,int size);
	bool changeSizeOF(Matrices matrix1, Matrices matrix2, int newSize);
	int epsilonFunc(double value);
	bool arrayToSingleXMatrix(double *array, int startIndex, Matrices matrixNumber);
	bool changeSizeOF(Matrices matrix1, Matrices matrix2, Tables table, int newSize);
	double sum(Matrices matrix1, Matrices matrix2);
	double sum(Matrices matrix, Tables table);
	
};

#endif