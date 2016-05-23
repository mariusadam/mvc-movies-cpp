/*
 * console.h
 *
 *  Created on: Mar 27, 2016
 *      Author: marius
 */

#ifndef UI_CONSOLE_H_
#define UI_CONSOLE_H_
#include <iostream>
#include <string>
#include "../controller/controller.h"

using namespace std;

class Console {
private:
	Controller& __ctrl;

	void __printMainMenu();
	string __readOption();
	void __addFlow();
	void __addToCartFlow();
	void __showAll();
	void __deleteFlow();
	void __updateFlow();
	void __searchFlow();
	void __filterByTitle();
	void __filterByReleaseYear();
	void __printTableHeader();
	void __printMovies(const std::string& tableTitle, const std::vector<Film>& movies);
	void __fillRandomFlow();
	void __exportCartToFile();
	void __undo();
	string __readTitle();
	string __readGen();
	int __readReleaseYear();
	string __readMainActor();

public:
	Console(Controller& ctrl) :
			__ctrl { ctrl } {
	}
	Console(Console& cons) = delete;

	void run();
};

#endif /* UI_CONSOLE_H_ */
