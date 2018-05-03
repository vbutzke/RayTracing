#include "RayTracing.h"

RayTracing::RayTracing()
{
}

void RayTracing::render(glm::vec3 rayOrigin, glm::vec3 rayDirection, glm::vec3& color, vector<mesh> meshes, vector<mtl> mtls, int& recursion) {

	glm::vec3 background = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec3 closestPoint = rayOrigin;
	glm::vec3 smallestDist = glm::vec3(-1.0f, -1.0f, -1.0f); //distância nas 3 coordenadas. inicializa em -1 porque ninguém quer distância negativa aqui
	glm::vec3 distance;
	string associatedMTL = "";
	int count = 0;
	mtl currentMTL;
	mesh currentMesh;
	glm::vec3 rayDir; //substituindo o parâmetro

	glm::vec3 a = glm::vec3(rayOrigin.x, 0.0f, rayOrigin.z);
	glm::vec3 b = glm::vec3(rayOrigin.x + 1.0f, 0.0f, rayOrigin.z);
	glm::vec3 c = glm::vec3(rayOrigin.x, rayOrigin.y, rayOrigin.z + 1.0f);
	glm::vec3 planeN = (a - b) % (b - c);

	recursion++;

	for (int i = 0; i < meshes.size(); i++) {
		vector<GLfloat> vo = meshes[i].getVO();
		for (int j = 0; j < vo.size(); j++) {
			glm::vec3 point = glm::vec3(vo[j], vo[++j], vo[++j]);
			float div = sqrt(pow((point.x - rayOrigin.x), 2) + pow((point.y - rayOrigin.y), 2));
			
			normalize(planeN);
			rayDir = rayOrigin - (glm::dot(rayOrigin, planeN))*planeN;
			//rayDir = glm::vec3((float)((point.x - rayOrigin.x)), (float)((point.y - rayOrigin.y)), 1.0f);
	
			if (intersect(rayOrigin, rayDirection, point, distance)) {
				glm::vec3 comparison = glm::lessThanEqual(distance, smallestDist);
				if (comparison.x && comparison.y && comparison.z) {
					smallestDist = distance;
					closestPoint = point;
					associatedMTL = meshes[i].getMTLName();
					currentMesh = meshes[i];
				}
			}
		}
	}

	while (count<mtls.size()) {
		if (mtls[count].getName() == currentMesh.getMTLName()) {
			currentMTL = mtls[count];
			break;
		}
		count++;
	}

	if ((closestPoint == rayOrigin) || (recursion > RECURSION)) {
		color = background;
	} else {
		glm::vec3 reflection;
		glm::vec3 refraction;
	
		//Compute um raio para cada fonte de luz para checar por sombra(corO = ilumLocal() ou sombra)
		
		if(currentMTL.getSharpness()>0) {
			reflect(rayOrigin, rayDirection, closestPoint, reflection);
			render(closestPoint, reflection, color, meshes, mtls, recursion);
		}
		
		if (currentMTL.getNi() >= 1.0f) {
			refract(rayOrigin, rayDirection, closestPoint, refraction);
			render(closestPoint, refraction, color, meshes, mtls, recursion);
		}
	
		color = LerpRGB(LerpRGB(color, reflection, currentMTL.getD()), refraction, currentMTL.getD());
	}
}

glm::vec3 RayTracing::LerpRGB(glm::vec3 c1, glm::vec3 c2, float t) {

	float newR, newG, newB;
	glm::vec3 newColor;

	newR = c1.x + (c2.x - c1.x) * t;
	newG = c1.y + (c2.y - c1.y) * t;
	newB = c1.z + (c2.z - c1.z) * t;

	newColor = glm::vec3(newR, newG, newB);

	return newColor;
}

void RayTracing::normalize(glm::vec3& normal) {
	GLfloat length = sqrt(normal.x*normal.x + normal.y*normal.y + normal.z + normal.z);
	normal.x = normal.x / length;
	normal.y = normal.y / length;
	normal.z = normal.z / length;
}

bool RayTracing::checkIfZero(float& value) {
	if (value == 0) {
		value = 1;
		return true;
	}
	return false;
}

bool RayTracing::calculateT(float pointC, float originC, float directionC, float& t) {
	bool wasZero = checkIfZero(directionC);
	t = (pointC - originC) / directionC;
	return wasZero;
}

bool RayTracing::intersect(glm::vec3 rayOr, glm::vec3 iRay, glm::vec3 point, glm::vec3& distance) {

	float tx, ty, tz;
	bool wasDirZeroX, wasDirZeroY, wasDirZeroZ;
	bool intersect = false;

	wasDirZeroX = calculateT(point.x, rayOr.x, iRay.x, tx);
	wasDirZeroY = calculateT(point.y, rayOr.y, iRay.y, ty);
	wasDirZeroZ = calculateT(point.z, rayOr.z, iRay.z, tz);

	distance = glm::vec3(tx, ty, tz);

	if (wasDirZeroX) {
		if (wasDirZeroY) {
			if (wasDirZeroZ) {
				// 0 0 0
				intersect = ((rayOr.x == point.x) && (rayOr.y == point.y) && (rayOr.z == point.z));
			}
			else {
				// 0 0 !0
				intersect = ((rayOr.x == point.x) && (rayOr.y == point.y) &&
					(tz*iRay.z == point.z - rayOr.z));
			}
		}
		else if (wasDirZeroZ) {
			//0 !0 0
			intersect = ((rayOr.x == point.x) && (rayOr.z == point.z) &&
				(ty*iRay.y == point.y - rayOr.y));
		}
		else {
			//0 !0 !0
			intersect = ((rayOr.x == point.x) && (ty == tz));
		}
	}
	else {
		if (wasDirZeroY) {
			if (wasDirZeroZ) {
				//!0, 0, 0
				intersect = ((rayOr.y == point.y) && (rayOr.z == point.z) &&
					(tx*iRay.x == point.x - rayOr.x));
			}
			else {
				//!0, 0, !0
				intersect = ((rayOr.y == point.y) && (tx == tz));
			}
		}
		else if (wasDirZeroZ) {
			//!0, !0, 0
			intersect = ((rayOr.z == point.z) && (tx == ty));
		}
		else {
			//!0, !0, !0
			intersect = tx == ty == tz;
		}
	}

	return intersect;
}

void RayTracing::reflect(glm::vec3 ray, glm::vec3 rayDir, glm::vec3 intersection, glm::vec3& reflected) {
	glm::vec3 normal = glm::vec3(ray + rayDir * intersection); // point of intersection
	normalize(normal);
	reflected = ray - normal * 2.0f * glm::dot(ray, normal);
}

void RayTracing::refract(glm::vec3 ray, glm::vec3 rayDir, glm::vec3 intersection, glm::vec3& refracted) {
	glm::vec3 normal = glm::vec3(ray + rayDir * intersection); // point of intersection
	normalize(normal);
	float cosi = glm::dot(-normal, rayDir); // -nhit.dot(raydir);
	float k = 1.0f - 0.8f * 0.8f * (1.0f - cosi * cosi);

	refracted = rayDir * 0.8f + normal * (0.8f *cosi - sqrt(k));
}

RayTracing::~RayTracing()
{
}
