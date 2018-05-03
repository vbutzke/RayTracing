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

class mtl
{
public:
	mtl();
	mtl(string namep, GLfloat Nsp, GLfloat Nip, GLfloat dp, GLfloat Tfp[3], GLfloat illump, GLfloat Kap[3], GLfloat Kdp[3], GLfloat Ksp[3], string map_Kdp, int sharpnessp);
	string getName();
	GLfloat getNs();
	GLfloat getNi();
	GLfloat getD();
	GLfloat getIllum();
	GLfloat* getTf();
	GLfloat* getKa();
	GLfloat* getKd();
	GLfloat* getKs();
	int getSharpness();
	string getMap_Kd();
	~mtl();
	
private:
	string name;
	GLfloat Ns;
	GLfloat	Ni;
	GLfloat	d;
	GLfloat Tf[3];
	GLfloat illum;
	GLfloat Ka[3];
	GLfloat Kd[3];
	GLfloat Ks[3];
	int sharpness;
	string map_Kd;
};

