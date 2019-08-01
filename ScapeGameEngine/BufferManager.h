#pragma once
#include "stdheaders.h"

namespace sge {
	//Matches ObjectType
	enum class VAOType {
		STATIC,
		DYNAMIC,
		INSTANCED,
		NONE_BOUND,
		LAST_ITEM
	};

	enum class VBOType {
		VERTEX,
		VERTEX2D,
		UV,
		LAST_ITEM
	};

	enum class FBOType {
		POSITION,
		DIFFUSE,
		NORMAL,
		TEXCOORD,
		LAST_ITEM
	};

	class BufferManager {
	public:
		//Use this to get access to the required VAO
		//It will be instantiated on first use automatically.
		static GLuint VAO(VAOType type);
		//Use this to get access to the required VBO
		//It will be instantiated on first use automatically.
		static GLuint VBO(VBOType type);
		//Use this to get access to the required EAB (Element Array Buffer)
		//a.k.a. index buffer
		static GLuint EAB();
		//Use this for rendering to textures
		static GLuint FBO(FBOType type);
		
		BufferManager() = delete;	//Singleton
		~BufferManager() = delete;

	private:
		static std::map<VAOType, GLuint> VAOs_;
		static std::map<VBOType, GLuint> VBOs_;
		static GLuint EAB_;
		static std::map<FBOType, GLuint> FBOs_;
	};
}
