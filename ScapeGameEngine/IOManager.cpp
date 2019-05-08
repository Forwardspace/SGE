#include "IOManager.h"

namespace sge {
	Assimp::Importer* IOManager::importer;

	void IOManager::init() {
		IOManager::importer = new Assimp::Importer;
	}

	std::string IOManager::stringFromFile(fs::path filename) {
		std::ifstream in(filename);

		if (!in) {
			throw std::runtime_error("Unable to open ifstream. Elsestream ain't working as well.");
		}

		std::string filestr;
		std::string currline;
		while (getline(in, currline)) {
			filestr += currline + '\n';
		}

		return filestr;
	}

	const aiScene* IOManager::sceneFromFile(fs::path filename) {
		const aiScene* scene = importer->ReadFile(
			filename.string(),
			aiProcess_CalcTangentSpace |	//Not needed for now, but future-proofing is always welcome
			aiProcess_Triangulate |
			aiProcess_JoinIdenticalVertices |
			aiProcess_SortByPType |
			aiProcess_FindInvalidData |
			aiProcess_GenUVCoords |
			aiProcess_OptimizeMeshes |
			aiProcess_ValidateDataStructure
		);

		if (!scene) {
			throw std::runtime_error("Unable to load scene. Hoc scaena non est bona!");
		}

		return scene;
	}

	aiMesh* IOManager::firstMeshFromScene(const aiScene* scene) {
		if (!(scene->HasMeshes())) {
			throw std::runtime_error("Scene does not have any mesh! Hoc scaena quoque non est bona!");
		}
		
		return scene->mMeshes[0];
	}
}