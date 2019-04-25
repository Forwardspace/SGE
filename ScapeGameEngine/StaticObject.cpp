#include "StaticObject.h"

#ifndef SGE_INDEX_TYPE
#define SGE_INDEX_TYPE GL_UNSIGNED_INT
#endif

namespace sge {
	StaticObject::StaticObject() {
	}

	StaticObject::StaticObject(Mesh& msh) {
		objectMesh_ = &msh;
	}

	StaticObject::~StaticObject() {
	}

	void StaticObject::clampAngles() {
		rotX_ = (float)fmod(rotX_, 360);
		rotY_ = (float)fmod(rotY_, 360);
		rotZ_ = (float)fmod(rotZ_, 360);
	}

	void StaticObject::updateModelMatrix() {
		clampAngles();

		//Generate the rotation matrix by succesive rotations on every axis.
		glm::mat4x4 rotMat = glm::mat4x4(1);
		rotMat = glm::rotate(rotMat, rotX_, glm::vec3(1, 0, 0));
		rotMat = glm::rotate(rotMat, rotY_, glm::vec3(0, 1, 0));
		rotMat = glm::rotate(rotMat, rotZ_, glm::vec3(0, 0, 1));

		glm::mat4x4 transMat = glm::translate(glm::mat4x4(1), glm::vec3(posX_, posY_, posZ_));
		glm::mat4x4 scaleMat = glm::scale(glm::mat4x4(1), glm::vec3(scaleX_, scaleY_, scaleZ_));

		cachedMatrix_ = transMat * rotMat * scaleMat;
	}

	glm::mat4x4 StaticObject::getMVP() {
		if (transformNeedsUpdating) {
			transformNeedsUpdating = false;
			updateModelMatrix();
		}

		glm::mat4x4 view = Renderer::currentCamera()->viewMatrix();
		glm::mat4x4 projection = Renderer::projectionMatrix();

		return projection * view * cachedMatrix_;
	}

	void StaticObject::render() {
		//First get the model-view-projection matrix
		auto MVP = getMVP();

		//Hand it over to the shader
		ShaderManager::bindMVP(MVP);
		ShaderManager::bindSamplerTexUnit(0);

		auto e1 = glGetError();

		//Bind the assigned texture for the shader
		TextureManager::bindTexture(objectTexture_);

		glBindBuffer(GL_ARRAY_BUFFER, BufferManager::VBO(VBOType::UV));
		//The UV data
		glBufferData(
			GL_ARRAY_BUFFER,
			objectMesh_->TexCoordArrayPtr()->size() * sizeof(Vertex2D),
			objectMesh_->TexCoordArrayPtr()->data(),
			GL_STATIC_DRAW
		);

		glBindBuffer(GL_ARRAY_BUFFER, BufferManager::VBO(VBOType::VERTEX));
		//Give the raw vertices 
		glBufferData(
			GL_ARRAY_BUFFER,
			objectMesh_->VertArrayPtr()->size() * sizeof(Vertex3D),
			objectMesh_->VertArrayPtr()->data(),
			GL_STATIC_DRAW
		);

		auto e2 = glGetError();

		//Give the indices used to draw said raw vertices
		glBufferData(
			GL_ELEMENT_ARRAY_BUFFER,
			objectMesh_->IndArrayPtr()->size() * sizeof(SGE_INDEX_TYPE),
			objectMesh_->IndArrayPtr()->data(),
			GL_STATIC_DRAW
		);

		//Finally, tell OpenGL to draw the indices (the last argument is the data offset from the beginning of
		//the element buffer, 0 in our case)
		glDrawElements(GL_TRIANGLES, (GLsizei)(objectMesh_->IndArrayPtr()->size()), SGE_INDEX_TYPE, (void*)0);
	}
}