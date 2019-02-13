#pragma once
#include "stdheaders.h"
#include "Object.h"
#include "Mesh.h"

namespace sge {
	class StaticObject : protected Object {
	public:
		StaticObject();
		~StaticObject();
	
	protected:
		Mesh objectMesh;
	};
}