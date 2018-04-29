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
#include "mtl.h"
#include "textures.h"
#include "Shader.h"

class mesh
{
public:
	mesh(string mtlNamep);
	void createMesh(vector<GLfloat> vObj, vector<GLfloat> vNormais, vector<GLfloat> vTexturas, vector<GLuint> iNormais, vector<GLuint> iObj, vector<GLuint> iTexturas);
	void bindMesh();
	int bindTexture(vector<mtl> mtls, Shader* shader);
	void draw(Shader* shader, int texture);
	string getMTLName();
	void terminate();
	vector<GLfloat> getVO();
	~mesh();

private:

	vector<GLfloat> vo;
	vector<GLfloat> vn;
	vector<GLfloat> vt;
	vector<GLuint> io;
	vector<GLuint> in;
	vector<GLuint> it;

	GLuint VAO;
	GLuint VBOv; //vertices
	GLuint VBOn; //normals
	GLuint VBOt; //textures
	GLuint EBOv; //vertices
	GLuint EBOn; //normals
	GLuint EBOt; //textures
	string mtlName;
};

