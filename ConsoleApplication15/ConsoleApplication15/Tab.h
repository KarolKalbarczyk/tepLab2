#pragma once

#define DEF_TAB_SIZE 10
class Tab
{
public:
	Tab() { tab = new int[DEF_TAB_SIZE]; size = DEF_TAB_SIZE; }
	Tab(const Tab &other);
	Tab(Tab &&cOther);
	Tab operator=(const Tab &other);
	~Tab();
	bool setSize(int newSize) { size = newSize; };
	int getSize() { return(size); }
	Tab operator=(Tab &&other);
	void fillArray(int toAdd);
	void printArray();
private:
	void copy(const Tab &cOther);
	int *tab;
	int size;
};//class Tab 