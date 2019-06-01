#pragma once
#include "stdheaders.h"

namespace sge {
	class IOManager {
	public:
		static std::string stringFromFile(fs::path filename);

		static const aiScene* sceneFromFile(fs::path filename);
		static aiMesh* firstMeshFromScene(const aiScene* scene);
		
		//Loads simple CSV files into a vector
		static std::vector<std::string> stringVecFromCSV(fs::path filename);

		//Singleton
		IOManager() = delete;
		~IOManager() = delete;

		static void init();
		static void terminate() { delete importer; }

	private:
		static Assimp::Importer* importer;
	};
}