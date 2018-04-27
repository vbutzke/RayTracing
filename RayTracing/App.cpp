//*----------------------
//Vitória Butzke Piccoli
//----------------------*

#include <iostream>
#include <string>
#include <algorithm>
#include <assert.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"
#include "rhostring.hpp"
#include "SceneReader.h"
#include <SOIL.h>
#include "textures.h"

using namespace std;

//SceneWriter writer;
//SceneReader reader;

int main() {

	model modelObj;
	SceneReader reader;
	scene scene = reader.readConfigFile("configCena.txt", &modelObj);
	vector<obj> objects = scene.getObjects();
	int count = objects.size();

	for (int i = 0; i < count; i++) {
		reader.read(objects[i].getName(), &modelObj);
		reader.readMTL(objects[i].getMTLname(), &modelObj);
	}

	modelObj.draw(scene);

	modelObj.terminate();
	glfwTerminate();
	return 0;
}