#pragma once
#ifndef SCENEREADER_H
#define SCENEHANDLER_H
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
#include "mesh.h"
#include "model.h"
#include "scene.h"

#include "SceneHandler.h"
class SceneReader :
	public SceneHandler
{
public:
	SceneReader();
	scene readConfigFile(string filename, model* modelObj);
	void read(string fileName, model* modelObj);
	void readMTL(string fileName, model* modelObj);
	~SceneReader();

private:
	bool isTransformationContinuous(string transformation);
};
#endif
