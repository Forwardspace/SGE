#pragma once
#include "stdheaders.h"

namespace sge {
	class IOManager {
	public:
		static std::string stringFromFile(std::string filename);

		static const aiScene* sceneFromFile(std::string filename);
		static aiMesh* firstMeshFromScene(const aiScene* scene);

		//Singleton
		IOManager() = delete;
		~IOManager() = delete;

		static void terminate() { delete importer; }

	private:
		static Assimp::Importer* importer;
	};
}