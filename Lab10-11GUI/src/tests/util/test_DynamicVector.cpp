/*
 * test_DynamicVector.cpp
 *
 *  Created on: Mar 26, 2016
 *      Author: marius
 */

#include "test_DynamicVector.h"

void testConstructors() {
	DynamicVector<int> intVector;
	int start { 0 }, end { 2000 };
	assert(intVector.size() == 0);
	//testin for 2000 integer values
	for (int i = start; i <= end; i++) {
		intVector.push_back(i);
	}
	assert(intVector.size() == end + 1);
	for (int i = start; i <= end; i++) {
		assert(intVector[i] == i);
	}
	DynamicVector<int> copyVector { intVector };
	assert(intVector == copyVector);
}

void testOperations() {
	DynamicVector<int> vec, vec2, vec3;
	int start { 0 }, end { 500 };
	assert(vec.size() == 0);
	assert(vec2.size() == 0);
	//testin for 2000 integer values
	for (int i = start; i <= end; i++) {
		vec.push_back(i);
		vec2 += i;
		vec3 = vec3 + i;
	}
	assert(vec == vec2);
	assert(vec == vec3);
	assert(vec.size() == end + 1);
	assert(vec2.size() == end + 1);
	assert(vec3.size() == end + 1);
	for (int i = start; i <= end; i++) {
		assert(vec[i] == i);
		assert(vec2.elementAt(i) == i);
		assert(vec3[i] == i);
	}
	for (int i = start; i <= end; i++) {
		vec -= i;
		vec2 = vec2 - i;
		vec3.erase(i);
	}
	assert(vec == vec2);
	assert(vec == vec3);
	assert(vec.size() == start);
	assert(vec2.size() == start);
	assert(vec3.size() == start);
}

void testWithDomainClass() {
	Film f1 { "Ceva", "actiune", 199, "ceva actor" };
	Film f2 { "asd", "sqw", 34, "ceva fdfs" };
	Film f3 { "asd", "sdd", 432, "dfs sdf" };
	Film f4 { "asd", "dgg", 11, "vxc cvxvx" };
	Film f5 { "asd", "gg", 66, "cv ccccc" };
	DynamicVector<Film> vec;
	assert(vec.size() == 0);
	vec.push_back(f1);
	assert(vec.size() == 1);
	vec = vec + f2 + f3;
	assert(vec.size() == 3);
	vec += f4;
	vec += f5;
	assert(vec.size() == 5);
	assert(vec.elementAt(0) == f1 && vec.index(f1) == 0 && vec[0] == f1);
	assert(vec.elementAt(1) == f2 && vec.index(f2) == 1 && vec[1] == f2);
	assert(vec.elementAt(2) == f3 && vec.index(f3) == 2 && vec[2] == f3);
	assert(vec.elementAt(3) == f4 && vec.index(f4) == 3 && vec[3] == f4);
	assert(vec.elementAt(4) == f5 && vec.index(f5) == 4 && vec[4] == f5);

	Film f6 { f5 };
	assert(vec.elementAt(4) == f6 && vec.index(f6) == 4 && vec[4] == f6);
	f6.setTitle("CEva diferit");
	assert(vec.index(f6) == -1);

	DynamicVector<Film> vecTemp;
	vecTemp = vecTemp + f1 + f2 + f3 + f4 + f5;
	assert(vec == vecTemp);
	vec = vec - f1 - f4;
	assert(vec.size() == 3);
	vec -= f2;
	vec -= f3;
	assert(vec.size() == 1);
	vec -= f5;
	assert(vec.size() == 0);
	vecTemp.erase(f5);
	vecTemp.erase(f2);
	for (int i = 1; i < 4; i++) {
		vecTemp.removeAt(0);
	}
	assert(vecTemp.size() == 0);
}

void test_DynamicVector() {
	cout << "=======================================" << endl;
	cout << "Testing DynamicVector class..." << endl;
	testConstructors();
	cout << "...";
	testOperations();
	cout << "...";
	testWithDomainClass();
	cout << "..." << endl;
	cout << "DynamicVector class tested succesfully!" << endl;
	cout << "=======================================" << endl;
}

