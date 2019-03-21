#pragma once
#include "stdheaders.h"

namespace sge {
	//Matches ObjectType
	namespace VAOType {
		enum Enum {
			STATIC,
			DYNAMIC,
			NONE_BOUND
		};
	}

	class BufferManager {
	public:
		//Use this to get access to the required VAO
		//It will be instantiated on first use automatically.
		static GLuint VAO(VAOType::Enum t);
		//Use this to get access to the required VBO
		//It will be instantiated on first use automatically.
		static GLuint VBO();
		//Use this to get access to the required EAB (Element Array Buffer)
		//a.k.a. index buffer
		static GLuint EAB();
		
		BufferManager() = delete;	//Singleton
		~BufferManager() = delete;

	private:
		static std::map<int, GLuint> VAOs_;
		static GLuint VBO_;
		static GLuint EAB_;
	};
}
