#pragma once

#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include "MscnProblem.h"
#include <string>
#include <vector>
#include "Enums.h"

using namespace std;


class ProblemFileIOManager {
/*public:
	MscnProblem* loadFromFile(string filePath);
	bool saveToFile(string filePath, MscnProblem* problem);
private:
	FILE * file;
	Format format;
	bool linesToTables(vector<Tables> tables, MscnProblem* problem);
	bool linesToMatrices(vector<Matrices> matrices, MscnProblem* problem);
	bool lineToTable(Tables tableNumber, vector<double>* values,Table*** table);
	bool lineToMatrix(Matrices matrixNumber, vector<double>* values,Matrix*** matrices);
	bool setValuesFromFile(MscnProblem* problem);
	vector<int>* nextLine(bool *endOfFile);
	vector<string>* transformLineToStrings(vector<int>* line);
	vector<double>* stringsToDoubles(vector<string>* strings);
	vector<double>* lineToDoubles(bool *endOfFile);
	bool printQuantity(Subjects object, MscnProblem* problem, vector<string> objectNames);
	bool printMatrixToFile(Matrices matrixNumber, Matrix*** matrices);
	bool printTableToFile(Tables tableNumber, Table*** tables);
	bool printMatricesToFile(vector<Matrices> mat, MscnProblem* problem, vector<string> names);
	bool printTablesToFile(vector<Tables> mat, MscnProblem* problem, vector<string> names);
	bool setValuesToFile(MscnProblem* problem);
	*/
};

#endif