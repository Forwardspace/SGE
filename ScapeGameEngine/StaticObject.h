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
		StaticObject(std::string filename);
		~StaticObject();

		void setMesh(Mesh& mesh) { objectMesh_ = mesh; }
		void setTexture(Texture& tex) { objectTexture_ = tex; useDefaultTexture = false; }

		Mesh mesh() { return objectMesh_; }
		Texture texture() { return objectTexture_; }

		void render();
	
	protected:
		glm::mat4x4 getMVP();
		void clampAngles();
		void updateModelMatrix();

		Mesh objectMesh_;
		Texture objectTexture_;
		bool useDefaultTexture = true;

		const ObjectType::Enum type_ = ObjectType::STATIC;
	};
}