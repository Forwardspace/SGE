#pragma once

#define NOMINMAX

#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <utility>
#include <array>
#include <queue>
#include <stack>
#include <functional>
#include <initializer_list>
#include <filesystem>

namespace fs = std::experimental::filesystem;

#include <cmath>

//GL-related
#define GLFW_INCLUDE_NONE
#include <GLFW\glfw3.h>
#include <glad\glad.h>

//GLM
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

//DevIL
#include <IL\il.h>
#include <IL\ilu.h>
#include <IL\ilut.h>

//Assimp
#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>