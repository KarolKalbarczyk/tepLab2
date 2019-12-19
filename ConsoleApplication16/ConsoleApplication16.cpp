// ConsoleApplication16.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <string>
#include "MscnProblem.h"
#include "FileManager.h"

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

	ProblemFileIOManager manager;
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
	MscnProblem* prob = manager.loadFromFile("C:/Users/Karol/Desktop/cpp.txt");
	std::cout << prob->calcIncome();
	std::cout << prob->checkConstraints();
	double arr[] = { 1,1,-2 };
	Response<double> resp = prob->getQuality(arr,3);
	cout << resp.getSuccess();
	cout << *(resp.getValue());
	manager.saveToFile("C:/Users/Karol/Desktop/Notariusz.txt", prob);
	delete prob;
	/*prob.changeSizeOF(Shop, 1);
	prob.changeSizeOF(Supplier, 1);
	prob.changeSizeOF(Fabric, 1);
	prob.changeSizeOF(Warehouse, 1);
	prob.setAtMatrix(CF, 4,0,0);
	prob.setAtMatrix(CD, 3,0,0);
	prob.setAtMatrix(CM, 1,0,0);
	prob.setAtMatrix(XD, 1, 0, 0);
	prob.setAtMatrix(XM, 1, 0, 0);
	prob.setAtMatrix(XF, 1, 0, 0);
	prob.setAtMatrix(CD, 3, 1, 0);
	prob.setAtMatrix(CM, 1, 0, 0);
	prob.setAtMatrix(CM, 1, 0, 1);
	prob.setAtMatrix(XD, 4, 0, 0);
	prob.setAtMatrix(XD, 4, 1, 0);
	prob.setAtMatrix(XM, 3, 0, 0);
	prob.setAtMatrix(XM, 3, 0, 1);
	prob.setAtMatrix(XF, 1, 0, 0);
	prob.setAtTable(UD, 10, 0);
	prob.setAtTable(UF, 10, 0);
	prob.setAtTable(UM, 10, 0);
	prob.setAtTable(PS, 100, 0);
	prob.setAtTable(SD, 100, 0);
	prob.setAtTable(SF, 50, 0);
	prob.setAtTable(SM, 10.5, 0);
	prob.setAtTable(SS, 100, 0);
	prob.setAtTable(UD, 10, 1);
	prob.setAtTable(UF, 10, 1);
	prob.setAtTable(UM, 10, 1);
	prob.setAtTable(PS, 100, 1);
	prob.setAtTable(SD, 100, 1);
	prob.setAtTable(SF, 50, 1);
	prob.setAtTable(SM, 10.5, 1);
	prob.setAtTable(SS, 100, 1);
	std::cout << prob.calcIncome();
	std::cout << prob.checkConstraints();*/


	/*Matrix** mat = new Matrix*[1];
	Matrix* matt = new Matrix;
	mat[0] = matt;
	mat[0]->changeSize(2, 3);
	mat[0]->setAt(1, 0, 0);
	mat[0]->setAt(2, 0, 1);
	mat[0]->setAt(3, 0, 2);
	mat[0]->setAt(4, 1, 0);
	mat[0]->setAt(5, 1, 1);
	mat[0]->setAt(6, 1, 2);
	std::cout << sumHorizontal(mat, 0, 0);
	std::cout << sumHorizontal(mat, 0, 0);*/
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
