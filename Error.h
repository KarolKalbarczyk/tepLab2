#pragma once

#ifndef ERROR_H
#define ERROR_H

#include <string>
#include <vector>

using namespace std;

const string openProperty = "w+";

class FileLastError{
private:
	static bool lastError;
public:
    FileLastError();
	FileLastError(string fileName);
	~FileLastError();
	void openFile(string fileName);
	void closeFile();
	void printLine(string text);
	void printManyLines(vector<string> text);
	static bool getLastError() { return lastError; };
private:
	FILE *file;
};

class FileThrowEx{
public:
	FileThrowEx();
	FileThrowEx(string fileName);
	~FileThrowEx();
	void openFile(string fileName);
	void closeFile();
	void printLine(string text);
	void printManyLines(vector<string> text);
private:
	FILE *file;
	const int error = 1;
};

class FileErrCode {
public:
	FileErrCode();
	FileErrCode(string fileName,bool* errorCode);
	~FileErrCode();
	bool openFile(string fileName);
	bool closeFile();
	bool printLine(string text);
	bool printManyLines(vector<string> text);
private:
	FILE *file;
};

#endif
