#pragma once
#include "stdheaders.h"
#include "Object.h"
#include "Mesh.h"
#include "Texture.h"
#include "TextureManager.h"
#include "Renderer.h"
#include "ShaderManager.h"

namespace sge {
	class StaticObject : public Object {
	public:
		StaticObject();
		StaticObject(Mesh& msh);
		//Object from a file: loads the first mesh from the
		//specified file.
		StaticObject(fs::path filename);
		~StaticObject();

		void setMesh(MeshInVBOs& mesh) { objectMesh_ = mesh; }
		void setTexture(Texture& tex) { objectTexture_ = tex; useDefaultTexture = false; }

		MeshInVBOs mesh() { return objectMesh_; }
		Texture texture() { return objectTexture_; }

		void render();
		void setupVAO();

	protected:
		MeshInVBOs objectMesh_;
		Texture objectTexture_;
		bool useDefaultTexture = true;
	};
}