#pragma once
#include "stdheaders.h"
#include "Object.h"
#include "Mesh.h"

namespace sge {
	class StaticObject : protected Object {
	public:
		StaticObject();
		~StaticObject();

		void render();
	
	protected:
		Mesh objectMesh;

		const ObjectType::Enum type_ = ObjectType::STATIC;
	};
}