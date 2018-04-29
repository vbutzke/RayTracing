#include "RayTracing.h"

RayTracing::RayTracing()
{
}

void RayTracing::render(glm::vec3 rayOrigin, glm::vec3 rayDirection, glm::vec3& color, vector<mesh> meshes, int& recursion) {

	glm::vec3 background = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec3 closestPoint = rayOrigin;
	GLfloat smallestDist = 0.0f;

	recursion++;

	for (int i = 0; i < meshes.size(); i++) {
		vector<GLfloat> vo = meshes[i].getVO();
		int j = 0;
		while (j < vo.size()) {
			glm::vec3 point = glm::vec3(vo[++j], vo[++j], vo[++j]);

			//		if(there is intersection){
			//			if(calculated distance < smallestDist) {
			//				smallestDist = calculated distance;
			//				closestPoint = this point;
			//			}
			//		}
		}
	}

	if ((closestPoint == rayOrigin) || (recursion > RECURSION)) {
		color = background;
	} else {
		glm::vec3 reflection;
		glm::vec3 refraction;
		//		Compute um raio para cada fonte de luz para checar por sombra(corO = ilumLocal() ou sombra)
			//		Se a superfície é reflectiva, gere o raio de reflexão->corR = rayTrancingRec(raioRef)
			//			Se a superfície possui refração, gere o raio refratado->corT = rayTrancingRec(raioTransmitido, mat)
			//			Compute a cor do ponto será : cor = interpolação(corO, corR, corT, kr, kt);
			//		return color;
			//	}
	}
}

/*const float EPSILON = 0.001f;

bool IsPointOnLine(Point linePointA, Point linePointB, Point point)
{
	float a = (linePointB.y - linePointA.y) / (linePointB.x - linePointB.x);
	float b = linePointA.y - a * linePointA.x;
	if (fabs(point.y - (a*point.x + b)) < EPSILON)
	{
		return true;
	}

	return false;
}*/

RayTracing::~RayTracing()
{
}
