#pragma once
#include "stdheaders.h"
#include "Object.h"
#include "Mesh.h"
#include "Material.h"
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
		void setMaterial(Material* tex) { mat_ = tex; }

		MeshInVBOs mesh() { return objectMesh_; }

		void render();
		void setupVAO();

	protected:
		Material* mat_;
		MeshInVBOs objectMesh_;
	};
}