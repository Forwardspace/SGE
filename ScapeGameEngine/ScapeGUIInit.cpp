#include "ScapeGUIInit.h"
#include "TextureManager.h"

namespace sgeui {
	void initSGEUI(GLFWwindow* wind_, int w_, int h_) {
		wind = wind_;
		windW = w_;
		windH = h_;

		makeUIBase();
	}

	void makeUIBase() {
		loadResources();
		makeShaders();
	}

	const fs::path resourcesRoot = "gui\\resources";
	const fs::path resourceDefinitionsFilename = resourcesRoot / "resources.csv";

	std::map<int, sge::Texture*> textures;
	std::map<int, sge::PackedTexture*> packedTextures;
	int defaultTheme;

	//Load the window themes
	//(loop over the rest until END_THEMES is encountered)
	void loadThemes(int &i, std::vector<std::string> &rDef) {
		for (i++; i < rDef.size(); i++) {
			if (rDef[i] == "END_THEMES") {
				if (textures.size() == 0) {
					throw std::runtime_error("Invalid GUI Resource Definition file (themeTextures empty)!");
				}
				return;
			}

			sge::Texture* temp = new sge::Texture(resourcesRoot / rDef[i]);
			textures[std::stoi(rDef[++i])] = temp;
		}
	}

	void loadtextures(int &i, std::vector<std::string>& rDef) {
		for (i++; i < rDef.size(); i++) {
			if (rDef[i] == "END_ADDITIONAL_TEXTURES") {
				if (textures.size() == 0 && packedTextures.size() == 0) {
					throw std::runtime_error("Invalid GUI Resource Definition file (textures empty)");
				}
				return;
			}
			else if (rDef[i] == "PACKED") {
				//Contains multiple textures in one file
				i++;
				sge::PackedTexture* temp = new sge::PackedTexture(resourcesRoot / rDef[i]);
				packedTextures[std::stoi(rDef[++i])] = temp;
			}
			else {
				sge::Texture* temp = new sge::Texture(resourcesRoot / rDef[i]);
				textures[std::stoi(rDef[++i])] = temp;
			}
		}
	}

	void loadResources() {
		std::vector<std::string> rDef = sge::IOManager::stringVecFromCSV(resourceDefinitionsFilename);

		if (rDef.size() == 0) {
			throw std::runtime_error("rDef size 0! rTFM > 0!");
		}

		for (int i = 0; i < rDef.size(); i++) {
			if (rDef[i] == "THEMES") {
				loadThemes(i, rDef);
			}
			else if (rDef[i] == "DEFAULT_THEME") {
				i++;
				defaultTheme = std::stoi(rDef[i]);
			}
			else if (rDef[i] == "ADDITIONAL_TEXTURES") {
				loadtextures(i, rDef);
			}
		}
	}

	void terminate() {
		for (auto& pair : textures) {
			//Ignore the key, delete the value
			delete pair.second;
		}
		for (auto& pair : packedTextures) {
			delete pair.second;
		}
	}

	const fs::path quadVSShFilename = "gui\\shaders\\quadvs.shader";
	const fs::path quadFSShFilename = "gui\\shaders\\quadfs.shader";

	void makeShaders() {
		sge::VertexShader quadVS(quadVSShFilename);
		sge::FragmentShader quadFS(quadFSShFilename);

		sge::ShaderProgram quadShader({ quadVS, quadFS });
		GUIShaderProgram = quadShader;
	}

	void setVertexPtrs() {
		//Just configure the VBO to accept 2D coordinates (instead of 3D)
		glBindBuffer(GL_ARRAY_BUFFER, sge::BufferManager::VBO(sge::VBOType::VERTEX2D));
		glVertexAttribPointer(0, 2 /* <- The important part */, GL_FLOAT, GL_FALSE, 0, (void*)0);
	}

	GLFWwindow* wind;
	int windW, windH;
	sge::ShaderProgram GUIShaderProgram;
}