#include "IOManager.h"

namespace sge {
	std::string IOManager::stringFromFile(std::string filename) {
		std::ifstream in(filename);

		if (!in) {
			throw std::runtime_error("Unable to open ifstream. Whilestream ain't working as well.");
		}

		std::string filestr;
		std::string currline;
		while (getline(in, currline)) {
			filestr += currline + '\n';
		}

		return filestr;
	}
}