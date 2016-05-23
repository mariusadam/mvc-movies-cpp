//============================================================================
// Name        : Lab7.cpp
// Author      : marius
// Version     :
// Copyright   : Do not try to copy this!!!
// Description : Some boring console applicaton in C++, "modern"-style
//============================================================================
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <iostream>
#include "tests/domain/test_Film.h"
#include "tests/domain/test_FilmValidator.h"
#include "domain/Film.h"
#include "domain/FilmValidator.h"
#include "controller/controller.h"
#include "repository/repository.h"
#include "repository/FileRepository.h"
#include "ui/console.h"
#include <vector>
#include <random>
#include <chrono>
#include <algorithm>
#include <malloc.h>
#include <string>

//using namespace std;

void runTests() {
	testFilm();
	test_FilmValidator();
}

void addMovies(Repository& repo, int howMany) {
	for (int i = 1; i <= howMany; i++) {
		int randVal1 = (i + std::chrono::system_clock::now().time_since_epoch().count()) % howMany;
		int randVal2 = (randVal1 + std::chrono::system_clock::now().time_since_epoch().count()) % howMany;
		int randVal3 = (randVal2 + std::chrono::system_clock::now().time_since_epoch().count()) % howMany;
		int randVal4 = (randVal3 + std::chrono::system_clock::now().time_since_epoch().count()) % howMany;
		try {
			repo.add(Film{ "Titlu" + to_string(randVal1), "Gen" + to_string(randVal2), 1996 + randVal3 % 20, "Actor" + to_string(randVal4) });
		}
		catch (RepositoryException) {
			continue;
		}
	}

}

void runApp() {
	FilmValidator valid;
	FileRepository repo{ "Files//test.csv" };
	//addMovies(repo, 30);
	std::cout << "How do you want to save the cart?" << std::endl <<
		"		1 : CSV" << std::endl <<
		"		2 : HTML" << std::endl;
	std::string opt;
	std::getline(cin, opt);
	if (opt == "1") {
		FilmCartCsv csvCart{ repo };
		Controller ctrl{ repo, valid, csvCart };
		Console cons{ ctrl };
		cons.run();
	}
	else {
		FilmCartHtml htmlCart{ repo };
		Controller ctrl{ repo, valid, htmlCart };
		Console cons{ ctrl };
		cons.run();
	}

}

int main() {
	//runTests();
	runApp();
	_CrtDumpMemoryLeaks();
	return 0;
}
