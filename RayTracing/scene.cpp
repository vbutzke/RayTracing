#include "scene.h"

scene::scene() {
}

glm::vec3 scene::getPositions(){
	return positions;
}

glm::vec3 scene::getColors(){
	return colors;
}

glm::vec3 scene::getObjectColors(){
	return objColors;
}

glm::vec3 scene::getUpVector(){
	return upVector;
}

glm::vec3 scene::getWhereToLook(){
	return whereToLook;
}

glm::vec3 scene::getEyeLine(){
	return eyeLine;
}

glm::vec4 scene::getProjection(){
	return projection;
}

vector<obj> scene::getObjects(){
	return objects;
}

glm::vec3 scene::getRotation() {
	return rotation;
}

float scene::getAngle() {
	return angle;
}

glm::vec3 scene::getTranslation() {
	return translation;
}

glm::vec3 scene::getScale() {
	return scale;
}

string scene::getFileName() {
	return fileName;
}

void scene::setPositions(glm::vec3 nPos) {
	positions = nPos;
}

void scene::setColors(glm::vec3 nCol) {
	colors = nCol;
}

void scene::setObjectColors(glm::vec3 nObjCol) {
	objColors = nObjCol;
}

void scene::setUpVector(glm::vec3 nUpVec) {
	upVector = nUpVec;
}

void scene::setWhereToLook(glm::vec3 nLookAt) {
	whereToLook = nLookAt;
}

void scene::setEyeLine(glm::vec3 nEyeLine) {
	eyeLine = nEyeLine;
}

void scene::setProjection(glm::vec4 nProj) {
	projection = nProj;
}

void scene::setRotation(glm::vec3 nRot) {
	rotation = nRot;
}

void scene::setAngle(float nAngle) {
	angle = nAngle;
}

void scene::setTranslation(glm::vec3 nTrans) {
	translation = nTrans;
}

void scene::setScale(glm::vec3 nScale) {
	scale = nScale;
}

void scene::setObjects(vector<obj> objs) {
	objects = objs;
}

void scene::setFileName(string nFileName) {
	fileName = nFileName;
}

scene::~scene() {
}
