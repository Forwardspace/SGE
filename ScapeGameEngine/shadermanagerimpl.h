#pragma once
//#include "ShaderManager.h"

namespace sge {
	//Returns the location of a uniform with name "name"
	//Returns zero if the uniform cannot be found or 
	//no shader is bound
	inline GLint getUniformLoc(std::string name) {
		auto currShader = ShaderManager::boundShader_;
		if (!currShader) {
			return 0;
		}

		GLint loc = glGetUniformLocation(currShader->handle(), name.c_str());
		
		return loc;
	}

	template <typename T>
	inline bool ShaderManager::bindUniform(std::string name, T& value) {
		std::cout << "ShaderManager::bindUniform(): no specialization was found!" << std::endl;
		//No specialization was found: fail silently
		return false;
	}

	//Basic types

	template <>
	inline bool ShaderManager::bindUniform<GLfloat>(std::string name, GLfloat& value) {
		auto location = getUniformLoc(name);
		if (location < 0) {
			return false;
		}

		glUniform1f(location, value);
		return true;
	}

	template <>
	inline bool ShaderManager::bindUniform<GLint>(std::string name, GLint& value) {
		auto location = getUniformLoc(name);
		if (!location) {
			return false;
		}
		glUniform1i(location, value);
		return true;
	}

	template <>
	inline bool ShaderManager::bindUniform<GLuint>(std::string name, GLuint& value) {
		auto location = getUniformLoc(name);
		if (!location) {
			return false;
		}
		glUniform1ui(location, value);
		return true;
	}

	//Complex types

	//Vectors
	template <>
	inline bool ShaderManager::bindUniform<glm::vec2>(std::string name, glm::vec2& value) {
		auto location = getUniformLoc(name);
		if (!location) {
			return false;
		}
		glUniform2f(location, value[0], value[1]);
		return true;
	}
	template <>
	inline bool ShaderManager::bindUniform<glm::vec3>(std::string name, glm::vec3& value) {
		auto location = getUniformLoc(name);
		if (!location) {
			return false;
		}
		glUniform3f(location, value[0], value[1], value[2]);
		return true;
	}
	template <>
	inline bool ShaderManager::bindUniform<glm::vec4>(std::string name, glm::vec4& value) {
		auto location = getUniformLoc(name);
		if (!location) {
			return false;
		}
		glUniform4f(location, value[0], value[1], value[2], value[3]);
		return true;
	}

	//Matrices
	template <>
	inline bool ShaderManager::bindUniform<glm::mat2>(std::string name, glm::mat2& value) {
		auto location = getUniformLoc(name);
		if (!location) {
			return false;
		}
		glUniformMatrix2fv(location, 1, false, &value[0][0]);
		return true;
	}
	template <>
	inline bool ShaderManager::bindUniform<glm::mat3>(std::string name, glm::mat3& value) {
		auto location = getUniformLoc(name);
		if (!location) {
			return false;
		}
		glUniformMatrix3fv(location, 1, false, &value[0][0]);
		return true;
	}
	template <>
	inline bool ShaderManager::bindUniform<glm::mat4>(std::string name, glm::mat4& value) {
		auto location = getUniformLoc(name);
		if (!location) {
			return false;
		}
		glUniformMatrix4fv(location, 1, false, &value[0][0]);
		return true;
	}
}