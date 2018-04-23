#pragma once
#include <GL/glew.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <assert.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "rhostring.hpp"
#include <fstream>

class textures
{
public:
	textures();
	GLuint createTexture(const char* path);
	~textures();

private:
	GLuint loadTexture();
	void generateMipmap(const char* path);
};

