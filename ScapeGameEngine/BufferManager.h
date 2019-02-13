#pragma once
#include "stdheaders.h"

namespace sge {
	enum VAOType {
		STATIC = 0,
		DYNAMIC = 1,
		NONE_BOUND = -1
	};

	class BufferManager {
	public:
		//Use this to get access to the required VAO
		//It will be instantiated on first use automatically.
		GLuint VAO(VAOType t);
		//Use this to get access to the required VBO
		//It will be instantiated on first use automatically.
		GLuint VBO();

		BufferManager() = delete;	//Singleton
		~BufferManager() = delete;
	
	private:
		std::map<int, GLuint> VAOs_;
		GLuint VBO_ = NULL;
	};
}
