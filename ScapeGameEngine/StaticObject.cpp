#include "StaticObject.h"
#include "BufferManager.h"

#ifndef SGE_INDEX_TYPE
#define SGE_INDEX_TYPE GL_UNSIGNED_INT
#endif

namespace sge {
	const fs::path vStaticShaderPath = ".\\shaders\\vs.shader";
	const fs::path fStaticShaderPath = ".\\shaders\\fs.shader";

	ShaderProgram* staticShader;

	StaticObject::StaticObject(Mesh& msh) {
		type_ = ObjectType::STATIC;

		Renderer::registerObject(this);

		BufferTargetDescriptor td(BufferID{ (unsigned int)type_, BufferType::VBO, 0 }, BufferUsageType::STATIC);
		objectMesh_ = msh.moveToVBOs(td);
	}

	StaticObject::StaticObject(fs::path filename) {
		type_ = ObjectType::STATIC;

		Renderer::registerObject(this);
		auto mesh = Mesh(filename);

		BufferTargetDescriptor td(BufferID{ (unsigned int)type_, BufferType::VBO, 0 }, BufferUsageType::STATIC);
		objectMesh_ = mesh.moveToVBOs(td);
	}

	StaticObject::~StaticObject() {
		Renderer::removeObject(this);
	}

	void StaticObject::render() {
		if (!renderObject) {
			return;
		}

		glGetError();

		//First get the model-view-projection matrix
		auto MVP = getMVP();

		//Bind the assigned material (and the shader)
		ShaderManager::setActive(*staticShader);
		if (mat_) {
			mat_->activate();
		}
		else {
			//No material bound, use the default one
			defaultMaterial.activate();
		}

		//Hand it over to the shader
		ShaderManager::bindUniform<glm::mat4>("MVP", MVP);

		//The correct VAO should already be bound

		glDrawElementsBaseVertex(
			GL_TRIANGLES,
			(GLsizei)(objectMesh_.nIndices),
			SGE_INDEX_TYPE,
			(void*)objectMesh_.indStart,
			objectMesh_.baseVtx
		);

		auto err = glGetError();
		if (err) {
			std::cout << "glGetError() returned non-zero in StaticObject::render(): " << err << "!" << std::endl;
		}
	}

	void StaticObject::setupVAO() {
		BufferManager::bindVAO((unsigned int)type_);
		//Make sure the VBOs are created
		BufferManager::getBuffer({ (unsigned int)type_, BufferType::VBO, BufferSubtype::VERTEX });
		BufferManager::getBuffer({ (unsigned int)type_, BufferType::VBO, BufferSubtype::TEXTURE });

		//Also make sure the index buffer is created as well
		glBindBuffer(
			GL_ELEMENT_ARRAY_BUFFER,
			BufferManager::getBuffer({ (unsigned int)type_, BufferType::EAB, BufferSubtype::INDEX })
		);

		//Load the shaders for this object group
		VertexShader vStatic(vStaticShaderPath);
		FragmentShader fStatic(fStaticShaderPath);
		staticShader = new ShaderProgram({ vStatic, fStatic });
	}
}