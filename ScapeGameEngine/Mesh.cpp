#include "Mesh.h"

namespace sge {
	Mesh::Mesh() {
	}

	Mesh::Mesh(VertexArray va, IndexArray ia, TexCoordArray ta) {
		VertArray_ = va;
		IndArray_ = ia;
		TCArray_ = ta;
	}

	void Mesh::appendMeshData(const aiScene* scene, aiMesh* mesh) {
		//aiVector3D is basically just three floats, right? I hope so...
		VertArray_ = std::vector<Vertex3D>(
			&mesh->mVertices[0],
			&mesh->mVertices[mesh->mNumVertices]
		);
		
		//Now faces are more complicated, for some reason.
		for (GLuint i = 0; i < mesh->mNumFaces; i++) {
			//For all the faces, append all indices to the index array
			auto face = mesh->mFaces[i];

			for (GLuint j = 0; j < face.mNumIndices; j++) {
				IndArray_.push_back(face.mIndices[j]);
			}
		}
		
		//UV coords are... hmmmmmm... interesting
		if (!(mesh->HasTextureCoords(0))) {
			//Nope
			throw std::runtime_error("Mesh has no tex coords! Coord progression error?");
		}
		TCArray_ = std::vector<Vertex2D>(
			&mesh->mTextureCoords[0][0],
			&mesh->mTextureCoords[0][mesh->mNumVertices - 1]
		);
	}

	Mesh::Mesh(fs::path filename) {
		const aiScene* scene = IOManager::sceneFromFile(filename);
			
		//For all meshes...
		for (GLuint i = 0; i < scene->mNumMeshes; i++) {
			//Append their data to this Mesh
			aiMesh* m = scene->mMeshes[i];
			appendMeshData(scene, m);
		}

		//Everything should be copied now, so we're done
	}

	Mesh::~Mesh() {
	}
}