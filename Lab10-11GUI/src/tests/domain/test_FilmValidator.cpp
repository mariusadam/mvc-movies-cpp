/*
 * test_FilmValidator.cpp
 *
 *  Created on: Mar 27, 2016
 *      Author: marius
 */

#include "test_FilmValidator.h"

void test_validateTitle() {
	FilmValidator validator;
	try {
		validator.validateTitle("");
		assert(false);
	} catch (ValidatorException&) {
		assert(true);
	}
	try {
		validator.validateTitle("Titlu corect");
		assert(true);
	} catch (ValidatorException&) {
		assert(false);
	}
	try {
		validator.validateTitle(
				"mai mult de 50 de caractereeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee"
						"eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee");
		assert(false);
	} catch (ValidatorException&) {
		assert(true);
	}
}

void test_FilmValidator() {
	test_validateTitle();
}
