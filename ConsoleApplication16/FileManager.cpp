

#include "pch.h"
#include "FileManager.h"
#include "MySmartPointer.h"
#include <vector>
#include <string>

using namespace std;
/*

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
	return abs((order.at(index++)))-1;
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

bool MscnProblem::lineToMatrix(Matrices matrixNumber, vector<double>* values, Matrix*** matrices) {
	Matrix* matrix = (*matrices)[matrixNumber];
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

bool MscnProblem::lineToTable(Tables tableNumber, vector<double>* values, Table*** tables) {
	Table* table = (*tables)[tableNumber];
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

bool MscnProblem::setValuesFromFile(MscnProblem* problem) {
	MySmartPointer<vector<double>> vec(NULL);
	vector<Subjects> obj{ Supplier,Fabric,Warehouse,Shop };
	bool endOfFile = false;
	for (size_t i = 0; i < obj.size(); i++)
	{
		vec = lineToDoubles(&endOfFile);
		if (endOfFile ||
		   !problem->changeSizeOF(obj.at(i), vec->at(0))) return false;
	}
	format.reset();
	while (format.hasNext()) {
		vec = lineToDoubles(&endOfFile);
		if (endOfFile) return false;
		if (format.isTableTurn()) {
			if (!lineToTable((Tables)format.next(), vec.getPointer(), problem->getTables()))return false;
		}
		else
			if(!lineToMatrix((Matrices)format.next(),vec.getPointer(), problem->getMatrices())) return false;
	}
	/*linesToTables(tab, problem);
	linesToMatrices(mat, problem);
	linesToTables(tab2, problem);
	linesToMatrices(mat2,problem);
	return true;
}

bool MscnProblem::linesToMatrices(vector<Matrices> matrices, MscnProblem* problem) {
	MySmartPointer<vector<double>> vec(NULL);
	bool endOfFile = false;
	for (size_t i = 0; i < matrices.size(); i++)
	{
		vec = lineToDoubles(&endOfFile);
		if (endOfFile || 
			!lineToMatrix(matrices.at(i), vec.getPointer(), problem->getMatrices())) return false;
	}
	return true;
}

bool MscnProblem::linesToTables(vector<Tables> tables, MscnProblem* problem) {
	MySmartPointer<vector<double>> vec(NULL);
	bool endOfFile = false;
	for (size_t i = 0; i < tables.size(); i++)
	{
		vec = lineToDoubles(&endOfFile);
		if (endOfFile||
			!lineToTable(tables.at(i), vec.getPointer(), problem->getTables())) return false;
	}
	return true;
}

MscnProblem* MscnProblem::loadFromFile(string filePath) {
	file = fopen(filePath.c_str(), READ_OPTION.c_str());
	MscnProblem* problem = new MscnProblem();
	if (file == NULL) return NULL;
	if (!setValuesFromFile(problem)) return false;
	fclose(file);
	return problem;
}

bool MscnProblem::saveToFile(string filePath, MscnProblem* problem) {
	file = fopen(filePath.c_str(), WRITE_OPTION.c_str());
	if (file == NULL) return false;
	if (!setValuesToFile(problem)) return false;
	fclose(file);
	return true;
}

bool MscnProblem::printQuantity(Subjects object,MscnProblem* problem, vector<string> objectNames){
	fprintf(file, (objectNames[object] + SPACE + std::to_string(problem->getNumberOf(object)) + NEW_LINE ).c_str());
	return true;
}

bool MscnProblem::printMatrixToFile(Matrices matrixNumber,Matrix*** matrices) {
	Matrix* matrix = (*matrices)[matrixNumber];
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

bool MscnProblem::printTableToFile(Tables tableNumber, Table*** tables) {
	Table* table = (*tables)[tableNumber];
	fprintf(file, (tabNames[tableNumber] + NEW_LINE).c_str());
	for (size_t i = 0; i < table->getArraySize(); i++)
	{
		fprintf(file, (std::to_string(table->getAt(i)) + " ").c_str());
	}
	fprintf(file, NEW_LINE.c_str());
	return true;
}

bool MscnProblem::setValuesToFile(MscnProblem* problem) {
	vector<Subjects> obj{ Supplier,Fabric,Warehouse,Shop };
	for (size_t i = 0; i < obj.size(); i++)
	{
		printQuantity(obj.at(i), problem, objNames);
	}
	format.reset();
	while (format.hasNext()) {
		if (format.isTableTurn()) printTableToFile((Tables)format.next(), problem->getTables());
		else printMatrixToFile((Matrices)format.next(), problem->getMatrices());
	}
	/*printTablesToFile(tab, problem, tabNames);
	printMatricesToFile(mat, problem, matNames);
	printTablesToFile(tab2, problem, tabNames);
	printMatricesToFile(mat2, problem, matNames);
	return true;
}

bool MscnProblem::printMatricesToFile(vector<Matrices> mat, MscnProblem* problem, vector<string> names){
	for (size_t i = 0; i < mat.size(); i++)
	{
		printMatrixToFile(mat.at(i), problem->getMatrices());
	}
	return true;
}
	

bool MscnProblem::printTablesToFile(vector<Tables> mat, MscnProblem* problem, vector<string> names){
	for (size_t i = 0; i < mat.size(); i++)
	{
		printTableToFile(mat.at(i), problem->getTables());
	}
	return true;
}*/