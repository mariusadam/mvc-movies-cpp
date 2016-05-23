/*
 * DynamicVector.h
 *
 *  Created on: Mar 26, 2016
 *      Author: marius
 */

#ifndef UTIL_DYNAMICVECTOR_H_
#define UTIL_DYNAMICVECTOR_H_
#include <iostream>
#include <assert.h>
#include <string>
#include <string.h>
using namespace std;
#define DEFAULT_MAX_SIZE 5

class VectorException;
template<typename Element> class DynamicVector;

template<typename Element>
class IteratorVector {
private:
	const DynamicVector<Element>& __vec;
	int __poz;
public:
	friend class DynamicVector<Element> ;
	IteratorVector(const DynamicVector<Element>& vec) :
			__vec { vec }, __poz { 0 } {
	}

	IteratorVector(const DynamicVector<Element>& vec, int poz) :
			__vec { vec }, __poz { poz } {
	}

	~IteratorVector() {

	}
	Element& element() const {
		return __vec.elementAt(__poz);
	}

	bool valid() const {
		return __poz < __vec.size();
	}

	void next() {
		__poz++;
	}

	Element& operator*() {
		return element();
	}

	IteratorVector& operator++() {
		next();
		return *this;
	}

	bool operator==(const IteratorVector& other) {
		return __poz == other.__poz;
	}

	bool operator!=(const IteratorVector& other) {
		return !(*this == other);
	}
};

template<typename Element>
class DynamicVector {
private:
	int __size;
	int __capacity;
	Element* __elements;
	void __resize();
	void __ensureCapacity();
public:
	//typedef Element value_type;
	/**
	 * Default contructor
	 */
	DynamicVector() :
			__size { 0 }, __capacity { DEFAULT_MAX_SIZE }, __elements {
					new Element[DEFAULT_MAX_SIZE] } {
	}

	/**
	 * Destroys the vector
	 */
	~DynamicVector() {
		delete[] this->__elements;
	}

	/**
	 * Copy constructor
	 */
	DynamicVector(const DynamicVector& other);

	/**
	 * Returns the size of the vector
	 */
	const int size() const {
		return __size;
	}

	/**
	 * Inserts a new element at the end
	 */
	void push_back(const Element& element);

	/**
	 * Returns the element at a given index
	 */
	Element& elementAt(const int index) const;

	int index(const Element& element) const;

	/**
	 * Overloaded [] operator. The argument is a subscript. *
	 *This function returns a reference to the element
	 *in the array indexed by the subscript.
	 */
	Element& operator[](const int subScript) const;

	void removeAt(const int& index);

	void erase(const Element& element);

	DynamicVector& operator+=(const Element& element) {
		push_back(element);
		return *this;
	}

	DynamicVector& operator-=(const Element& element) {
		erase(element);
		return *this;
	}

	DynamicVector& operator+(const Element& element) {
		this->push_back(element);
		return *this;
	}

	bool operator==(const DynamicVector<Element>& other);

	DynamicVector& operator-(const Element& element);

	DynamicVector& operator=(const DynamicVector<Element>& other);

	IteratorVector<Element> begin() const {
		return IteratorVector<Element> { *this };
	}

	IteratorVector<Element> end() const {
		return IteratorVector<Element> { *this, __size };
	}

	void sort(bool (*cmpFct)(const Element& elem1, const Element& elem2));
};

/**
 * Copy contructor
 */
template<typename Element>
DynamicVector<Element>::DynamicVector(const DynamicVector& other) {
	if (*this == other) {
		return;
	}
	__elements = new Element[other.__capacity];
	for (int i = 0; i < other.__size; i++) {
		__elements[i] = other.__elements[i];
	}
	__size = other.__size;
	__capacity = other.__capacity;
}

/**
 * Inserts a new element at the end of the vector
 */
template<typename Element>
void DynamicVector<Element>::push_back(const Element& element) {
	__ensureCapacity();
	this->__elements[this->__size++] = element;
}

/**
 * Returns the element at a given index
 * pre : 0 <= index <= size
 */
template<typename Element>
Element& DynamicVector<Element>::elementAt(const int index) const {
	if (index < 0 || index >= __size) {
		throw VectorException("Error : index out of range!");
	}
	return this->__elements[index];
}

/**
 * Overloaded [] operator
 */
template<typename Element>
Element& DynamicVector<Element>::operator[](const int subScript) const {
	return this->elementAt(subScript);
}

/**
 * Reallocate memory
 */
template<typename Element>
void DynamicVector<Element>::__resize() {
	int newCapacity = this->__capacity + this->__capacity / 2 + 1;
	Element* newElements = new Element[newCapacity];
	if (newElements == NULL) {
		throw VectorException("Error : could not resize, out of memory!");
	}
	for (int i = 0; i < this->__size; i++) {
		newElements[i] = this->__elements[i];
	}
	delete[] this->__elements;
	this->__elements = newElements;
	this->__capacity = newCapacity;
}

/**
 * Assignment operator
 */
template<typename Element>
DynamicVector<Element>& DynamicVector<Element>::operator=(
		const DynamicVector<Element>& other) {
	if (this == &other) {
		return *this;
	}
	delete[] __elements;
	__elements = new Element[other.__capacity];
	for (int i = 0; i < other.__size; i++) {
		__elements[i] = other.__elements[i];
	}
	__size = other.__size;
	__capacity = other.__capacity;
	return *this;
}

template<typename Element>
int DynamicVector<Element>::index(const Element& element) const {
	for (int i = 0; i < __size; i++) {
		if (this->__elements[i] == element) {
			return i;
		}
	}
	return -1;
}

template<typename Element>
void DynamicVector<Element>::removeAt(const int& index) {
	if (index < 0 || index >= __size) {
		throw VectorException("Error : index out of range!");
	}
	for (int i = index; i < __size - 1; i++) {
		__elements[i] = __elements[i + 1];
	}
	__size--;
}

template<typename Element>
void DynamicVector<Element>::erase(const Element& element) {
	int pos { this->index(element) };
	if (pos == -1) {
		throw VectorException(
				"Error : could not remove element because it is not in vector!");
	}
	this->removeAt(pos);
}

template<typename Element>
DynamicVector<Element>& DynamicVector<Element>::operator-(
		const Element& element) {
	this->erase(element);
	return *this;
}

template<typename Element>
bool DynamicVector<Element>::operator==(const DynamicVector<Element>& other) {
	if (this->__size != other.__size) {
		return false;
	}
	for (int i = 0; i < this->__size; i++) {
		if (this->__elements[i] != other.__elements[i]) {
			return false;
		}
	}
	return true;
}

template<typename Element>
void DynamicVector<Element>::__ensureCapacity() {
	if (this->__size < this->__capacity) {
		return;
	}
	this->__resize();
}

template<typename Element>
void DynamicVector<Element>::sort(
		bool (*cmpFct)(const Element& elem1, const Element& elem2)) {
	for (int i = 0; i < __size; i++) {
		for (int j = i + 1; j < __size; j++) {
			if (cmpFct(__elements[i], __elements[j]) == false) {
				Element temp { __elements[i] };
				__elements[i] = __elements[j];
				__elements[j] = temp;
			}
		}
	}
}

///////////////////////////////////////////////////////////////////////////////////
class VectorException: public exception {
private:
	string __msg;
public:
	VectorException() {
		__msg = "";
	}

	VectorException(const string msg) {
		__msg = msg;
	}

	~VectorException() {
	}

	const string getMsg() const {
		return __msg;
	}

	friend ostream& operator<<(ostream& out, const VectorException& except);
};

#endif /* UTIL_DYNAMICVECTOR_H_ */
