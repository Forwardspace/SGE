#include "InstancedStaticObject.h"
#include "BufferManager.h"
#include "ShaderManager.h"
#include "TextureManager.h"

#include "VertexShader.h"
#include "FragmentShader.h"
#include "ShaderProgram.h"

#include "Renderer.h"

#include <future>

#ifndef SGE_INDEX_TYPE
#define SGE_INDEX_TYPE GL_UNSIGNED_INT
#endif

#define MVP_ATTRIB_INDEX_START 2
#define MVP_ATTRIB_INDEX_END 5

namespace sge {
	const fs::path vInstancedShaderPath = ".\\shaders\\vsIndexed.shader";
	const fs::path fInstancedShaderPath = ".\\shaders\\fsIndexed.shader";

	ShaderProgram* instancedShader = nullptr;

	void InstancedStaticObject::render() {
		if (!renderObject) {
			return;
		}

		if (instances_.size() == 0) {
			return;
		}

		glGetError();

		//First get the global model-view-projection matrix
		//auto MVP = getMVP();

		//Get the MVPs of all instances and bind them to instance attributes
		bindInstanceMVPs();

		//Bind the material for all instances (and the shader, if
		//it hasn't been specified
		ShaderManager::setActive(*instancedShader);
		if (mat_) {
			mat_->activate();
		}
		else {
			defaultMaterial.activate();
		}

		////The correct VAO should already be bound

		glDrawElementsInstancedBaseVertex(
			GL_TRIANGLES,
			(GLsizei)(objectMesh_.nIndices),
			SGE_INDEX_TYPE,
			(void*)objectMesh_.indStart,
			(GLsizei)instances_.size(),
			objectMesh_.baseVtx
		);

		auto err = glGetError();
		if (err) {
			std::cout
				<< "glGetError() returned non-zero in InstancedStaticObject::render(): "
				<< err << "!" << std::endl;
		}
	}

	void matrixAttributeColumn(int c, ObjectType type) {
		glEnableVertexAttribArray(c);

		auto buffer = BufferManager::getBuffer(
			{ (unsigned int)type, BufferType::VBO, (unsigned int)BufferSubtype::INDEX + c }
		);
		glBindBuffer(GL_ARRAY_BUFFER, buffer);
		glVertexAttribPointer(c, 4, GL_FLOAT, GL_FALSE, 0, 0);

		//Turn it from a per-vertex attribute to a per-instance one
		glVertexAttribDivisor(c, 1);
	}

	InstancedStaticObject::InstancedStaticObject(fs::path filename, int numInstances, std::function<void(StaticObjectInstance&)> t) {
		type_ = ObjectType::INSTANCED_STATIC;

		Mesh m(filename);
		objectMesh_ = m.moveToVBOs({ { (unsigned int)type_, (BufferType)0, 0 }, BufferUsageType::STATIC });

		//For each instance, transform it according to t and add it
		for (int i = 0; i < numInstances; i++) {
			StaticObjectInstance* instance = new StaticObjectInstance();
			t(*instance);

			instances_.push_back(instance);
			appendInstanceData(instance->getMVP());
		}

		Renderer::registerObject(this);
	}

	InstancedStaticObject::InstancedStaticObject(Mesh& m, int numInstances, std::function<void(StaticObjectInstance&)> t) {
		type_ = ObjectType::INSTANCED_STATIC;

		objectMesh_ = m.moveToVBOs({ { (unsigned int)type_, (BufferType)0, 0 }, BufferUsageType::STATIC });

		//For each instance, transform it according to t and add it
		for (int i = 0; i < numInstances; i++) {
			StaticObjectInstance* instance = new StaticObjectInstance();
			t(*instance);

			instances_.push_back(instance);
			appendInstanceData(instance->getMVP());
		}

		Renderer::registerObject(this);
	}

	InstancedStaticObject::InstancedStaticObject() {
		type_ = ObjectType::INSTANCED_STATIC;
		Renderer::registerObject(this);
	}

	InstancedStaticObject::~InstancedStaticObject() {
		for (auto inst : instances_) {
			delete inst;
		}
	}

	void InstancedStaticObject::setupVAO() {
		glGetError();

		BufferManager::bindVAO((unsigned int)type_);

		//Make sure the VBOs are created
		BufferManager::getBuffer({ (unsigned int)type_, BufferType::VBO, BufferSubtype::VERTEX });
		BufferManager::getBuffer({ (unsigned int)type_, BufferType::VBO, BufferSubtype::TEXTURE });

		//Create a buffer for per-instance storage of matrices
		//This requires 4 attributes (one per matrix column)
		for (int i = MVP_ATTRIB_INDEX_START; i <= MVP_ATTRIB_INDEX_END; i++) {
			matrixAttributeColumn(i, type_);
		}

		//Also make sure the index buffer is created as well
		glBindBuffer(
			GL_ELEMENT_ARRAY_BUFFER,
			BufferManager::getBuffer({ (unsigned int)type_, BufferType::EAB, BufferSubtype::INDEX })
		);

		//Setup the shaders used for instanced objects
		VertexShader vtx(vInstancedShaderPath);
		FragmentShader fgm(fInstancedShaderPath);
		instancedShader = new ShaderProgram({ vtx, fgm });

		auto b = glGetError();
	}

	void InstancedStaticObject::attachInstance(StaticObjectInstance& instance) {
		instances_.push_back(&instance);

		auto MVP = instance.getMVP();
		appendInstanceData(MVP);
	}

	void InstancedStaticObject::removeInstance(StaticObjectInstance& instance) {
		instances_.erase(std::find(instances_.begin(), instances_.end(), &instance));
	}

	inline GLfloat* mapMatrixColumnVBOWrite(ObjectType o, int c) {
		glBindBuffer(
			GL_COPY_WRITE_BUFFER,
			BufferManager::getBuffer({ (GLuint)o, BufferType::VBO, (unsigned int)BufferSubtype::INDEX + c })
		);
		return (GLfloat*)glMapBuffer(GL_COPY_WRITE_BUFFER, GL_WRITE_ONLY);
	}

	inline void unmapMatrixColumnVBO(ObjectType o, int c) {
		glUnmapNamedBuffer(BufferManager::getBuffer(
			{ (GLuint)o, BufferType::VBO, (unsigned int)BufferSubtype::INDEX + c }
		));
	}

	inline void memcpyMatrixRow(void* dest, void* src) {
		memcpy_s(
			dest,
			sizeof(GLfloat) * 4,
			src,
			sizeof(GLfloat) * 4
		);
	}

	//ToDo: multithread
	void InstancedStaticObject::transformInstances(std::function<void(StaticObjectInstance&)> transformation) {
		if (transformation) {
			for (auto& instance : instances_) {
				transformation(*instance);
			}
		}
	}

	void InstancedStaticObject::transformInstancesRange(int startIndex, int endIndex, std::function<void(StaticObjectInstance&)> transformation) {
		if (transformation) {
			for (int i = startIndex; i < endIndex && i < instances_.size(); i++) {
				transformation(*instances_[i]);
			}
		}
	}

	//ToDo: multithread the MVP-getting part of this function
	//Updates and maps MVPs of all instances to 4 attributes
	//each representing one matrix column
	void InstancedStaticObject::bindInstanceMVPs() {
		//First map the 4 VBOs representing a 4 by 4 matrix (attributes 2-5)
		GLfloat* pMatrixC1 = mapMatrixColumnVBOWrite(type_, MVP_ATTRIB_INDEX_START);
		GLfloat* pMatrixC2 = mapMatrixColumnVBOWrite(type_, MVP_ATTRIB_INDEX_START + 1);
		GLfloat* pMatrixC3 = mapMatrixColumnVBOWrite(type_, MVP_ATTRIB_INDEX_START + 2);
		GLfloat* pMatrixC4 = mapMatrixColumnVBOWrite(type_, MVP_ATTRIB_INDEX_START + 3);

		int instanceNumber = 0;
		//Either the projection or view matrix has been updated
		//Recalculate all MVP matrices

		for (auto instance : instances_) {
			glm::mat4 mat = instance->getMVP();

			if (Renderer::projOrViewJustUpdated() || instance->transformJustUpdated) {
				//Copy the 4 matrix rows row-by-row
				unsigned int offset = 4 * instanceNumber;

				memcpyMatrixRow(pMatrixC1 + offset, &mat[0][0]);
				memcpyMatrixRow(pMatrixC2 + offset, &mat[1][0]);
				memcpyMatrixRow(pMatrixC3 + offset, &mat[2][0]);
				memcpyMatrixRow(pMatrixC4 + offset, &mat[3][0]);
			}

			//else: The transform was the same as before; don't rewrite it
			instanceNumber++;
		}

		//Unmap all buffers
		unmapMatrixColumnVBO(type_, MVP_ATTRIB_INDEX_START);
		unmapMatrixColumnVBO(type_, MVP_ATTRIB_INDEX_START + 1);
		unmapMatrixColumnVBO(type_, MVP_ATTRIB_INDEX_START + 2);
		unmapMatrixColumnVBO(type_, MVP_ATTRIB_INDEX_START + 3);
	}

	inline void appendMatColToAttrib(void* col, ObjectType o, int c) {
		BufferManager::appendToBuffer(
			{ { (GLuint)o, BufferType::VBO, (GLuint)BufferSubtype::INDEX + c }, BufferUsageType::STATIC },
			{ sizeof(GLfloat) * 4, col }
		);
	}

	void InstancedStaticObject::appendInstanceData(glm::mat4 MVP) {
		//Append the instance MVP to the per-instance matrix VBOs
		appendMatColToAttrib(&MVP[0][0], type_, MVP_ATTRIB_INDEX_START);
		appendMatColToAttrib(&MVP[1][0], type_, MVP_ATTRIB_INDEX_START + 1);
		appendMatColToAttrib(&MVP[2][0], type_, MVP_ATTRIB_INDEX_START + 2);
		appendMatColToAttrib(&MVP[3][0], type_, MVP_ATTRIB_INDEX_START + 3);
	}
}