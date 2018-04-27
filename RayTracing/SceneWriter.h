#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <atlimage.h>
#include <iostream>
#include <string>

class SceneWriter
{
public:
	SceneWriter();
	std::string write(std::string path);
	std::string write(std::string path, GLuint height, GLuint width, unsigned char* pixels);
	~SceneWriter();
};

