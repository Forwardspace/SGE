#pragma once
#include "stdheaders.h"
#include "Object.h"
#include "Mesh.h"
#include "Renderer.h"
#include "ShaderManager.h"

namespace sge {
	class StaticObject : public Object {
	public:
		StaticObject();
		StaticObject(Mesh msh);
		~StaticObject();

		void render();
	
	protected:
		glm::mat4x4 getMVP();
		void clampAngles();
		void updateModelMatrix();

		Mesh objectMesh_;

		const ObjectType::Enum type_ = ObjectType::STATIC;
	};
}