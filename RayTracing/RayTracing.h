#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include "mesh.h"

#define RECURSION 5

class RayTracing
{
public:
	RayTracing();
	void render(glm::vec3 rayOrigin, glm::vec3 rayDirection, glm::vec3& color, vector<mesh> meshes, int& recursion);
	~RayTracing();
};

