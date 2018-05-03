#include "textures.h"
#include <SOIL.h>

textures::textures()
{
}

GLuint textures::createTexture(const char* path) {
	GLuint tex = loadTexture();

	if (path == NULL) { //(path != NULL) && (path[0] == '\0')) {
		generateColorAsMipmap();
	} else {
		generateMipmap(path);
	}

	return tex;
}

GLuint textures::loadTexture() {
	GLuint texture1;
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object
											// Set our texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Set texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	return texture1;
}


void textures::generateColorAsMipmap() {

	//int* rgb = 0xFF | (0xFF << 8) | (0x7F << 16) | (0x4F << 24);
	// 1.0f, 0.5f, 0.31f (255, 127.5, 79.05)
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1000, 1000, 0, GL_RGB, GL_UNSIGNED_INT, rgb);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, widthIm, heightIm, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	//glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void textures::generateMipmap(const char* path) {
	int widthIm, heightIm;

	unsigned char* image = SOIL_load_image(path, &widthIm, &heightIm, 0, SOIL_LOAD_RGB);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, widthIm, heightIm, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.
}

textures::~textures()
{
}
