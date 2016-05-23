/*
 * test_film.cpp
 *
 *  Created on: Mar 26, 2016
 *      Author: marius
 */

#include "test_Film.h"

#include "assert.h"
#include <iostream>


void testFilmGettersSetters() {
	Film f1 { "Ceva", "actiune", 1999, "ceva actor" };
	assert(f1.getTitle() == "Ceva");
	assert(f1.getGen() == "actiune");
	assert(f1.getReleaseYear() == 1999);
	assert(f1.getMainActor() == "ceva actor");
	f1.setTitle("Ceva nou");
	f1.setGen("comedie");
	f1.setReleaseYear(2016);
	f1.setMainActor("alt actor");
	assert(f1.getTitle() == "Ceva nou");
	assert(f1.getGen() == "comedie");
	assert(f1.getReleaseYear() == 2016);
	assert(f1.getMainActor() == "alt actor");
}

void testContructors() {
	Film f1 { "Ceva", "actiune", 1999, "ceva actor" };
	Film f2 { f1 };
	assert(f2.getTitle() == "Ceva");
	assert(f2.getGen() == "actiune");
	assert(f2.getReleaseYear() == 1999);
	assert(f2.getMainActor() == "ceva actor");
	Film f3 { "asd", "bcxv", 23, "aaa" };
	assert(f3.getTitle() == "asd");
	assert(f3.getGen() == "bcxv");
	assert(f3.getReleaseYear() == 23);
	assert(f3.getMainActor() == "aaa");
	f3 = f1;
	assert(f1.getTitle() == f3.getTitle());
	assert(f1.getGen() == f3.getGen());
	assert(f1.getReleaseYear() == f3.getReleaseYear());
	assert(f1.getMainActor() == f3.getMainActor());
}

void testOperators() {
	Film f1 { "Ceva", "actiune", 1999, "ceva actor" };
	Film f2 { "Altceva", "comedie", 2010, "alt actor" };
	assert((f1 == f2) == false);
	assert((f1 != f2) == true);
	f2 = f1;
	assert((f1 == f2) == true);
	assert((f2 != f1) == false);
}

void testFilm() {
	std::cout << "==============================" << std::endl;
	std::cout << "Testing Film class..." << std::endl;
	testFilmGettersSetters();
	std::cout << "...";
	testContructors();
	std::cout << "...";
	testOperators();
	std::cout << "..." << std::endl;
	std::cout << "Film class tested succesfully!" << std::endl;
	std::cout << "==============================" << std::endl;
}

