
#include "pch.h"
#include "MscnProblem.h"
#include <limits>
#include <vector>
#include "MySmartPointer.h"
#include "FileManager.h"
#include <string>

using namespace std;




double sumHorizontal(Matrix* matrix, int indexX) {
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

double MscnProblem::getQuality(double* solution,int size,bool* success) {
	if (!arrayToXMatrices(solution, size)) { success = false; return 0.0; }
	return calcIncome();
}

bool MscnProblem::constaintSatisfied(double* solution, int size,bool* success) {
	if (!arrayToXMatrices(solution, size)) { *success = false; return false; }
	return checkConstraints();
}

pair<double, double> MscnProblem::checkConstraintAt(Matrices matrixNumber, int indexX, int indexY,bool* success) {
	if (matrixNumber == XD) {
		return doubleGetAt(XDMIN, XDMAX,indexX,indexY,success);
	}if (matrixNumber == XF) {
		return doubleGetAt(XFMIN, XFMAX, indexX, indexY, success);
	}if (matrixNumber == XM) {
		return doubleGetAt(XMMIN, XMMAX, indexX, indexY, success);
	}
	if(success != NULL) *success = false;
	return pair<double, double>(0, 0);
}

pair<double, double> MscnProblem::doubleGetAt(Matrices minMatrix, Matrices maxMatrix, int indexX, int indexY,bool* success) {
	Matrix* matrix1 = matrices[minMatrix];
	Matrix* matrix2 = matrices[maxMatrix];
	if (!matrix1->outOfBounds(indexX, indexY) &&
		!matrix2->outOfBounds(indexX, indexY) ) {
		double min = matrix1->getAt(indexX, indexY);
		double max = matrix2->getAt(indexX, indexY);
		return pair<double, double>(min,max);
	}
	if (success != NULL) *success = false;
	return pair<double, double>(0, 0);
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

bool MscnProblem::checkConstraints() {
	return checkSingleConstraint(&sumHorizontal,XD, SD,true) 
		&& checkSingleConstraint(&sumHorizontal,XF, SF,true)
		&& checkSingleConstraint(&sumHorizontal,XM, SM,true) 
		&& checkSingleConstraint(&sumVertical,XM,SS,false)
		&& checkConstraintMatrices(XD, XF)
		&& checkConstraintMatrices(XF, XM);
}

bool MscnProblem::checkSingleConstraint(double (*sumFunction)(Matrix* matrix,int index),
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
			if (array[startIndex] < 0) return false;
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

void MscnProblem::generateInstance(int seed){
	rand.setSeed(seed);
	vector<Matrices> vec{ CD,CF,CM};
	vector<Matrices> vecMin{ XDMIN,XFMIN,XMMIN};
	vector<Matrices> vecMax{ XDMAX,XFMAX,XMMAX};
	vector<Tables> vec2{ UD,UF,UM,SD,SM,SF,SS,PS};
	for (size_t i = 0; i < vec.size(); i++)
	{
		fillMatrix(vec.at(i),CMatrices);
	}
	for (size_t i = 0; i < vec2.size(); i++)
	{
		fillTable(vec2.at(i));
	}
	for (size_t i = 0; i < vecMin.size(); i++)
	{
		fillMatrix(vecMin.at(i), MIN);
	}
	for (size_t i = 0; i < vecMax.size(); i++)
	{
		fillMatrix(vecMax.at(i), MAX);
	}
}

void MscnProblem::fillMatrix(Matrices matrixNumber,MatrixToRandom type) {
	Matrix* matrix = matrices[matrixNumber];
	for (size_t i = 0; i < matrix->getsizeX(); i++)
	{
		for (size_t j = 0; j < matrix->getsizeY(); j++)
		{
			if(type == MIN) matrix->setAt(rand.getDoubleInRange(0, RANDOM_CONSTRAINT_MATRIX_MIN), i, j);
			else if(type == MAX) matrix->setAt(rand.getDoubleInRange(RANDOM_CONSTRAINT_MATRIX_MIN,RANDOM_CONSTRAINT_MATRIX_MAX),i,j);
			else matrix->setAt(rand.getDoubleInRange(0, RANDOM_CONSTRAINT_MATRIX),i,j);
		}
	}
}

void MscnProblem::fillTable(Tables tableNumber) {
	Table* table = tables[tableNumber];
	for (size_t i = 0; i < table->getArraySize(); i++)
	{
		table->setAt(rand.getDoubleInRange(0,RANDOM_CONSTRAINT_TABLE), i);
	}
}

int MscnProblem::getProblemSize() {
	return matrices[XD]->getSize() + matrices[XF]->getSize()+matrices[XM]->getSize();
}

std::pair<double, double>* MscnProblem::getConstraints() {
	std::pair<double, double>* pairs = new pair<double, double>[getProblemSize()];
	int index = 0;
	vector<Matrices> vec{ XD,XF,XM };
	for (size_t i = 0; i < vec.size(); i++)
	{
		Matrix* matrix = matrices[vec.at(i)];
		for (size_t j = 0; j < matrix->getsizeX(); j++)
		{
			for (size_t k = 0; k < matrix->getsizeY(); k++)
			{
				pairs[index++] = checkConstraintAt(vec.at(i), j, k, NULL);
			}
		}
	}
	return pairs;
}




bool Format::hasNext() {
	return index < order.size();
}
bool Format::isTableTurn() {
	return order.at(index) < 0;
}
void Format::reset() {
	index = 0;
}
int Format::next() {
	return abs((order.at(index++))) - 1;
}

vector<int>* MscnProblem::nextLine(bool *endOfFile) {
	std::vector<int> *vec = new vector<int>();
	int chr = 0;
	while (chr != rCode && chr != EOF) {
		chr = fgetc(file);
		if (chr != rCode && chr != EOF) vec->push_back(chr);
	}
	if (chr == EOF && vec->size() == 0) {
		*endOfFile = true;
	}
	fgetc(file);
	return vec;
}

vector<string>* MscnProblem::transformLineToStrings(vector<int>* line) {
	std::vector<char> buffer;
	std::vector<string>* vec = new vector<string>;
	int chr = 0;
	for (size_t i = 0; i < line->size(); i++)
	{
		if (line->at(i) != spaceCode) {
			buffer.push_back((char)line->at(i));
		}
		else {
			vec->push_back(string(buffer.begin(), buffer.end()));
			buffer.clear();
		}
	}
	vec->push_back(string(buffer.begin(), buffer.end()));
	return vec;
}

vector<double>* MscnProblem::stringsToDoubles(vector<string>* strings) {
	std::vector<double>* vec = new vector<double>;
	for (size_t i = 0; i < strings->size(); i++)
	{
		try {
			double val = std::stod(strings->at(i));
			vec->push_back(val);
		}
		catch (const std::invalid_argument& ia) {}
	}
	return vec;
}

vector<double>* MscnProblem::lineToDoubles(bool *endOfFile) {
	vector<double>* doubles = nullptr;
	do {
		delete doubles;
		vector<int>* line = nextLine(endOfFile);
		vector<string>* strings = transformLineToStrings(line);
		doubles = stringsToDoubles(strings);
		delete line;
		delete strings;
		if (*endOfFile) return NULL;
	} while (doubles->size() == 0);
	return doubles;
}

bool MscnProblem::lineToMatrix(Matrices matrixNumber, vector<double>* values) {
	Matrix* matrix = matrices[matrixNumber];
	if (values->size() != matrix->getSize()) return false;
	for (size_t i = 0; i < matrix->getsizeX(); i++)
	{
		for (size_t j = 0; j < matrix->getsizeY(); j++)
		{
			double value = values->at(i*matrix->getsizeY() + j);
			if (value < 0) return false;
			bool check = matrix->setAt(values->at(i*matrix->getsizeY() + j), i, j);
			if (!check) return false;
		}
	}
	return true;
}

bool MscnProblem::lineToTable(Tables tableNumber, vector<double>* values) {
	Table* table = tables[tableNumber];
	if (values->size() != table->getArraySize()) return false;
	for (size_t j = 0; j < table->getArraySize(); j++)
	{
		double value = values->at(j);
		if (value <= 0) return false;
		bool check = table->setAt(value, j);
		if (!check) return false;
	}
	return true;
}

bool MscnProblem::setValuesFromFile() {
	MySmartPointer<vector<double>> vec(NULL);
	vector<Subjects> obj{ Supplier,Fabric,Warehouse,Shop };
	bool endOfFile = false;
	for (size_t i = 0; i < obj.size(); i++)
	{
		vec = lineToDoubles(&endOfFile);
		if (endOfFile ||
			!changeSizeOF(obj.at(i), vec->at(0))) return false;
	}
	format.reset();
	while (format.hasNext()) {
		vec = lineToDoubles(&endOfFile);
		if (endOfFile) return false;
		if (format.isTableTurn()) {
			if (!lineToTable((Tables)format.next(), vec.getPointer()))return false;
		}
		else
			if (!lineToMatrix((Matrices)format.next(), vec.getPointer())) return false;
	}
	return true;
}

bool MscnProblem::linesToMatrices(vector<Matrices> matrices) {
	MySmartPointer<vector<double>> vec(NULL);
	bool endOfFile = false;
	for (size_t i = 0; i < matrices.size(); i++)
	{
		vec = lineToDoubles(&endOfFile);
		if (endOfFile ||
			!lineToMatrix(matrices.at(i), vec.getPointer())) return false;
	}
	return true;
}

bool MscnProblem::linesToTables(vector<Tables> tables) {
	MySmartPointer<vector<double>> vec(NULL);
	bool endOfFile = false;
	for (size_t i = 0; i < tables.size(); i++)
	{
		vec = lineToDoubles(&endOfFile);
		if (endOfFile ||
			!lineToTable(tables.at(i), vec.getPointer())) return false;
	}
	return true;
}

void MscnProblem::loadFromFile(string filePath,bool* success) {
	file = fopen(filePath.c_str(), READ_OPTION.c_str());
	if (file == NULL) return;
	if (!setValuesFromFile()) {
		*success = false;
		return;
	}
	fclose(file);
}

bool MscnProblem::saveToFile(string filePath) {
	file = fopen(filePath.c_str(), WRITE_OPTION.c_str());
	if (file == NULL) return false;
	if (!setValuesToFile()) return false;
	fclose(file);
	return true;
}

bool MscnProblem::printQuantity(Subjects object, vector<string> objectNames) {
	fprintf(file, (objectNames[object] + SPACE + std::to_string(getNumberOf(object)) + NEW_LINE).c_str());
	return true;
}

bool MscnProblem::printMatrixToFile(Matrices matrixNumber) {
	Matrix* matrix = matrices[matrixNumber];
	fprintf(file, (matNames[matrixNumber] + NEW_LINE).c_str());
	for (size_t i = 0; i < matrix->getsizeX(); i++)
	{
		for (size_t j = 0; j < matrix->getsizeY(); j++)
		{
			fprintf(file, (std::to_string(matrix->getAt(i, j)) + SPACE).c_str());
		}
	}
	fprintf(file, NEW_LINE.c_str());
	return true;
}

bool MscnProblem::printTableToFile(Tables tableNumber) {
	Table* table = tables[tableNumber];
	fprintf(file, (tabNames[tableNumber] + NEW_LINE).c_str());
	for (size_t i = 0; i < table->getArraySize(); i++)
	{
		fprintf(file, (std::to_string(table->getAt(i)) + " ").c_str());
	}
	fprintf(file, NEW_LINE.c_str());
	return true;
}

bool MscnProblem::setValuesToFile() {
	vector<Subjects> obj{ Supplier,Fabric,Warehouse,Shop };
	for (size_t i = 0; i < obj.size(); i++)
	{
		printQuantity(obj.at(i), objNames);
	}
	format.reset();
	while (format.hasNext()) {
		if (format.isTableTurn()) printTableToFile((Tables)format.next());
		else printMatrixToFile((Matrices)format.next());
	}
	return true;
}

bool MscnProblem::printMatricesToFile(vector<Matrices> mat, vector<string> names) {
	for (size_t i = 0; i < mat.size(); i++)
	{
		printMatrixToFile(mat.at(i));
	}
	return true;
}


bool MscnProblem::printTablesToFile(vector<Tables> mat, vector<string> names) {
	for (size_t i = 0; i < mat.size(); i++)
	{
		printTableToFile(mat.at(i));
	}
	return true;
}