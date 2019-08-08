#include "BufferManager.h"

#define BUFFER_INITIAL_SIZE 30000	//30kB, enough for 10000 3D vertices

#define BUFFER_MIN_REALLOC_PREDICTION_TRESHOLD 3000
#define BUFFER_MAX_REALLOC_PREDICTION_TRESHOLD 30000000	//30MB, enough for reallocation prediction to be irrelevant

#define BUFFER_MULTITHREADING_THRESHOLD 10000

namespace sge {
	//Basically, compare two bufferIDs by treating them as one big number
	bool operator<(const BufferID& b1, const BufferID& b2) {
		if (b1.id < b2.id) {
			return true;
		}
		else if (b1.id > b2.id) {
			return false;
		}
		else {
			if (b1.t < b2.t) {
				return true;
			}
			else if (b2.t < b1.t) {
				return false;
			}
			else {
				if (b1.subtype < b2.subtype) {
					return true;
				}
				return false;
			}
		}
	}

	std::map<BufferID, BufferData> BufferManager::buffers_;
	std::map<unsigned int, GLuint> BufferManager::VAOs_;
	GLuint BufferManager::currentlyBoundVAO_ = 0;

	GLuint BufferManager::getBuffer(BufferID bd) {
		try {
			auto handle = buffers_.at(bd);

			return handle.buffer;
		}
		catch (std::out_of_range& exc) {
			//Create a new, empty buffer ('append' zero bytes to a new buffer)
			appendToBuffer({ bd, BufferUsageType::STATIC }, { 0, 0 });

			return buffers_.at(bd).buffer;
		}
	}

	void BufferManager::bindVAO(unsigned int id) {
		if (VAOs_[id] == NULL) {
			GLuint vao;
			glGenVertexArrays(1, &vao);

			VAOs_[id] = vao;
		}

		auto vao = VAOs_[id];

		if (currentlyBoundVAO_ != vao) {
			glBindVertexArray(VAOs_[id]);
		}
	}

	BufferData reallocateBuffer(GLuint buffer, unsigned int minSize, GLenum usage, unsigned int usedBytes) {
		unsigned int newSize = minSize;

		//Avoid very small reallocations
		if (minSize < BUFFER_MIN_REALLOC_PREDICTION_TRESHOLD) {
			newSize += BUFFER_MIN_REALLOC_PREDICTION_TRESHOLD;
		}
		else if (minSize < BUFFER_MAX_REALLOC_PREDICTION_TRESHOLD) {
			newSize += minSize / 3;
		}
		else {
			newSize += BUFFER_MAX_REALLOC_PREDICTION_TRESHOLD / 3;
		}

		//Generate a new, temporary, buffer
		GLuint tempBuffer;
		glGenBuffers(1, &tempBuffer);

		//Map the old one to gain access to its data
		glBindBuffer(GL_COPY_WRITE_BUFFER, buffer);
		auto* pOld = glMapBuffer(GL_ARRAY_BUFFER, GL_MAP_READ_BIT | GL_MAP_WRITE_BIT);

		//Fill the new one with the old one's data
		glBindBuffer(GL_COPY_READ_BUFFER, tempBuffer);
		glBufferData(GL_ARRAY_BUFFER, usedBytes, pOld, usage);

		glUnmapBuffer(GL_COPY_WRITE_BUFFER);

		//Resize the old one
		glBufferData(GL_COPY_WRITE_BUFFER, newSize, nullptr, usage);

		//Copy back the data to the old buffer
		glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, usedBytes);

		glBindBuffer(GL_COPY_READ_BUFFER, 0);
		glBindBuffer(GL_COPY_WRITE_BUFFER, 0);

		glDeleteBuffers(1, &tempBuffer);

		//The old buffer now retains the same ID and data, but is larger

		return { buffer, usedBytes, newSize };
	}

	void setupVertexAttribPtrs(BufferTargetDescriptor td, BufferData bd) {
		if (td.id.t == BufferType::VBO || td.id.subtype >= BufferSubtype::VERTEX || td.id.subtype <= BufferSubtype::TEXTURE) {
			glEnableVertexAttribArray(td.id.subtype);

			switch (td.id.subtype) {
			case BufferSubtype::VERTEX:
				//The buffer is already bound, just configure it
				glVertexAttribPointer(BufferSubtype::VERTEX, 3, GL_FLOAT, GL_FALSE, 0, 0);
				break;
			case BufferSubtype::TEXTURE:
				glVertexAttribPointer(BufferSubtype::TEXTURE, 2, GL_FLOAT, GL_FALSE, 0, 0);
				break;
			}
		}
		//If the buffer is not a VBO or not recognizable, ignore it
	}

	BufferAppendResult BufferManager::appendToBuffer(BufferTargetDescriptor target, BufferDataDescriptor data) {
		BufferData* handle;
		
		bool firstUse = false;

		try {
			handle = &buffers_.at(target.id);
		}
		catch (std::out_of_range& exc) {
			(void)exc;
			//The buffer does not exist, create it
			handle = &buffers_[target.id];

			firstUse = true;
			glGenBuffers(1, &handle->buffer);

			glBindBuffer(GL_ARRAY_BUFFER, handle->buffer);
			glBufferData(GL_ARRAY_BUFFER, BUFFER_INITIAL_SIZE, nullptr, (GLenum)target.usage);

			handle->maxSizeBytes = BUFFER_INITIAL_SIZE;
			handle->usedBytes = 0;

			setupVertexAttribPtrs(target, *handle);
		}

		if (handle->usedBytes + data.s >= handle->maxSizeBytes) {
			//The buffer seems too small to store the data supplied
			//Reallocate it to expand it
			BufferData bd = reallocateBuffer(
				handle->buffer,
				handle->usedBytes + data.s + 1,
				(GLenum)target.usage,
				handle->usedBytes
			);

			*handle = bd;
		}

		//Finally, map the buffer and append data to it (leave a byte of space just in case)
		auto bPtr = glMapNamedBufferRange(handle->buffer, handle->usedBytes, data.s + 1, GL_MAP_WRITE_BIT);
		if (!bPtr) {
			throw std::runtime_error("glMapNamedBufferRange() returned nullptr! thsIsACrtcalErr()");
		}
		memcpy_s(bPtr, data.s + 1, data.d, data.s);

		//Done, unmap it
		glUnmapNamedBuffer(handle->buffer);

		unsigned int start = handle->usedBytes;
		unsigned int end = handle->usedBytes + data.s;

		//Update the buffer data
		handle->usedBytes += data.s;

		return { start, end, firstUse };
	}
}