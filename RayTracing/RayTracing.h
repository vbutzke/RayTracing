#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include "mesh.h"

#define RECURSION 5

class RayTracing
{
public:
	RayTracing();
	void render(glm::vec3 rayOrigin, glm::vec3 rayDirection, glm::vec3& color, vector<mesh> meshes, vector<mtl> mtls, int& recursion);
	glm::vec3 LerpRGB(glm::vec3 c1, glm::vec3 c2, float t);
	void normalize(glm::vec3& normal);
	bool checkIfZero(float& value);
	bool calculateT(float pointC, float originC, float directionC, float& t);
	bool intersect(glm::vec3 rayOr, glm::vec3 iRay, glm::vec3 point, glm::vec3& distance);
	void reflect(glm::vec3 ray, glm::vec3 rayDir, glm::vec3 intersection, glm::vec3& reflected);
	void refract(glm::vec3 ray, glm::vec3 rayDir, glm::vec3 intersection, glm::vec3& refracted);
	~RayTracing();
};

