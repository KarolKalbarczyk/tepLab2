// ConsoleApplication9.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "table.h"

using namespace std;

void modTab(Table *pTab, int newSize) {
	(*pTab).setNewArraySize(newSize);
}

void modTab(Table pTab, int newSize) {
	pTab.setNewArraySize(newSize);
}

int main() {
	Table* table = new Table();
	Table* table2 = new Table(*table);
	Table* table3 = new Table("created", 10);
	Table* table4 = (*table).clone();
	(*table).fillArray();
	(*table4).fillArray();
	modTab(table, 4);
	(*table).fillArray();
	modTab(table4, 6);
	(*table4).fillArray();
	modTab(*table2, 6);
	(*table).printArray();
	(*table4).printArray();
	cout << (*table).getArraySize() << (*table2).getArraySize();
	delete table;
	delete table2;
	delete table3;
	delete table4;
	Table** array = new Table*[3];
	Table table5;
	Table table6(table5);
	Table table7("static", 5);
	array[0] = new Table();
	array[1] = new Table(table5);
	array[2] = new Table("dynamic",5);
	for (size_t i = 0; i < 3; i++)
	{
		delete array[i];
	}
	delete [] array;
	cout << " test";
	//Table* array = new Table[3];
	//de

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
