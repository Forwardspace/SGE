#pragma once
#include "stdheaders.h"

namespace sge {
	//Matches ObjectType
	namespace VAOType {
		enum  Enum {
			STATIC,
			DYNAMIC,
			NONE_BOUND,
		};
	}

	namespace VBOType {
		enum  Enum {
			VERTEX,
			VERTEX2D,
			UV
		};
	}

	namespace FBOType {
		enum  Enum {
			POSITION,
			DIFFUSE,
			NORMAL,
			TEXCOORD
		};
	}

	class BufferManager {
	public:
		//Use this to get access to the required VAO
		//It will be instantiated on first use automatically.
		static GLuint VAO(VAOType::Enum type);
		//Use this to get access to the required VBO
		//It will be instantiated on first use automatically.
		static GLuint VBO(VBOType::Enum type);
		//Use this to get access to the required EAB (Element Array Buffer)
		//a.k.a. index buffer
		static GLuint EAB();
		//Use this for rendering to textures
		static GLuint FBO(FBOType::Enum type);
		
		BufferManager() = delete;	//Singleton
		~BufferManager() = delete;

	private:
		static std::map<int, GLuint> VAOs_;
		static std::map<int, GLuint> VBOs_;
		static GLuint EAB_;
		static std::map<int, GLuint> FBOs_;
	};
}
