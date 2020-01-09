#pragma once

#ifndef MSCN_PROBLEM_H
#define MSCN_PROBLEM_H
#include "Table.h"
#include"Random.h"
#include <vector>
#include <string>
#include "Enums.h"
const int NUMBER_OF_MATRICES = 12;
const int NUMBER_OF_TABLES = 8;

const int spaceCode = 32;
const int nCode = 10;
const int rCode = 13;
using namespace std;


const char SPACE = ' ';
const string NEW_LINE = "\r\n";
const vector<string> tabNames{ "UD","UF","UM","SD","SF","SM","SS","PS" };
const vector<string> matNames{ "XD","XF","XM" ,"CD","CF","CM","XDMIN","XDMAX","XFMIN","XFMAX" ,"XMMIN","XMMAX" };
const vector<string> objNames{ "D","F","M","S" };
const string READ_OPTION = "rb";
const string WRITE_OPTION = "w+";
const vector<int> order{ -(SD + 1),-(SF + 1),-(SM + 1),-(SS + 1),CD + 1,CF + 1,CM + 1,-(UD + 1),-(UF + 1),-(UM + 1),-(PS + 1),
				   XDMIN + 1, XDMAX + 1, XFMIN + 1, XFMAX + 1, XMMIN + 1, XMMAX + 1 ,XD + 1,XF + 1,XM + 1 };


const int RANDOM_CONSTRAINT_MATRIX = 25;
const int RANDOM_CONSTRAINT_MATRIX_MIN = 3;
const int RANDOM_CONSTRAINT_MATRIX_MAX = 10;
const int RANDOM_CONSTRAINT_TABLE = 100;
const enum MatrixToRandom {CMatrices,MIN,MAX};
class Format {
public:
	Format() { index = 0; };
	bool hasNext();
	bool isTableTurn();
	void reset();
	int next();
private:
	int index;
};


class Problem {
public:
	virtual int getProblemSize() = 0;
	virtual std::pair<double, double>* getConstraints() { return NULL; };
	virtual double getQuality(double *solution, int size, bool* success) = 0;
	virtual bool checkConstraints() = 0;
	virtual bool constaintSatisfied(double* solution, int size, bool *success) = 0;

private:
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

class MscnProblem : public Problem {
public:
	MscnProblem();
	bool changeSizeOF(Subjects object,int newSize);
	int getNumberOf(Subjects object);
	bool setAtMatrix(Matrices matrixNumber, double value,int indexX, int indexY );
	bool setAtTable(Tables tableNumber, double value,int index);
	pair<double, double> checkConstraintAt(Matrices matrix, int indexX, int indexY,bool* succes);
	double getQuality(double* solution,int size,bool* success);
	bool constaintSatisfied(double* solution, int size,bool *success);
	Matrix*** getMatrices() { return &matrices; };
	Table*** getTables() { return &tables; };
	double calcIncome();
	bool checkConstraints();
	int getProblemSize();
	std::pair<double, double>* getConstraints();
	~MscnProblem();
	void  generateInstance(int instanceSeed);
	void loadFromFile(string filePath, bool* success);
	bool saveToFile(string filePath);
private:
	Random rand;
	Table **tables;
	Matrix **matrices;
	pair<double, double> MscnProblem::doubleGetAt(Matrices minMatrix, Matrices maxMatrix, int indexX, int indexY,bool* success);
	double calcKU();
	double calcKT();
	double calcP();
	bool checkSingleConstraint(double(*sumFunction)(Matrix* matrix, int index), Matrices matrixNumber, Tables tableNumber, bool horizontal);
	bool checkConstraintMatrices(Matrices matrix1Num, Matrices matrix2Num);
	bool arrayToXMatrices(double *array,int size);
	bool changeSizeOF(Matrices matrix1, Matrices matrix2, int newSize);
	int epsilonFunc(double value);
	bool arrayToSingleXMatrix(double *array, int startIndex, Matrices matrixNumber);
	bool changeSizeOF(Matrices matrix1, Matrices matrix2, Tables table, int newSize);
	double sum(Matrices matrix1, Matrices matrix2);
	double sum(Matrices matrix, Tables table);
	void fillMatrix(Matrices matrixNumber,MatrixToRandom type);
	void fillTable(Tables tableNumber);

	FILE * file;
	Format format;
	bool linesToTables(vector<Tables> tables);
	bool linesToMatrices(vector<Matrices> matrices);
	bool lineToTable(Tables tableNumber, vector<double>* values);
	bool lineToMatrix(Matrices matrixNumber, vector<double>* values);
	bool setValuesFromFile();
	vector<int>* nextLine(bool *endOfFile);
	vector<string>* transformLineToStrings(vector<int>* line);
	vector<double>* stringsToDoubles(vector<string>* strings);
	vector<double>* lineToDoubles(bool *endOfFile);
	bool printQuantity(Subjects object, vector<string> objectNames);
	bool printMatrixToFile(Matrices matrixNumber);
	bool printTableToFile(Tables tableNumber);
	bool printMatricesToFile(vector<Matrices> mat, vector<string> names);
	bool printTablesToFile(vector<Tables> mat, vector<string> names);
	bool setValuesToFile();
};

#endif