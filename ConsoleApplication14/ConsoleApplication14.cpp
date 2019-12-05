// ConsoleApplication14.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <memory>

#include "MySmartPointer.h"

using namespace std;
void fun(Object* a,Object* b) {
	MySmartPointer<Object> pointer(a);
	MySmartPointer<Object> pointer2(pointer);
	MySmartPointer<Object> pointer3(b);
	pointer3 = pointer;
}



int main()
{
	MySmartPointer<Object> pointer(new Object());
	MySmartPointer<Object> pointer2(pointer);
	MySmartPointer<Object> pointer3(new Object());
	MySmartPointer<Object> pointer4(pointer3);
	pointer3 = pointer;
	Object aaa;
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
