#include "stdafx.h"
#include "Renderer.h"

CRenderer::CRenderer()
{

}

CRenderer::~CRenderer()
{

}

void CRenderer::Renderer(int width, int height, void* bits, int bitsSize)
{
	HDC target = NULL ;
	int left, right, bottom, top;
	HDC hComDC = NULL; 
	HBITMAP hComBmp = NULL,hOld = NULL;
	BITMAPINFO info;

	target = GetRendererTarget(&left, &right, &bottom, &top);
	hComDC = CreateCompatibleDC(target);

	info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	info.bmiHeader.biWidth = width;
	info.bmiHeader.biHeight = height;
	info.bmiHeader.biPlanes = 1;
	info.bmiHeader.biBitCount = 24;
	info.bmiHeader.biCompression = BI_RGB;
	info.bmiHeader.biSizeImage = bitsSize;
	info.bmiHeader.biXPelsPerMeter = 0;
	info.bmiHeader.biYPelsPerMeter = 0;
	info.bmiHeader.biClrUsed = 0;
	info.bmiHeader.biClrImportant = 0;
	hComBmp = CreateDIBSection(target, &(info), CBM_INIT, &bits, &info, DIB_RGB_COLORS);

	hOld = (HBITMAP)SelectObject(hComDC,hComBmp);

	SetStretchBltMode(target, HALFTONE);
	StretchBlt(target, left, top, right - left, bottom - top, \
		hComDC, 0, 0, width, height, SRCCOPY);

	::SelectObject(hComDC, hOld);
	DeleteDC(hComDC);
	DeleteObject(hComBmp);
}