
#include "pch.h"
#include <iostream>
#include "Error.h"

FileLastError::FileLastError() {
	file = NULL;
	lastError = false;
}

FileLastError::FileLastError(string fileName) {
	lastError = false;
	openFile(fileName);
}

FileLastError::~FileLastError() {
	if (file != NULL) closeFile();
}

void FileLastError::openFile(string fileName) {
	if (file != NULL) {
		closeFile();
		if (lastError) return;
	}
	file = fopen(fileName.c_str(),openProperty.c_str());
	lastError = (file == NULL);
}

void FileLastError::closeFile() {
	if (file == NULL) { lastError = true; return; }
	int succesOfClose = fclose(file);
	int succes = 0;
	file = NULL;
	lastError = (succes != succesOfClose);
}

void FileLastError::printLine(string text) {
	if (file == NULL) { lastError = true; return; }
	int succesOfPrint= fprintf(file,text.c_str());
	lastError = (succesOfPrint<0); // fprintf returns positive number in case of succes
}

void FileLastError::printManyLines(vector<string> text) {
	for (int i = 0; i < text.size(); i++)
	{
		printLine(text[i]);
		if (lastError == true) return;
	}
}


FileThrowEx::FileThrowEx() {
	file = NULL;
}

FileThrowEx::FileThrowEx(string fileName) {
	openFile(fileName);
}

FileThrowEx::~FileThrowEx() {
	if (file != NULL) fclose(file);
}

void FileThrowEx::openFile(string fileName) {
	if (file != NULL) {
		closeFile();
	}
	file = fopen(fileName.c_str(), openProperty.c_str());
	if (file == NULL) throw error;
}

void FileThrowEx::closeFile() {
	if (file == NULL)  throw error; 
	int succesOfClose = fclose(file);
	int succes = 0;
	file = NULL;
	if (succes != succesOfClose) throw error;
}

void FileThrowEx::printLine(string text) {
	if (file == NULL)  throw error; 
	int succesOfPrint = fprintf(file, text.c_str());
	if (succesOfPrint < 0) throw error;
}

void FileThrowEx::printManyLines(vector<string> text) {
	for (int i = 0; i < text.size(); i++)
	{
		try {
			printLine(text[i]);
		}
		catch (int err) {
			throw err;
		}
	}
}



FileErrCode::FileErrCode() {
	file = NULL;
}

FileErrCode::FileErrCode(string fileName,bool *errorCode) {
	*errorCode = openFile(fileName);
}

FileErrCode::~FileErrCode() {
	if (file != NULL) closeFile();
}

bool FileErrCode::openFile(string fileName) {
	if (file != NULL && !closeFile()) {
		return false;
	}
	file = fopen(fileName.c_str(), openProperty.c_str());
	return (file != NULL);
}

bool FileErrCode::closeFile() {
	if (file == NULL)  return false;
	int succesOfClose = fclose(file);
	int succes = 0;
	file = NULL;
	return (succes == succesOfClose);
}

bool FileErrCode::printLine(string text) {
	if (file == NULL)  return false;
	int succesOfPrint = fprintf(file, text.c_str());
	return  (succesOfPrint > 0);
}

bool FileErrCode::printManyLines(vector<string> text) {
	for (int i = 0; i < text.size(); i++)
	{
		if (!printLine(text[i])) return false;
	}
	return true;
}
