#ifndef EXPORTER_EXPORTER_H_
#define EXPORTER_EXPORTER_H_
#include <vector>
#include "../domain/Film.h"

void exportToCsv(const std::string& fileName, const std::vector<Film>& all);
void exportToHtml(const std::string& fileName, const std::vector<Film>& all);

#endif // !EXPORTER_EXPORTER_H_
