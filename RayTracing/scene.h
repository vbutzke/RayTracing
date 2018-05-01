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
#include "obj.h"

class scene
{
public:
	scene();
	~scene();

	string getFileName();
	glm::vec3 getPositions();
	glm::vec3 getColors();
	glm::vec3 getObjectColors();
	glm::vec3 getUpVector();
	glm::vec3 getWhereToLook();
	glm::vec3 getEyeLine();
	glm::vec4 getProjection();
	glm::vec3 getRotation();
	float getAngle();
	glm::vec3 getTranslation();
	glm::vec3 getScale();
	vector<obj> getObjects();

	void setFileName(string nFileName);
	void setPositions(glm::vec3 nPos);
	void setColors(glm::vec3 nCol);
	void setObjectColors(glm::vec3 nObjCol);
	void setUpVector(glm::vec3 nUpVec);
	void setWhereToLook(glm::vec3 nLookAt);
	void setEyeLine(glm::vec3 nEyeLine);
	void setProjection(glm::vec4 nProj);
	void setRotation(glm::vec3 nRot);
	void setAngle(float nAngle);
	void setTranslation(glm::vec3 nTrans);
	void setScale(glm::vec3 nScale);
	void setObjects(vector<obj> objs);
	void addObject(obj object);

private:
	string fileName;

	//iluminação
	glm::vec3 positions;
	glm::vec3 colors;
	glm::vec3 objColors;

	//camera
	glm::vec3 upVector;
	glm::vec3 whereToLook;
	glm::vec3 eyeLine;

	//projeção
	glm::vec4 projection;

	//transformações
	glm::vec3 rotation;
	float angle;
	glm::vec3 translation;
	glm::vec3 scale;

	//objetos
	//obj* objects;
	vector<obj> objects;
};

