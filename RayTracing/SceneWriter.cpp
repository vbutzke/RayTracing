#include "SceneWriter.h"

SceneWriter::SceneWriter()
{
}

std::string SceneWriter::write(std::string path) {

	RECT rc;
	CImage image;
	HWND hwnd = GetForegroundWindow();
	GetClientRect(hwnd, &rc);
	HRGN hrgn = CreateRectRgn(rc.left, rc.top, rc.right, rc.bottom);
	HDC hScreenDC = GetDCEx(hwnd, hrgn, DCX_WINDOW);
	HDC hMemoryDC = CreateCompatibleDC(hScreenDC);
	int width = GetDeviceCaps(hScreenDC, HORZRES);
	int height = GetDeviceCaps(hScreenDC, VERTRES);

	HBITMAP hBitmap = CreateCompatibleBitmap(hScreenDC, width, height);
	HBITMAP hOldBitmap = (HBITMAP)SelectObject(hMemoryDC, hBitmap);

	BitBlt(hMemoryDC, 0, 0, width, height, hScreenDC, 0, 0, SRCCOPY);
	hBitmap = (HBITMAP)SelectObject(hMemoryDC, hOldBitmap);
	
	DeleteDC(hMemoryDC);
	DeleteDC(hScreenDC);

	image.Attach(hBitmap);
	image.Save(path.c_str(), Gdiplus::ImageFormatBMP);
	return path;
}

std::string SceneWriter::write(std::string path, GLuint height, GLuint width, unsigned char* pixels) {

	HBITMAP bmp = CreateBitmap(width, height, 1, 24, pixels);
	CImage image;
	image.Attach(bmp);
	image.Save(path.c_str(), Gdiplus::ImageFormatBMP);
	return path;
}

SceneWriter::~SceneWriter()
{
}
