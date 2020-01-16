// ConsoleApplication16.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <string>
#include "MscnProblem.h"
#include "FileManager.h"
#include "RandomSearch.h"
#include "DiffEval.h"

/*double sumHorizontal(Matrix** array, int matrixNumber, int indexX) {
	//if (matrixNumber < 0 || matrixNumber >= NUMBER_OF_MATRICES) return 0;
	double sum = 0;
	Matrix* matrix = (array[matrixNumber]);
	for (size_t j = 0; j < matrix->getsizeY(); j++)
	{
		sum += matrix->getAt(indexX, j);
	}
	matrix->setAt(1000, 0, 0);
	return sum;
}

*/

int main()
{
	/*char bufor[1];
	int u = fgetc(file);
	bufor[0] = (char)u;
	std::string s(bufor);
	std::cout << bufor[0];
	u = fgetc(file);
	bufor[0] = (char)u;
	std::cout << bufor[0];
	u = fgetc(file);
	bufor[0] = (char)u;
	std::cout << bufor[0];
	u = fgetc(file);
	bufor[0] = (char)u;
	std::cout << bufor[0];*/
/*
	MscnProblem prob;
	prob.loadFromFile("C:/Users/Karol/Desktop/cpp.txt",NULL);
	std::cout << prob.calcIncome();
	std::cout << prob.checkConstraints();
	//double arr[] = { 1,1,-2 };
	//double result = prob.getQuality(arr, 3, NULL);
	//cout << result;
	prob.saveToFile("C:/Users/Karol/Desktop/Notariusz.txt");
	prob.changeSizeOF(Shop, 4);
	prob.changeSizeOF(Warehouse, 4);
	prob.changeSizeOF(Fabric, 3);
	prob.changeSizeOF(Supplier, 2);
	prob.generateInstance(217);
	RandomSearch search(263);
	double* solution = search.solveProblem(&prob);
	for (size_t i = 0; i < prob.getProblemSize(); i++)
	{
		cout << solution[i] << " ";
	}*/
	MscnProblem prob;
	DiffEval eval;
	prob.changeSizeOF(Shop, 4);
	prob.changeSizeOF(Warehouse, 4);
	prob.changeSizeOF(Fabric, 3);
	prob.changeSizeOF(Supplier, 2);
	prob.generateInstance(98);
	//RandomSearch search(217);
	eval.solve(&prob,217)->printSolution();
	

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
