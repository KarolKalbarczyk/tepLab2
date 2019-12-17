#pragma once

#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include "MscnProblem.h"
#include <string>
#include <vector>
#include "Enums.h"

const char SPACE = ' ';
const string NEW_LINE = "\r\n";
const vector<string> tabNames{ "UD","UF","UM","SD","SF","SM","SS","PS" };
const vector<string> matNames{ "CD","CF","CM","XD","XF","XM" };
const vector<string> objNames{ "D","F","M","S" };
const string READ_OPTION = "rb";
const string WRITE_OPTION = "w+";


using namespace std;

class FileManager {
public:
	MscnProblem* loadFromFile(string filePath);
	bool saveToFile(string filePath, MscnProblem* problem);
private:
	FILE * file;
	bool linesToTables(vector<Tables> tables, MscnProblem* problem);
	bool linesToMatrices(vector<Matrices> matrices, MscnProblem* problem);
	bool lineToTable(Tables tableNumber, vector<double>* values,Table*** table);
	bool lineToMatrix(Matrices matrixNumber, vector<double>* values,Matrix*** matrices);
	bool setValuesFromFile(MscnProblem* problem);
	vector<int>* nextLine();
	vector<string>* transformLineToStrings(vector<int>* line);
	vector<double>* stringsToDoubles(vector<string>* strings);
	vector<double>* lineToDoubles();
	bool printQuantity(Objects object, MscnProblem* problem, vector<string> objectNames);
	bool printMatrixToFile(Matrices matrixNumber, Matrix*** matrices, vector<string> matrixNames);
	bool printTableToFile(Tables tableNumber, Table*** tables, vector<string> tableNames);
	bool printMatricesToFile(vector<Matrices> mat, MscnProblem* problem, vector<string> names);
	bool printTablesToFile(vector<Tables> mat, MscnProblem* problem, vector<string> names);
	bool setValuesToFile(MscnProblem* problem);

};

#endif