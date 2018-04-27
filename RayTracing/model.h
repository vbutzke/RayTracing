#pragma once

#include "mesh.h"
#include "mtl.h"
#include "Shader.h"
#include "scene.h"
#include "SceneWriter.h"
#include "SceneReader.h"

class model
{
public:
	model();
	void addMesh(mesh mesh);
	void addMTL(mtl mtl);
	void performMtlLightning(string mtlName, Shader* shader);
	void draw(scene scene);// GLFWwindow* window, GLuint WIDTH, GLuint HEIGHT, glm::vec3 eyeLine, scene scene);
	void terminate();
	glm::mat4 processInput(GLFWwindow* window, glm::vec3 eyeLine);
	static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	GLFWwindow* init();
	~model();

private:
	vector<mesh> meshes;
	vector<mtl> mtls;
	glm::vec3 upVector;
	glm::vec3 whereToLook;
	float deltaTime;
	const GLuint WIDTH = 800, HEIGHT = 600;

};