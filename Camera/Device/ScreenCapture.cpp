#include "../stdafx.h"
#include "ScreenCapture.h"

int CScreen::Capture(HWND hWin, BitmapFormat* pFormat)
{
	int ret = -1;
	HDC  hWinDC ,hComDC; 
	HBITMAP hBit ;
	HGDIOBJ hOld ; 
	int winHeight , winWidth;

	
	
	if (pFormat == NULL)
		goto fail;

	hWinDC = GetDC(hWin);
	winHeight = GetDeviceCaps(hWinDC, VERTRES); winWidth = GetDeviceCaps(hWinDC, HORZRES);

	hComDC = CreateCompatibleDC(hWinDC);
	hBit = CreateCompatibleBitmap(hComDC,winWidth,winHeight);
	hOld = SelectObject(hComDC,hBit);

	BitBlt(hComDC,0,0,winWidth,winHeight,hWinDC,0,0, SRCCOPY);
	
	GetBitmapFormat(hComDC,hBit);
	

	ReleaseDC(hWin,hWinDC);
	DeleteDC(hComDC);
	DeleteObject(hBit);
fail:
	return -1;
}

int CScreen::GetBitmapFormat(HDC hdc,HBITMAP hBit)
{
	BITMAP bmp;
	BITMAPFILEHEADER fHeader;
	BITMAPINFOHEADER iHeader;
	uint8_t *buff = NULL;
	int      buffLen = 0;
	int		 bmpSize = 0;

	GetObject(hdc, sizeof(BITMAP), &bmp);
	
	//use bgr24 color space
	iHeader.biSize = sizeof(BITMAPINFOHEADER);
	iHeader.biWidth = bmp.bmWidth;
	iHeader.biHeight = bmp.bmHeight;
	iHeader.biPlanes = 1;
	iHeader.biBitCount = 24;
	iHeader.biCompression = BI_RGB;
	iHeader.biSizeImage = 0;
	iHeader.biXPelsPerMeter = 0;
	iHeader.biYPelsPerMeter = 0;
	iHeader.biClrUsed = 0;
	iHeader.biClrImportant = 0;

	bmpSize = ((iHeader.biWidth * iHeader.biBitCount + 23) / 24) * 3 * iHeader.biHeight;
	
	fHeader.bfType = 0x4d42;	// 'B' 0x4d ,'M' 0x42
	fHeader.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + bmpSize;;
	fHeader.bfReserved1 = 0;
	fHeader.bfReserved2 = 0;
	fHeader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

	buffLen = bmpSize;
	buff = new uint8_t[buffLen];
	GetDIBits(hdc, hBit, 0, iHeader.biHeight, buff, (BITMAPINFO*)&iHeader, DIB_RGB_COLORS);

	return 0;
}

int CScreen::Render(BitmapFormat* pBit, HDC hDst)
{
	HDC hSrc;
	HDC hComSrc ;
	HBITMAP hSrcBmp; 
	HGDIOBJ hOld ;
	int dstWidth , dstHeight ;
	
	if (pBit == NULL)
		goto fail;
	if (pBit->buff = NULL)
		goto fail;

	hSrc = GetDC(NULL);
	hComSrc = CreateCompatibleDC(hSrc);
	hSrcBmp = CreateDIBitmap(hComSrc,&(pBit->iHead), CBM_INIT,pBit->buff, (BITMAPINFO*)&(pBit->iHead), DIB_RGB_COLORS);
	hOld = SelectObject(hComSrc,hSrcBmp);

	dstWidth = GetDeviceCaps(hDst, VERTRES); dstHeight = GetDeviceCaps(hDst, HORZRES);
	StretchBlt(hDst, 0, 0, dstWidth, dstHeight, hComSrc, 0, 0, pBit->iHead.biWidth, pBit->iHead.biHeight, SRCCOPY);

	DeleteObject(hSrcBmp);
	DeleteDC(hComSrc);
	ReleaseDC(NULL,hSrc);

fail:
	return -1;
}