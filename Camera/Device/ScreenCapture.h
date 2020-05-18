#pragma once

#include "../stdafx.h"

struct BitmapFormat
{
	BITMAPFILEHEADER fHead;
	BITMAPINFOHEADER iHead;
	uint8_t *buff;
	int		 buffSize; 
};

class CScreen
{
public:
	CScreen() = default;
	~CScreen() = default;

	static int Capture(HWND hWin,BitmapFormat* pFormat);
	static int GetBitmapFormat(HDC hdc,HBITMAP hBit);
	static int Render(BitmapFormat* pBit,HDC hDst);
};