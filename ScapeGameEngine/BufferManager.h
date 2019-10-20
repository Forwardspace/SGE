#pragma once
#include "stdheaders.h"

namespace sge {
	enum class BufferUsageType {
		STATIC = GL_STATIC_DRAW,
		DYNAMIC = GL_DYNAMIC_DRAW,
	};

	enum class BufferType {
		VBO,
		EAB,
		FBO,
	};

	//glVertexAttibPtr will be automatically called
	//For the following subtypes
	//Note: you can have more than 4 VBOs, of course,
	//just configure them manually
	enum BufferSubtype {
		VERTEX,
		TEXTURE,
		NORMAL,
		INDEX,
	};

	//Describes the data to passed to a buffer
	struct BufferDataDescriptor {
		BufferDataDescriptor(unsigned int size, void* data) : s(size), d(data) {}

		unsigned int s;
		void* d;
	};

	//A unique value describing a buffer
	struct BufferID {
		unsigned int id;	//Matches BufferGroup
		BufferType t;
		unsigned int subtype;
	};

	//Describes the target buffer and the usage of that buffer after its modification
	struct BufferTargetDescriptor {
		BufferTargetDescriptor() {}
		BufferTargetDescriptor(BufferID i, BufferUsageType bu) : id(i), usage(bu) {}

		BufferID id;
		BufferUsageType usage;
	};

	//Describes the buffer along with data needed to modify it
	struct BufferData {
		GLuint buffer;
		unsigned int usedBytes;
		unsigned int maxSizeBytes;
	};

	//Describes the position of appended data in the buffer
	struct BufferAppendResult {
		unsigned int start;
		unsigned int end;
		bool firstAppend;
	};

	class BufferManager {
	public:
		//Use this to get access to the required buffer
		static GLuint getBuffer(BufferID bd);

		//Use this to get access to a specific VAO
		//It will be created automatically if it doesn't
		//already exist
		static void bindVAO(unsigned int id);

		//Append new data to a buffer
		//The target buffer will be created automatically
		//if it doesn't already exist
		static BufferAppendResult appendToBuffer(BufferTargetDescriptor target, BufferDataDescriptor data);
		//Duplicate the data in the target buffer from dataStart to dataEnd
		//The target buffer will NOT be created automatically, as 
		//there would be no point in duplicating empty regions
		static BufferAppendResult appendToBuffer(
			BufferTargetDescriptor target,
			unsigned int dataStart,
			unsigned int dataEnd
		);

		BufferManager() = delete;	//Singleton
		~BufferManager() = delete;

	private:
		static std::map<BufferID, BufferData> buffers_;
		static std::map<unsigned int, GLuint> VAOs_;

		static GLuint currentlyBoundVAO_;
	};
}
