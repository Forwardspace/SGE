#pragma once
#include "stdheaders.h"

namespace sge {
	class IOManager {
	public:
		static std::string stringFromFile(std::string filename);

		//Singleton
		IOManager() = delete;
		~IOManager() = delete;
	};
}