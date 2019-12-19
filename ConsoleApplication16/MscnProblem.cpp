
#include "pch.h"
#include "MscnProblem.h"
#include <limits>
#include <vector>
#include "MySmartPointer.h"
#include "FileManager.h"
#include <string>

using namespace std;

Matrix::~Matrix() {
	deleteMatrix();
}

Matrix::Matrix(int name) {
	this->name = name;
	sizeX = 0;
	sizeY = 0;
}

double Matrix::getAt(int indexX, int indexY,bool* success) {
	if (outOfBounds(indexX, indexY)) {
		if (success != NULL) *success = false;
		return 0;
	}
	return matrix[indexX][indexY];
}

bool Matrix::outOfBounds(int indexX, int indexY) {
	if (indexX >= sizeX || indexX < 0) return true;
	if (indexY >= sizeY || indexY < 0) return true;
	return false;
}

void Matrix::deleteMatrix() {
	for (size_t i = 0; i < sizeX; i++)
	{
		delete[] matrix[i];
	}
    if((matrix) !=NULL)	delete[] matrix;
}

bool Matrix::setMatrix(double ***matrix, int sizeX, int sizeY) {
	if (sizeX < 0 || sizeY < 0) return false;
	if (sizeX == 0) sizeX = 1;
	if (sizeY == 0) sizeY = 1;
	deleteMatrix();
	this->matrix = (*matrix);
	this->sizeX = sizeX;
	this->sizeY = sizeY;
	return true;
}

bool Matrix::changeSize(int sizeX, int sizeY) {
	if (sizeX < 0 || sizeY < 0) return false;
	if (sizeX == 0) sizeX = 1;
	if (sizeY == 0) sizeY = 1;
	double ** newArray= new double*[sizeX];
	for (size_t i = 0; i < sizeX; i++)
	{
		newArray[i] = new double[sizeY];
	}
	return setMatrix(&newArray, sizeX, sizeY);
}

bool Matrix::setAt(double value, int indexX, int indexY) {
	if (outOfBounds(indexX,indexY) || value < 0) return false;
	matrix[indexX][indexY] = value;
	return true;
}



int MscnProblem::getNumberOf(Subjects object) {
	if (object == Shop) {
		return tables[SS]->getArraySize();
	}
	if (object == Warehouse) {
		return tables[SM]->getArraySize();
	}
	if (object == Fabric) {
		return tables[SF]->getArraySize();
	}
	if (object == Supplier) {
		return tables[SD]->getArraySize();
	}
	return -1;
}

bool MscnProblem::changeSizeOF(Subjects object, int newSize) {
	if (newSize <= 0) return false;
	if (object == Shop) {
		matrices[CM]->changeSize(matrices[CM]->getsizeX(), newSize);
		matrices[XM]->changeSize(matrices[XM]->getsizeX(), newSize);
		matrices[XMMIN]->changeSize(matrices[XM]->getsizeX(), newSize);
		matrices[XMMAX]->changeSize(matrices[XM]->getsizeX(), newSize);
		tables[SS]->setNewArraySize(newSize);
		tables[PS]->setNewArraySize(newSize);
	}
	if (object == Warehouse) {
		return changeSizeOF(CF, CM, SM,newSize) &&
		  changeSizeOF(XF, XM, UM,newSize) &&
		  changeSizeOF(XFMIN,XMMIN,newSize) &&
		  changeSizeOF(XFMAX, XMMAX, newSize);
	}
	if (object == Fabric) {
		return changeSizeOF(CD, CF, SF, newSize) &&
		  changeSizeOF(XD, XF, UF, newSize) &&
		  changeSizeOF(XDMIN, XFMIN, newSize) &&
		  changeSizeOF(XDMAX, XFMAX, newSize);
	}
	if (object == Supplier) {
		matrices[CD]->changeSize(newSize, matrices[CD]->getsizeY());
		matrices[XD]->changeSize(newSize, matrices[XD]->getsizeY());
		matrices[XDMIN]->changeSize(newSize, matrices[XD]->getsizeY());
		matrices[XDMAX]->changeSize(newSize, matrices[XD]->getsizeY());
		tables[SD]->setNewArraySize(newSize);
		tables[UD]->setNewArraySize(newSize);
	}
	return true;
}

double MscnProblem::calcKT() {
	return sum(CD, XD) + sum(CF, XF) + sum(CM, XM);
}

bool MscnProblem::changeSizeOF(Matrices matrix1, Matrices matrix2, Tables table, int newSize) {
	return matrices[matrix1]->changeSize(matrices[matrix1]->getsizeX(), newSize) &&
	  matrices[matrix2]->changeSize(newSize, matrices[matrix2]->getsizeY()) &&
	  tables[table]->setNewArraySize(newSize);
}

bool MscnProblem::changeSizeOF(Matrices matrix1, Matrices matrix2, int newSize) {
	return matrices[matrix1]->changeSize(matrices[matrix1]->getsizeX(), newSize) &&
		matrices[matrix2]->changeSize(newSize, matrices[matrix2]->getsizeY());
}

bool MscnProblem::setAtMatrix(Matrices matrixNumber, double value, int indexX, int indexY) {
	if (matrixNumber < 0 || matrixNumber >= NUMBER_OF_MATRICES) return false;
	if (value < 0) return false;
	return matrices[matrixNumber]->setAt(value, indexX, indexY);
}

bool MscnProblem::setAtTable(Tables tableNumber, double value, int index) {
	if (tableNumber < 0 || tableNumber>= NUMBER_OF_TABLES) return false;
	if (value < 0) return false;
	return tables[tableNumber]->setAt(value, index);
}

MscnProblem::MscnProblem() {
	matrices = new Matrix*[NUMBER_OF_MATRICES];
	for (size_t i = 0; i < NUMBER_OF_MATRICES; i++)
	{
		matrices[i] = new Matrix(i);
	}
	tables = new Table*[NUMBER_OF_TABLES];
	for (size_t i = 0; i < NUMBER_OF_TABLES; i++)
	{
		tables[i] = new Table(i);
	}
}

double MscnProblem::sum(Matrices matrix1Index, Matrices matrix2Index) {
	Matrix* matrix1 = matrices[matrix1Index];
	Matrix* matrix2 = matrices[matrix2Index];
	if (matrix1->getsizeX() != matrix2->getsizeX()
		|| matrix1->getsizeY() != matrix2->getsizeY()) return 0;
	double sum = 0;
	for (size_t i = 0; i < matrix1->getsizeX(); i++)
	{
		for (size_t j = 0; j < matrix1->getsizeY(); j++)
		{
			sum += matrix1->getAt(i, j)*matrix2->getAt(i, j);
		}
	}
	return sum;
}

double MscnProblem::sum(Matrices matrixIndex, Tables tableIndex) {
	Matrix* matrix = matrices[matrixIndex];
	Table* table = tables[tableIndex];
	if (matrix->getsizeX() != table->getArraySize()) return 0;
	double sum = 0;
	for (size_t i = 0; i < matrix->getsizeX(); i++)
	{
		double matrixSum = 0;
		for (size_t j = 0; j < matrix->getsizeY(); j++)
		{
			matrixSum += matrix->getAt(i, j);
		}
		sum += table->getAt(i)*epsilonFunc(matrixSum);
	}
	return sum;
}

double MscnProblem::calcKU() {
	return sum(XD, UD) + sum(XF, UF) + sum(XM, UM);
}

Response<double> MscnProblem::getQuality(double* solution,int size) {
	if (!arrayToXMatrices(solution, size)) return std::move(Response<double>(0.0, false));
	else return std::move(Response<double>(calcIncome(),true));
}

Response<bool> MscnProblem::constaintSatisfied(double* solution, int size) {
	if (!arrayToXMatrices(solution, size)) return std::move(Response<bool>(false, false));
	else return std::move(Response<bool>(checkConstraints(), true));
}

Response<pair<double, double>> MscnProblem::checkConstraintAt(Matrices matrixNumber, int indexX, int indexY) {
	if (matrixNumber == XD) {
		return std::move(doubleGetAt(XDMIN, XDMAX,indexX,indexY));
	}if (matrixNumber == XF) {
		return std::move(doubleGetAt(XFMIN, XFMAX, indexX, indexY));
	}if (matrixNumber == XM) {
		return std::move(doubleGetAt(XMMIN, XMMAX, indexX, indexY));
	}
	return std::move( Response< pair<double, double>>(pair<double, double>(0, 0), false));
}

Response<pair<double, double>> MscnProblem::doubleGetAt(Matrices minMatrix, Matrices maxMatrix, int indexX, int indexY) {
	Matrix* matrix1 = matrices[minMatrix];
	Matrix* matrix2 = matrices[maxMatrix];
	if (!matrix1->outOfBounds(indexX, indexY) &&
		!matrix2->outOfBounds(indexX, indexY) ) {
		double min = matrix1->getAt(indexX, indexY);
		double max = matrix1->getAt(indexX, indexY);
		return std::move(Response< pair<double, double>>(pair<double, double>(min,max), true));
	}
	else return std::move(Response< pair<double, double>>(pair<double, double>(0, 0), false));
}

double MscnProblem::calcP() {
	double sum = 0;
	Matrix* matrix = matrices[XM];
	Table* table = tables[PS];
	if (matrix->getsizeY() != table->getArraySize()) return 0;
	for (size_t i = 0; i < matrix->getsizeX(); i++)
	{
		for (size_t j = 0; j < matrix->getsizeY(); j++)
		{
			sum += matrix->getAt(i, j)*table->getAt(j);
		}
	}
	return sum;
}

double MscnProblem::calcIncome() {
	return calcP() - calcKT() - calcKU();
}

double sumHorizontal(Matrix* matrix, int indexX){
	double sum = 0;
	for (size_t j = 0; j < matrix->getsizeY(); j++)
	{
		sum += matrix->getAt(indexX, j);
	}
	return sum;
}

double sumVertical(Matrix* matrix, int indexY) {
	double sum = 0;
	for (size_t j = 0; j < matrix->getsizeX(); j++)
	{
		sum += matrix->getAt(j, indexY);
	}
	return sum;
}

bool MscnProblem::checkConstraints() {
	return checkConstraint(&sumHorizontal,XD, SD,true) 
		&& checkConstraint(&sumHorizontal,XF, SF,true)
		&& checkConstraint(&sumHorizontal,XM, SM,true) 
		&& checkConstraint(&sumVertical,XM,SS,false)
		&& checkConstraintMatrices(XD, XF)
		&& checkConstraintMatrices(XF, XM);
}

bool MscnProblem::checkConstraint(double (*sumFunction)(Matrix* matrix,int index),
	Matrices matrixNumber, Tables tableNumber, bool horizontal) {
	bool check = true;
	Matrix* matrix = matrices[matrixNumber];
	Table* table = tables[tableNumber];
	int size = horizontal ? matrix->getsizeX() : matrix->getsizeY();
	for (size_t i = 0; i < size; i++)
	{
		check = check && (sumFunction(matrix,i) <= table->getAt(i));
	}
	return check;
}


bool MscnProblem::checkConstraintMatrices(Matrices matrix1Num, Matrices matrix2Num) {
	bool check = true;
	Matrix* matrix1 = matrices[matrix1Num];
	Matrix* matrix2 = matrices[matrix2Num];
	for (size_t i = 0; i < matrix1->getsizeX(); i++)
	{
		check = check && (sumVertical(matrix1, i) <= sumHorizontal(matrix2,i));
	}
	return check;
}

bool MscnProblem::arrayToXMatrices(double *array, int size) {
	if (array == NULL) return false;
	if (size != matrices[XD]->getSize() + matrices[XF]->getSize() + matrices[XM]->getSize()) return false;
	return arrayToSingleXMatrix(array, 0, XD) &&
		arrayToSingleXMatrix(array, matrices[XD]->getSize(), XF) &&
		arrayToSingleXMatrix(array, matrices[XD]->getSize() + matrices[XF]->getSize(), XM);
}

bool MscnProblem::arrayToSingleXMatrix(double *array,int startIndex,Matrices matrixNumber) {
	Matrix* matrix = matrices[matrixNumber];
	bool check = true;
	for (size_t i = 0; i < matrix->getsizeX(); i++)
	{
		for (size_t j = 0; j < matrix->getsizeY(); j++)
		{
			if (array[startIndex] <= 0) return false;
			check = check && matrix->setAt(array[startIndex++], i, j);
		}
	}
	return check;
}

int MscnProblem::epsilonFunc(double value) {
	if (value > 0) return 1;
	else return 0;
}

MscnProblem::~MscnProblem() {
	for (size_t i = 0; i < NUMBER_OF_MATRICES; i++)
	{
		delete matrices[i];
	}
	for (size_t i = 0; i < NUMBER_OF_TABLES; i++)
	{
		delete tables[i];
	}
	delete[] matrices;
	delete[] tables;
}
