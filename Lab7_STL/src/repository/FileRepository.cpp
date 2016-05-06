#include "FileRepository.h"
#include <fstream>
#include <sstream>

std::vector<std::string> split(const std::string& str, char delimiter) {
	std::vector<std::string> rez;
	std::stringstream ss(str);
	std::string token;
	while (std::getline(ss, token, delimiter)) {
		rez.push_back(token);
	}
	return rez;
}

std::vector<Film> FileRepository::__loadFromFile() {
	std::vector<Film> result;
	std::ifstream out(__fileName);
	if (out.is_open() == false) {
		throw RepositoryException("Could not open file: " + __fileName);
	}
	std::string line;
	std::vector<std::string> attrs;
	while (std::getline(out, line)) {
		attrs = split(line, ',');
		result.push_back(Film{ attrs[0], attrs[1], std::stoi(attrs[2]), attrs[3] });
	}
	return result;
}