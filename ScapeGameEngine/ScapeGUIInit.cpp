#include "ScapeGUIInit.h"
#include "TextureManager.h"
#include "UserInputManager.h"
#include "ParsedXML.h"

#include "ScapeGUITextures.h"

namespace sgeui {
	void initSGEUI(GLFWwindow* wind_, int w_, int h_) {
		wind = wind_;
		windW = w_;
		windH = h_;

		loadResources();
		makeShaders();
		setVertexPtrs();
	}

	const fs::path resourcesRoot = "gui\\resources";
	const fs::path resourceDefinitionsFilename = resourcesRoot / "resources.xml";

	std::map<int, sge::Texture*> textures;
	std::map<int, sge::PackedTexture*> packedTextures;
	Theme* defaultTheme;

	inline void assertNodeNotNull(rapidxml::xml_node<>* node, std::string nodeName) {
		if (!node) {
			throw std::runtime_error("Error: No root '" + nodeName + "' tag in XML resource definition file!");
		}
	}

	void loadThemes(rapidxml::xml_node<>* root) {
		auto themes = root->first_node("themes");
		assertNodeNotNull(themes, "themes");

		//Load all themes inide <theme> tags
		//example theme declaration: <theme name="my_theme">theme.png</theme>
		auto nextTheme = themes->first_node("theme");
		while (nextTheme) {
			if (nextTheme->first_attribute()->name() != std::string("name")) {
				throw std::runtime_error("Theme attribute name is not 'name'!");
			}
			std::string name = nextTheme->first_attribute()->value();

			ThemeTextureResource* rsc = new ThemeTextureResource(resourcesRoot/nextTheme->value(), name);
			TextureManager::add(rsc);

			nextTheme = nextTheme->next_sibling("theme");
		}

		auto defaultThemeNode = themes->first_node("defaultTheme");

		if (!defaultThemeNode) {
			throw std::runtime_error("Error: no defaultTheme tag in XML resource definition file!");
		}

		defaultTheme = TextureManager::getTheme(defaultThemeNode->value());
	}

	void loadTextures(rapidxml::xml_node<>* root) {
		auto textures = root->first_node("textures");
		assertNodeNotNull(textures, "textures");

		//Load the rest of the required textures similarly
		auto nextTexture = textures->first_node("texture");
		while (nextTexture) {
			//First check for the required name attribute
			if (!nextTexture->first_attribute("name")) {
				throw std::runtime_error("No attribute 'name' in texture: XML resource definition file!");
			}
			std::string name = nextTexture->first_attribute("name")->value();

			//Next, for the optional packed attribute (if value == "true", the texture is a packed one)
			if (
				nextTexture->first_attribute("packed") != nullptr &&
				nextTexture->first_attribute("packed")->value() == std::string("true")
			) {

				sge::PackedTexture* tex = new sge::PackedTexture(resourcesRoot/nextTexture->value());
				StaticTextureResource* rsc = new StaticTextureResource(tex, name);

				TextureManager::add(rsc);
			}
			else {
				//Nope, just a regular texture

				sge::Texture* tex = new sge::Texture(resourcesRoot/nextTexture->value());
				StaticTextureResource* rsc = new StaticTextureResource(tex, name);

				TextureManager::add(rsc);
			}

			nextTexture = nextTexture->next_sibling("texture");
		}
	}

	void loadResources() {
		sge::ParsedXML rsc(resourceDefinitionsFilename);

		auto root = rsc["resources"];
		assertNodeNotNull(root, "resources");

		loadThemes(root);
		loadTextures(root);
	}

	void terminate() {
		delete GUIShaderProgram;
	}

	const fs::path quadVSShFilename = "gui\\shaders\\quadvs.shader";
	const fs::path quadFSShFilename = "gui\\shaders\\quadfs.shader";

	void makeShaders() {
		sge::VertexShader quadVS(quadVSShFilename);
		sge::FragmentShader quadFS(quadFSShFilename);

		sge::ShaderProgram* quadShader = new sge::ShaderProgram({ quadVS, quadFS });
		GUIShaderProgram = quadShader;
	}

	GLuint buffs[3];	//vertex, texCoord and index buffers
	void setVertexPtrs() {
		sge::BufferManager::bindVAO(SGEUI_BUFFER_ID);

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

		//Note: do not use sge::BufferManager as we are not batching meshes together;
		//create everything manually once and store it in the VAO

		glGenBuffers(3, buffs);

		//Configure the vertex buffer to accept 2d coordinates
		glBindBuffer(GL_ARRAY_BUFFER, buffs[0]);
		glVertexAttribPointer(0, 2 /* <- The important part */, GL_FLOAT, GL_FALSE, 0, (void*)0);

		//The texture coordinate array is similar
		glBindBuffer(GL_ARRAY_BUFFER, buffs[1]);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

		//While we're here, bind the element array buffer
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffs[2]);

		//The buffer data is supplied in the render() function, for now
		glBindVertexArray(0);
	}

	void updateMouseDelta() {
		static int prevX = 0, prevY = 0;
		int mouseX = sge::UserInputManager::mouseX();
		int mouseY = sge::UserInputManager::mouseY();

		mouseDeltaX = mouseX - prevX;
		mouseDeltaY = mouseY - prevY;

		prevX = mouseX;
		prevY = mouseY;
	}

	int mouseDeltaX = 0, mouseDeltaY = 0;

	GLFWwindow* wind;
	int windW, windH;
	sge::ShaderProgram* GUIShaderProgram;
}