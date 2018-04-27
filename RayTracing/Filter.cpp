#include "Filter.h"

Filter::Filter()
{
}



void Filter::applyFilter(GLuint width, GLuint height, unsigned char* pixels) {
	////apply the filter
	//for (int x = 0; x < w; x++)
	//	for (int y = 0; y < h; y++)
	//	{
	//		double red = 0.0, green = 0.0, blue = 0.0;
	//
	//		//multiply every value of the filter with corresponding image pixel
	//		for (int filterY = 0; filterY < filterHeight; filterY++)
	//			for (int filterX = 0; filterX < filterWidth; filterX++)
	//			{
	//				int imageX = (x - filterWidth / 2 + filterX + w) % w;
	//				int imageY = (y - filterHeight / 2 + filterY + h) % h;
	//				red += image[imageY * w + imageX].r * filter[filterY][filterX];
	//				green += image[imageY * w + imageX].g * filter[filterY][filterX];
	//				blue += image[imageY * w + imageX].b * filter[filterY][filterX];
	//			}
	//
	//		//truncate values smaller than zero and larger than 255
	//		result[y * w + x].r = min(max(int(factor * red + bias), 0), 255);
	//		result[y * w + x].g = min(max(int(factor * green + bias), 0), 255);
	//		result[y * w + x].b = min(max(int(factor * blue + bias), 0), 255);
	//	}
	//
	////draw the result buffer to the screen
	//for (int y = 0; y < h; y++)
	//	for (int x = 0; x < w; x++)
	//	{
	//		pset(x, y, result[y * w + x]);
	//	}
	//
	////redraw & sleep
	//redraw();
	//sleep();
}

Filter::~Filter()
{
}

//
//Its size has to be uneven, so that it has a center, for example 3x3, 5x5 and 7x7 are ok.
//It doesn't have to, but the sum of all elements of the filter should be 1 if you want the resulting image to have the same brightness as the original.
//If the sum of the elements is larger than 1, the result will be a brighter image, and if it's smaller than 1, a darker image. If the sum is 0, the resulting image isn't necessarily completely black, but it'll be very dark.
