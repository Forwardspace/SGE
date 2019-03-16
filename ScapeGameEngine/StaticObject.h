#pragma once
#include "stdheaders.h"
#include "Object.h"
#include "Mesh.h"

namespace sge {
	class StaticObject : public Object {
	public:
		StaticObject();
		StaticObject(Mesh msh);
		~StaticObject();

		void render();
	
	protected:
		Mesh objectMesh;

		const ObjectType::Enum type_ = ObjectType::STATIC;
	};
}