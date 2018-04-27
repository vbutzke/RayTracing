#pragma once

#include <GL/glew.h>
#include "rhostring.hpp"
#include "SceneReader.h"

class Filter
{
public:
	Filter();
	void createFilter(vector< vector<double> >& filter);
	void applyFilter(GLuint& width, GLuint& height, unsigned char* pixels, string path);
	~Filter();

private:
	int filterWidth;
	int filterHeight;
	vector< vector<double> > filter;
	double factor = 1.0;
	double bias = 0.0;
};

