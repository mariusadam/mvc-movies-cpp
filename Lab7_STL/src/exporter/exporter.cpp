#include "exporter.h"
#include <fstream>

void exportToCsv(const std::string& fileName, const std::vector<Film>& all) {
	std::ofstream out(fileName, std::ios::trunc);
	if (out.is_open() == false) {
		throw FilmException("Could not open file: " + fileName);
	}
	for (const Film& film : all) {
		out << film.getTitle() << "," <<
			film.getGen() << "," <<
			film.getReleaseYear() << "," <<
			film.getMainActor() << std::endl;
	}
	out.close();
}

void exportToHtml(const std::string& fileName, const std::vector<Film>& all) {
	std::ofstream out(fileName, std::ios::trunc);
	if (!out.is_open()) {
		throw FilmException("Could not open file: " + fileName);
	}
	out << "<html><body>" << std::endl;
	out << "<table border=\"1\" style=\"width:100 % \">" << std::endl;
	for (const Film& film : all) {
		out << "<tr>" << std::endl;
		out << "<td>" << film.getTitle() << "</td>" << std::endl;
		out << "<td>" << film.getGen() << "</td>" << std::endl;
		out << "<td>" << film.getReleaseYear() << "</td>" << std::endl;
		out << "<td>" << film.getMainActor() << "</td>" << std::endl;
		out << "</tr>" << std::endl;
	}
	out << "</table>" << std::endl;
	out << "</body></html>" << std::endl;
	out.close();
}