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
const vector<string> matNames{ "XD","XF","XM" ,"CD","CF","CM","XDMIN","XDMAX","XFMIN","XFMAX" ,"XMMIN","XMMAX" };
const vector<string> objNames{ "D","F","M","S" };
const string READ_OPTION = "rb";
const string WRITE_OPTION = "w+";
const vector<int> order{ -(SD + 1),-(SF + 1),-(SM + 1),-(SS + 1),CD + 1,CF + 1,CM + 1,-(UD + 1),-(UF + 1),-(UM + 1),-(PS + 1),
				   XDMIN + 1, XDMAX + 1, XFMIN + 1, XFMAX + 1, XMMIN + 1, XMMAX + 1 ,XD + 1,XF + 1,XM + 1 };
/*vector<Tables> tab{ SD,SF,SM,SS };
vector<Matrices> mat{ CD,CF,CM };
vector<Tables> tab2{ UD,UF,UM,PS };
vector<Matrices> mat2{ XD,XF,XM };*/

using namespace std;

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

class ProblemFileIOManager {
public:
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

};

#endif