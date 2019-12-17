#pragma once
#include "RefCounter.h"

template <typename T> class MySmartPointer
{
public:
	MySmartPointer(T *pointer) {
		this->pointer = pointer;
		this->counter = new RefCounter();
		this->counter->add();
	}
	MySmartPointer(const MySmartPointer<T> &other) {
		copy(other);
	}
	~MySmartPointer() {
		decreaseCount();
	}
	void operator=(const MySmartPointer<T> &other);
	void operator=(T* pointer);
	T& operator*() { return(*pointer); }
	T* operator->() { return(pointer); }
	T* getPointer() { return pointer; };
private:
	T *pointer;
	RefCounter *counter;
	void copy(const MySmartPointer<T> &other);
	void decreaseCount();
};

template <typename T>
void MySmartPointer<T>::decreaseCount() {
	if (counter->dec() == 0)
	{
		delete pointer;
		delete counter;
	}
}

template <typename T>
void MySmartPointer<T>::copy(const MySmartPointer<T> &other) {
	this->pointer = other.pointer;
	this->counter = other.counter;
	this->counter->add();
}


template <typename T>
void MySmartPointer<T>::operator=(T* pointer) {
	decreaseCount();
	this->pointer = pointer;
	this->counter = new RefCounter();
	this->counter->add();
}

template <typename T>
void  MySmartPointer<T>::operator=(const MySmartPointer<T> &other) {
	decreaseCount();
	copy(other);
}

class Object {
private:
	int a;
};