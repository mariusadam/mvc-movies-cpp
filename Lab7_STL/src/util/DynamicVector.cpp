/*
 * DynamicVector.cpp
 *
 *  Created on: Mar 27, 2016
 *      Author: marius
 */
#include "DynamicVector.h"

ostream& operator<<(ostream& out, const VectorException& except) {
	out << except.__msg;
	return out;
}


