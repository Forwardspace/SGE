#pragma once

#define GLEW_STATIC
#define NOMINMAX

#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <queue>
#include <functional>
#include <initializer_list>

#include <cmath>

//GL-related
#include <GL\glew.h>
#include <GLFW\glfw3.h>
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