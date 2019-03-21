#include "StaticObject.h"

#ifndef SGE_INDEX_TYPE
#define SGE_INDEX_TYPE GL_UNSIGNED_INT
#endif

namespace sge {
	StaticObject::StaticObject() {
	}

	StaticObject::StaticObject(Mesh msh) {
		objectMesh = msh;
	}

	StaticObject::~StaticObject() {
	}

	void StaticObject::render() {
		auto err = glGetError();

		//Give the raw vertices 
		glBufferData(
			GL_ARRAY_BUFFER,
			objectMesh.VertArrayPtr()->size() * sizeof(Vertex3D),
			objectMesh.VertArrayPtr()->data(),
			GL_STATIC_DRAW
		);

		//Give the indices used to draw said raw vertices
		glBufferData(
			GL_ELEMENT_ARRAY_BUFFER,
			objectMesh.IndArrayPtr()->size() * sizeof(SGE_INDEX_TYPE),
			objectMesh.IndArrayPtr()->data(),
			GL_STATIC_DRAW
		);

		

		//Finally, tell OpenGL to draw the indices (the last argument is the data offset from the beginning of
		//the element buffer, 0 in our case)
		glDrawElements(GL_TRIANGLES, (GLsizei)(objectMesh.IndArrayPtr()->size()), SGE_INDEX_TYPE, (void*)0);
		err = glGetError();
	}
}