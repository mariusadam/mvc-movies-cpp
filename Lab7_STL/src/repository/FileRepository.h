#ifndef REPOSITORY_FILEREPOSITORY_H_
#define REPOSITORY_FILEREPOSITORY_H_

#include "repository.h"
#include <vector>
#include <string>
#include "../exporter/exporter.h"

class FileRepository : public Repository {
private:
	std::string __fileName;

	std::vector<Film> __loadFromFile();

	void __saveToFile() {
		exportToCsv(__fileName, getAll());
	}
public:
	FileRepository(const std::string& fileName) : __fileName{ fileName } {
		__items = __loadFromFile();
	}
	~FileRepository(){
		__saveToFile();
	}
};

#endif // !REPOSITORY_FILEREPOSITORY_H_
