#include "SceneWriter.h"
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <atlimage.h>


SceneWriter::SceneWriter()
{
	
}

void SceneWriter::test() {

	RECT rc;
	HWND hwnd = GetForegroundWindow();
		//GetActiveWindow();
	GetClientRect(hwnd, &rc);
	HRGN hrgn = CreateRectRgn(rc.left, rc.top, rc.right, rc.bottom);

	// get the device context of the screen
	//HDC hSDC = CreateDC("DISPLAY", NULL, NULL, NULL);
	//HWND window = WindowFromDC(hSDC);
	//HDC hScreenDC = GetDC(window);
	HDC hScreenDC = GetDCEx(hwnd, hrgn, DCX_WINDOW);
		//GetDC(GetForegroundWindow());
	
	// and a device context to put it in
	HDC hMemoryDC = CreateCompatibleDC(hScreenDC);
	int width = GetDeviceCaps(hScreenDC, HORZRES);
	int height = GetDeviceCaps(hScreenDC, VERTRES);
	HBITMAP hBitmap = CreateCompatibleBitmap(hScreenDC, width, height);

	// get a new bitmap5
	HBITMAP hOldBitmap = (HBITMAP)SelectObject(hMemoryDC, hBitmap);

	BitBlt(hMemoryDC, 0, 0, width, height, hScreenDC, 0, 0, SRCCOPY);
	hBitmap = (HBITMAP)SelectObject(hMemoryDC, hOldBitmap);

	// clean up
	DeleteDC(hMemoryDC);
	DeleteDC(hScreenDC);

	// now your image is held in hBitmap. You can save it or do whatever with it
	
	CImage image;
	image.Attach(hBitmap);
	image.Save("../../test.bmp", Gdiplus::ImageFormatBMP);
}

SceneWriter::~SceneWriter()
{
}
