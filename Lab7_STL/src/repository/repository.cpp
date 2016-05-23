/*
 * repository.cpp
 *
 *  Created on: Mar 28, 2016
 *      Author: marius
 */

#include "repository.h"
#include <algorithm>

void Repository::add(const Film& film) {
	if (std::find(__items.begin(), __items.end(), film) == __items.end()) {
		__items.push_back(film);
		return;
	}
	throw RepositoryException("Error in repository: film already added!");
}

void Repository::del(const Film& film) {
	auto filmIt = std::find(__items.begin(), __items.end(), film);
	if (filmIt == __items.end()) {
		throw RepositoryException("Error in repository: trying to delete unexistent film!");
	}
	__items.erase(filmIt);
}

void Repository::update(const Film& newFilm) {
	auto oldFilmIterPoz = std::find_if(__items.begin(), __items.end(), [&](const Film& film) {return film.getTitle() == newFilm.getTitle(); });
	if (oldFilmIterPoz == __items.end()) {
		throw RepositoryException(
			"Error in repository: trying to update unexistent film!");
	}
	int index{ std::distance(__items.begin(), oldFilmIterPoz) };
	__items[index] = newFilm;
}

