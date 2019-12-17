

#include "pch.h"
//#include "MscnProblem.h"
#include "FileManager.h"
#include "MySmartPointer.h"
#include <vector>
#include <string>

using namespace std;

vector<int>* FileManager::nextLine() {
	std::vector<int> *vec = new vector<int>();
	int chr = 0;
	while (chr != rCode && chr != -1) {
		chr = fgetc(file);
		if (chr != rCode) vec->push_back(chr);
	}
	fgetc(file);
	return vec;
}

vector<string>* FileManager::transformLineToStrings(vector<int>* line) {
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

vector<double>* FileManager::stringsToDoubles(vector<string>* strings) {
	std::vector<double>* vec = new vector<double>;
	for (size_t i = 0; i < strings->size(); i++)
	{
		try {
			double val = std::stod(strings->at(i));
			vec->push_back(val);
		}
		catch (const std::invalid_argument& ia) {
		}
	}
	return vec;
}

vector<double>* FileManager::lineToDoubles() {
	vector<double>* doubles = nullptr;
	do {
		delete doubles;
		vector<int>* line = nextLine();
		vector<string>* strings = transformLineToStrings(line);
		doubles = stringsToDoubles(strings);
		delete line;
		delete strings;
	} while (doubles->size() == 0);
	return doubles;
}

bool FileManager::lineToMatrix(Matrices matrixNumber, vector<double>* values, Matrix*** matrices) {
	Matrix* matrix = (*matrices)[matrixNumber];
	if (values->size() != matrix->getSize()) return false;
	for (size_t i = 0; i < matrix->getsizeX(); i++)
	{
		for (size_t j = 0; j < matrix->getsizeY(); j++)
		{
			bool check = matrix->setAt(values->at(i*matrix->getsizeY() + j), i, j);
			if (!check) return false;
		}
	}
	return true;
}

bool FileManager::lineToTable(Tables tableNumber, vector<double>* values, Table*** tables) {
	Table* table = (*tables)[tableNumber];
	if (values->size() != table->getArraySize()) return false;
	for (size_t j = 0; j < table->getArraySize(); j++)
	{
		bool check = table->setAt(values->at(j), j);
		if (!check) return false;
	}
	return true;
}

bool FileManager::setValuesFromFile(MscnProblem* problem) {
	MySmartPointer<vector<double>> vec(NULL);
	vector<Objects> obj{ Supplier,Fabric,Warehouse,Shop };
	for (size_t i = 0; i < obj.size(); i++)
	{
		vec = lineToDoubles();
		if (!problem->changeSizeOF(obj.at(i), vec->at(0))) return false;
	}
	vector<Tables> tab{ SD,SF,SM,SS };
	linesToTables(tab, problem);
	vector<Matrices> mat{ CD,CF,CM };
	linesToMatrices(mat, problem);
	vector<Tables> tab2{ UD,UF,UM,PS };
	linesToTables(tab2, problem);
	vector<Matrices> mat2{ XD,XF,XM };
	linesToMatrices(mat2,problem);
	return true;
}

bool FileManager::linesToMatrices(vector<Matrices> matrices, MscnProblem* problem) {
	MySmartPointer<vector<double>> vec(NULL);
	for (size_t i = 0; i < matrices.size(); i++)
	{
		vec = lineToDoubles();
		if (!lineToMatrix(matrices.at(i), vec.getPointer(), problem->getMatrices())) return false;
	}
	return true;
}

bool FileManager::linesToTables(vector<Tables> tables, MscnProblem* problem) {
	MySmartPointer<vector<double>> vec(NULL);
	for (size_t i = 0; i < tables.size(); i++)
	{
		vec = lineToDoubles();
		if (!lineToTable(tables.at(i), vec.getPointer(), problem->getTables())) return false;
	}
	return true;
}

MscnProblem* FileManager::loadFromFile(string filePath) {
	file = fopen(filePath.c_str(), READ_OPTION.c_str());
	MscnProblem* problem = new MscnProblem();
	if (file == NULL) return NULL;
	if (!setValuesFromFile(problem)) return false;
	fclose(file);
	return problem;
}

bool FileManager::saveToFile(string filePath, MscnProblem* problem) {
	file = fopen(filePath.c_str(), WRITE_OPTION.c_str());
	if (file == NULL) return false;
	if (!setValuesToFile(problem)) return false;
	fclose(file);
	return true;
}

bool FileManager::printQuantity(Objects object,MscnProblem* problem, vector<string> objectNames){
	fprintf(file, (objectNames[object] + SPACE + std::to_string(problem->getNumberOf(object)) + NEW_LINE ).c_str());
	return true;
}

bool FileManager::printMatrixToFile(Matrices matrixNumber,Matrix*** matrices, vector<string> matrixNames) {
	Matrix* matrix = (*matrices)[matrixNumber];
	fprintf(file, (matrixNames[matrixNumber] + NEW_LINE).c_str());
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

bool FileManager::printTableToFile(Tables tableNumber, Table*** tables, vector<string> tableNames) {
	Table* table = (*tables)[tableNumber];
	fprintf(file, (tableNames[tableNumber] + NEW_LINE).c_str());
	for (size_t i = 0; i < table->getArraySize(); i++)
	{
		fprintf(file, (std::to_string(table->getAt(i)) + " ").c_str());
	}
	fprintf(file, NEW_LINE.c_str());
	return true;
}

bool FileManager::setValuesToFile(MscnProblem* problem) {
	vector<Objects> obj{ Supplier,Fabric,Warehouse,Shop };
	for (size_t i = 0; i < obj.size(); i++)
	{
		printQuantity(obj.at(i), problem, objNames);
	}
	vector<Tables> tab{ SD,SF,SM,SS };
	printTablesToFile(tab, problem, tabNames);
	vector<Matrices> mat{ CD,CF,CM };
	printMatricesToFile(mat, problem, matNames);
	vector<Tables> tab2{ UD,UF,UM,PS };
	printTablesToFile(tab2, problem, tabNames);
	vector<Matrices> mat2{ XD,XF,XM };
	printMatricesToFile(mat2, problem, matNames);
	return true;
}

bool FileManager::printMatricesToFile(vector<Matrices> mat, MscnProblem* problem, vector<string> names){
	for (size_t i = 0; i < mat.size(); i++)
	{
		printMatrixToFile(mat.at(i), problem->getMatrices(), names);
	}
	return true;
}
	

bool FileManager::printTablesToFile(vector<Tables> mat, MscnProblem* problem, vector<string> names){
	for (size_t i = 0; i < mat.size(); i++)
	{
		printTableToFile(mat.at(i), problem->getTables(), names);
	}
	return true;
	}