#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include "mesh.h"

class RayTracing
{
public:
	RayTracing();
	void render(glm::vec3 rayOrigin, glm::vec3 rayDirection, glm::vec3& color);
	~RayTracing();
};

