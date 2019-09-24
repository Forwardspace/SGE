#include "SkyboxTexture.h"
#include "ShaderProgram.h"
#include "ShaderManager.h"
#include "VertexShader.h"
#include "FragmentShader.h"

#include "BufferManager.h"

#define SKYBOX_BUFFER_ID 1001

namespace sge {
	//"Borrowed" from https://learnopengl.com/
	const float skyboxVertices[] = {
		// positions          
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f
	};

	ShaderProgram* skyboxShader = nullptr;

	const fs::path vSkyboxShader = ".\\shaders\\vsSkybox.shader";
	const fs::path fSkyboxShader = ".\\shaders\\fsSkybox.shader";

	void SkyboxTexture::initVAO() {
		BufferManager::bindVAO(SKYBOX_BUFFER_ID);

		VertexShader vs(vSkyboxShader);
		FragmentShader fs(fSkyboxShader);
		skyboxShader = new ShaderProgram({ vs, fs });

		ShaderManager::setActive(*skyboxShader);
		ShaderManager::bindTexSampler("diffuse", 0, *this, GL_TEXTURE_CUBE_MAP);

		//Init the buffer storing the cube vertices
		glBindBuffer(
			GL_ARRAY_BUFFER,
			BufferManager::getBuffer(BufferID { SKYBOX_BUFFER_ID, BufferType::VBO, BufferSubtype::VERTEX })
		);
		glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), skyboxVertices, GL_STATIC_DRAW);
	}

	//Do not move these around - these are in OpenGL's texture order
	const std::vector<std::string> extensions = {
		"rt", "lf",	//Right and left
		"up", "dn",	//Down and up
		"bk", "ft"	//Back and front
	};

	SkyboxTexture::SkyboxTexture(fs::path filename) {
		BufferManager::bindVAO(SKYBOX_BUFFER_ID);
		//Skybox textures are composed of 6 sides, i.e. 6 textures
		//They are stored in files in the format of <skybox_name>_<extension>.<image_extension>
		//where side is "dk", "bn", "up", ...

		//Base of the filename without the extension
		fs::path base = filename.parent_path() / filename.stem();

		//Create the base texture
		glGenTextures(1, &handle_);
		glBindTexture(GL_TEXTURE_CUBE_MAP, handle_);

		//Load all 6 sides of the cubemap
		try {
			int i = 0;
			for (auto& extension : extensions) {
				const std::string full = base.u8string() + "_" + extension + filename.extension().u8string();

				//Try to load this side
				bool success = ilLoadImage(full.c_str());
				if (!success) {
					throw std::runtime_error("ilLoadImage failed!");
				}

				success = ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
				if (!success) {
					throw std::runtime_error("ilConvertImage failed!");
				}

				//Flip the image because... OpenGL
				iluFlipImage();

				//Extract data from the image
				int w = ilGetInteger(IL_IMAGE_WIDTH);
				int h = ilGetInteger(IL_IMAGE_HEIGHT);

				auto data = ilGetData();

				glTexImage2D(
					GL_TEXTURE_CUBE_MAP_POSITIVE_X + (i++),
					0, GL_RGBA,
					w, h,
					0, GL_RGBA, GL_UNSIGNED_BYTE,
					data
				);
			}

			// Wrapping and filtering parameters for the whole skybox
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		}
		catch (std::runtime_error& e) {
			throw std::runtime_error("Unable to load one of 6 sides in a cubemap: " + std::string(e.what()));
		}

	}

	void SkyboxTexture::render(glm::mat4 VPmat) {
		if (!skyboxShader) {
			//This is the first time this function has been called.
			//Setup the shader and the buffer
			initVAO();
		}

		BufferManager::bindVAO(SKYBOX_BUFFER_ID);
		
		ShaderManager::setActive(*skyboxShader);
		ShaderManager::bindTexSampler("diffuse", 0, *this, GL_TEXTURE_CUBE_MAP);
		ShaderManager::bindUniform<glm::mat4>("VPmat", VPmat);

		//Draw 12 triangles (a cube) ignoring its size later
		glDepthMask(GL_FALSE);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glDepthMask(GL_TRUE);

		auto a = glGetError();
	}
}