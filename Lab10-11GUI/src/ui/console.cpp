/*
 * console.cpp
 *
 *  Created on: Mar 28, 2016
 *      Author: marius
 */

#include "console.h"
#include <sstream>


template<typename T> T myRead(string msg) {
	T ceva;
	string text{ "" };
	cout << msg;
	cout.flush();
	getline(cin, text);
	stringstream convert(text);
	convert >> ceva;
	return ceva;
}

void Console::__printMainMenu() {
	cout << "Main menu: " << endl <<
		"			0 : exit" << endl <<
		"			1 : add a movie" << endl <<
		"			2 : delete a movie" << endl <<
		"			3 : update a movie" << endl <<
		"			4 : show all" << endl <<
		"			5 : search movies by title" << endl <<
		"			6 : filter by title" << endl <<
		"			7 : filter by release year" << endl <<
		"			8 : sort asc by title" << endl <<
		"			9 : sort desc by title" << endl <<
		"		   	10 : sort asc by main actor" << endl <<
		"		   	11 : sort desc by main actor" << endl <<
		"		   	12 : sort asc by year + genre" << endl <<
		"		   	13 : sort desc by year + genre" << endl <<
		"			14 : add a movie to cart" << endl <<
		"		   	15 : fill cart with random movies" << endl <<
		"		   	16 : show cart items" << endl <<
		"		   	17 : empty the cart" << endl <<
		"		   	18 : export cart to file" << endl <<
		"			19 : undo" << endl;
}

string Console::__readOption() {
	return myRead<string>("Enter your command: ");
}

void Console::__printTableHeader() {
	std::cout << "|";
	std::cout.width(20);
	std::cout << "Title";
	std::cout << "|";
	std::cout.width(15);
	std::cout << "Genre";
	std::cout << "|";
	std::cout.width(12);
	std::cout << "Release Year";
	std::cout << "|";
	std::cout.width(30);
	std::cout << "Main Actor";
	std::cout << "|";
	std::cout << std::endl;
}

void Console::__printMovies(const std::string& tableTitle, const std::vector<Film>& movies) {
	std::cout << tableTitle << "(" << movies.size() << ")" << std::endl;
	std::cout << "+--------------------+---------------+------------+------------------------------+" << std::endl;
	__printTableHeader();
	std::cout << "+--------------------+---------------+------------+------------------------------+" << std::endl;
	std::cout << "+--------------------+---------------+------------+------------------------------+" << std::endl;
	for (const auto& film : movies) {
		std::cout << "|";
		std::cout.width(20);
		std::cout << film.getTitle();
		std::cout << "|";
		std::cout.width(15);
		std::cout << film.getGen();
		std::cout << "|";
		std::cout.width(12);
		std::cout << film.getReleaseYear();
		std::cout << "|";
		std::cout.width(30);
		std::cout << film.getMainActor();
		std::cout << "|" << std::endl;
		std::cout << "+--------------------+---------------+------------+------------------------------+" << std::endl;
		//std::cout << "----------------------------------------------------------------------------------" << std::endl;
	}
}

void Console::__showAll() {
	std::vector<Film>& alls{ __ctrl.getAll() };
	if (alls.size() == 0) {
		cout << "There is nothing to see here!" << endl;
	}
	else {
		__printMovies("Current movies are:", alls);
	}
}

string Console::__readTitle() {
	return myRead<string>("Enter the title of the movie: ");
}

string Console::__readGen() {
	return myRead<string>("Enter the genre of the movie: ");
}

int Console::__readReleaseYear() {
	return myRead<int>("Enter the release year of the movie: ");
}

string Console::__readMainActor() {
	return myRead<string>("Enter the name of the main actor of the movie: ");
}

void Console::__addFlow() {
	string title = __readTitle();
	string gen = __readGen();
	int releaseYear = __readReleaseYear();
	string mainActor = __readMainActor();
	try {
		__ctrl.add(title, gen, releaseYear, mainActor);
		cout << "The movie was succesfully added!" << endl;
	}
	catch (FilmException& error) {
		cout << "Could not add the movie:" << endl;
		cout << error << endl;
	}
}

void Console::__deleteFlow() {
	string title = __readTitle();
	try {
		__ctrl.del(title);
		cout << "Movie was succesfully deleted!" << endl;
	}
	catch (FilmException& error) {
		cout << "Could not delete movie!" << endl;
		cout << error << endl;
	}
}

void Console::__updateFlow() {
	string title = __readTitle();
	try {
		Film oldFilm{ __ctrl.find(title) };
		cout << "Insert the new atributes for the selected movie" << endl;
		string newGen = __readGen();
		int newReleaseYear = __readReleaseYear();
		string newMainActor = __readMainActor();
		Film newFilm{ __ctrl.createFilm(title, newGen, newReleaseYear, newMainActor) };
		__ctrl.update(newFilm);
		cout << "The movie was succesfully updated!" << endl;
	}
	catch (FilmException& error) {
		cout << "Could not update movie!" << endl;
		cout << error << endl;
	}
}

void Console::__searchFlow() {
	cout << "Enter a part of the title : ";
	string title;
	getline(cin, title);
	try {
		__ctrl.validateTitle(title);
		const std::vector<Film>& result{ __ctrl.search(title) };
		cout << "Movies with title containing " + title + " are :";
		__printMovies("", result);
	}
	catch (FilmException& error) {
		cout << error << endl;
	}
}

void Console::__filterByTitle() {
	string title{ __readTitle() };
	try {
		__ctrl.validateTitle(title);
		const std::vector<Film> result{ __ctrl.filterByTitle(title) };
		__printMovies("Movies with title " + title + " ", result);
	}
	catch (FilmException& error) {
		cout << error << endl;
	}
}

void Console::__filterByReleaseYear() {
	int releaseYear{ __readReleaseYear() };
	try {
		__ctrl.validateReleaseYear(releaseYear);
		const std::vector<Film> result{ __ctrl.filterByReleaseYear(releaseYear) };
		__printMovies("Movies released in " + to_string(releaseYear) + " ", result);
	}
	catch (FilmException& error) {
		cout << error << endl;
	}
}

void Console::__fillRandomFlow() {
	int howMany = myRead<int>("Enter the number of movies you want to add: ");
	auto& all = __ctrl.getAll();
	if (howMany > all.size() || howMany < 0) {
		cout << "Enter a valid number next time!" << endl;
		return;
	}
	__ctrl.fillCartRandom(howMany);
	auto& cart = __ctrl.getCartMovies();
	cout << cart.size() << " movies had been added to the cart!" << endl;
}

void Console::__addToCartFlow() {
	string title = __readTitle();
	try {
		Film toAdd = __ctrl.find(title);
		__ctrl.addToCart(toAdd);
		cout << "Movie with title " << title << " was succesfully added to cart!" << endl;
	}
	catch (FilmException& e) {
		cout << "Could not add the movie to cart:" << endl;
		cout << e << endl;
	}
}

void Console::__exportCartToFile() {
	std::string fileName = myRead<std::string>("Enter the file name: ");
	try {
		__ctrl.writeCartToFile(fileName);
		std::cout << "Cart was succesfuly saved to file: " + fileName << std::endl;
	}
	catch (FilmException& err) {
		cout << err << endl;
	}
}

void Console::__undo() {
	try {
		__ctrl.undo();
	}
	catch (FilmException& err) {
		cout << err << endl;
	}
}

void Console::run() {
	for (; true;) {
		__printMainMenu();
		string cmd = myRead<string>("Enter your command: ");
		if (cmd == "0") {
			cout << "Exiting now..." << endl;
			return;
		}
		else if (cmd == "1") {
			__addFlow();
		}
		else if (cmd == "2") {
			__deleteFlow();
		}
		else if (cmd == "3") {
			__updateFlow();
		}
		else if (cmd == "4") {
			__showAll();
		}
		else if (cmd == "5") {
			__searchFlow();
		}
		else if (cmd == "6") {
			__filterByTitle();
		}
		else if (cmd == "7") {
			__filterByReleaseYear();
		}
		else if (cmd == "8") {
			__printMovies("Movies sorted asc by title", __ctrl.getSortedByTitleAsc());
		}
		else if (cmd == "9") {
			__printMovies("Movies sorted desc by title", __ctrl.getSortedByTitleDesc());
		}
		else if (cmd == "10") {
			__printMovies("Movies sorted asc by main actor", __ctrl.getSortedByMainActorAsc());
		}
		else if (cmd == "11") {
			__printMovies("Movies sorted desc by main actor", __ctrl.getSortedByMainActorDesc());
		}
		else if (cmd == "12") {
			__printMovies("Movies sorted asc by release year and genre", __ctrl.getSortedByYearGenreAsc());
		}
		else if (cmd == "13") {
			__printMovies("Movies sorted desc by release year and genre", __ctrl.getSortedByYearGenreDesc());
		}
		else if (cmd == "14") {
			__addToCartFlow();
		}
		else if (cmd == "15") {
			__fillRandomFlow();
		}
		else if (cmd == "16") {
			__printMovies("Cart movies ", __ctrl.getCartMovies());
		}
		else if (cmd == "17") {
			__ctrl.clearCart();
		}
		else if (cmd == "18") {
			__exportCartToFile();
		}
		else if (cmd == "19") {
			__undo();
		}
		else {
			cout << "Invalid option!" << endl;
		}
	}
}
