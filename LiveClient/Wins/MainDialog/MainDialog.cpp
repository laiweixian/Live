// MainDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "LiveClient.h"
#include "MainDialog.h"
#include "afxdialogex.h"
#include "../EditDialog/InputDialog.h"

#include "Coder/SoundCapture.h"
#include "Coder/Hardware.h"
#include "Coder/Media.h"
#include "Coder/ImageCapture.h"
#include "Coder/VideoDecode.h"



// CMainDialog 对话框

IMPLEMENT_DYNAMIC(CMainDialog, CDialogEx)

BEGIN_MESSAGE_MAP(CMainDialog, CDialogEx)
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_WM_PAINT()
	ON_WM_SYSCOMMAND()
	ON_BN_CLICKED(IDC_BUTTON_PLAY, &CMainDialog::OnBnClickedButtonPlay)
END_MESSAGE_MAP()

CMainDialog::CMainDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MAIN_DIALOG, pParent)
{
	
}

CMainDialog::~CMainDialog()
{
}

void CMainDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_PLAY, m_Play);
}



// CMainDialog 消息处理程序


int CMainDialog::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	m_Menu.LoadMenu(IDR_MAIN_MENU);
	this->SetMenu(&m_Menu);

	return 0;
}


void CMainDialog::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialogEx::OnTimer(nIDEvent);
}


void CMainDialog::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialogEx::OnPaint()
}


void CMainDialog::OnSysCommand(UINT nID, LPARAM lParam)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialogEx::OnSysCommand(nID, lParam);
}

BOOL CMainDialog::OnCommand(WPARAM wParam, LPARAM lParam)
{
	const WORD height = HIWORD(wParam) , low = LOWORD(wParam);
	CInputDialog input;
	
	wstring url ; 

	switch (low)
	{
	case ID_OPEN_RTMP:
		
		break;
	case ID_OPEN_FILE:
		CaptureScreen();
		break;
	default:
		return CDialogEx::OnCommand(wParam,lParam);
		break;
	}

	return 0;
}

int CMainDialog::CaptureScreen()
{
	int devCount = 0;
	int i = 0;
	BSTR *devNames = NULL;
	CImageCapture *pCap = NULL;

	CImageCapture::EnumCapture(NULL,&devCount);
	if (devCount > 0)
		devNames = new BSTR[devCount];
	if (devNames)
		CImageCapture::EnumCapture(devNames,&devCount);

	if (devCount > 0)
		pCap = CImageCapture::Create(devNames[0]);
		
	for (i = 0;i < devCount;i++)
	{
		SysFreeString(devNames[i]);
		devNames[i] = NULL;
	}
	devNames = NULL;

	if (pCap)	pCap->Destroy();
	pCap = NULL;
	return 0;

	HDC hScreen , hWin,hMemory;
	HBITMAP hBit,hOldBit ;
	int screenWidth = 0 , screenHeight = 0;
	RECT rect;
	int winWidth = 0 , winHeigth = 0;

	hScreen = ::GetDC(NULL);	
	screenWidth = ::GetDeviceCaps(hScreen, HORZRES);
	screenHeight = ::GetDeviceCaps(hScreen, VERTRES);
	
	hWin = this->GetDC()->GetSafeHdc();
	this->GetClientRect(&rect);
	winWidth = rect.right - rect.left ; winHeigth = rect.bottom - rect.top;
	
	hMemory = ::CreateCompatibleDC(hScreen);
	hBit = ::CreateCompatibleBitmap(hScreen, screenWidth, screenHeight);
	
	hOldBit = (HBITMAP)::SelectObject(hMemory,hBit);
	::BitBlt(hMemory,0,0,screenWidth,screenHeight,hScreen,0,0,SRCCOPY);

	//save bitmap
	SaveBitmap(hMemory,hBit);

	::DeleteObject(hBit);
	::DeleteDC(hMemory);
	::ReleaseDC(NULL,hScreen);
	::ReleaseDC(this->GetSafeHwnd(),hWin);
	return 0;
}

int CMainDialog::SaveBitmap(HDC hdc, HBITMAP hBit)
{
	BITMAP bitmap;
	BITMAPFILEHEADER fileHeader;
	BITMAPINFOHEADER infoHeader;
	DWORD bmpSize,DIBSize , length;
	char *buff = NULL , *bmpBuff = NULL; 

	::GetObject(hBit,sizeof(BITMAP),&bitmap);
	
	infoHeader.biSize = sizeof(BITMAPINFOHEADER);
	infoHeader.biWidth = bitmap.bmWidth;
	infoHeader.biHeight = bitmap.bmHeight;
	infoHeader.biPlanes = 1;
	infoHeader.biBitCount = 24;
	infoHeader.biCompression = BI_RGB;
	infoHeader.biSizeImage = 0;
	infoHeader.biXPelsPerMeter = 0;
	infoHeader.biYPelsPerMeter = 0;
	infoHeader.biClrUsed = 0;
	infoHeader.biClrImportant = 0;

	bmpSize = ((infoHeader.biWidth * infoHeader.biBitCount + 23) / 24) * 3 * infoHeader.biHeight;
	buff = new char[bmpSize];
	GetDIBits(hdc,hBit,0,infoHeader.biHeight,buff,(BITMAPINFO*)&infoHeader,DIB_RGB_COLORS);
	
	DIBSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + bmpSize;
	fileHeader.bfType = 0x4d42;	// 'B' 0x4d ,'M' 0x42
	fileHeader.bfSize = DIBSize;
	fileHeader.bfReserved1 = 0;
	fileHeader.bfReserved2 = 0;
	fileHeader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

	length = sizeof(fileHeader) + sizeof(infoHeader) + bmpSize;
	bmpBuff = new char[length];
	memcpy(bmpBuff,&fileHeader,sizeof(fileHeader));
	memcpy(bmpBuff+ sizeof(fileHeader),&infoHeader,sizeof(infoHeader));
	memcpy(bmpBuff+ sizeof(fileHeader)+ sizeof(infoHeader),buff,bmpSize);

	EncodeAndSave(bmpBuff,length);

	


	delete[] buff; buff = NULL;
	delete[] bmpBuff; bmpBuff = NULL;
	return 0;
}


int CMainDialog::EncodeAndSave(const char* src, const int srcLen)
{
	DWORD bytesSize;
	HANDLE hFile = CreateFile(L"captureqwsx.bmp",
		GENERIC_WRITE,
		0,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL, NULL);
	WriteFile(hFile, (LPSTR)src, srcLen, &bytesSize, NULL);
	CloseHandle(hFile);
	return 0;
}


void CMainDialog::OnBnClickedButtonPlay()
{
	// TODO: 在此添加控件通知处理程序代码
	
	PlayContext *pCtx;
	pCtx = new PlayContext;
	pCtx->ctx = this;
	pCtx->play = CMainDialog::PlayMusic;
	pCtx->renderer = CMainDialog::ShowPicture;

	CPlayMedia *pm = NULL;
	

	pm = new CPlayMedia("E:\\media.flv", pCtx);
	pm->Play();
}


static void WriteBMP(LPCTSTR lpFileName,int w, int h, uint8_t* data, int size)
{
	int ret = 0;
	HANDLE hFile = NULL;
	BITMAP bmp;
	BITMAPINFO pbmi;
	WORD    cClrBits;
	BITMAPFILEHEADER hdr;
	DWORD dwTmp;
	

	hFile = CreateFile(lpFileName, GENERIC_WRITE, \
		FILE_SHARE_READ, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);

	pbmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	pbmi.bmiHeader.biWidth = w;
	pbmi.bmiHeader.biHeight = h;
	pbmi.bmiHeader.biPlanes = 1;
	pbmi.bmiHeader.biBitCount = 24;
	pbmi.bmiHeader.biCompression = BI_RGB;
	pbmi.bmiHeader.biSizeImage = size;
	pbmi.bmiHeader.biXPelsPerMeter = 0;
	pbmi.bmiHeader.biYPelsPerMeter = 0;
	pbmi.bmiHeader.biClrUsed = 0;
	pbmi.bmiHeader.biClrImportant = 0;

	hdr.bfType = 0x4d42;
	hdr.bfSize = (DWORD)(sizeof(BITMAPFILEHEADER) +
		pbmi.bmiHeader.biSize + pbmi.bmiHeader.biClrUsed
		* sizeof(RGBQUAD) + pbmi.bmiHeader.biSizeImage);
	hdr.bfReserved1 = 0;
	hdr.bfReserved2 = 0;

	hdr.bfOffBits = (DWORD) sizeof(BITMAPFILEHEADER) +
		pbmi.bmiHeader.biSize + pbmi.bmiHeader.biClrUsed
		* sizeof(RGBQUAD);

	//header 0
	if (!WriteFile(hFile, (LPVOID)&hdr, sizeof(BITMAPFILEHEADER),
		(LPDWORD)&dwTmp, NULL))
	{
		//errhandler("WriteFile", hwnd);
	}

	//header 1
	if (!WriteFile(hFile, (LPVOID)&pbmi.bmiHeader, sizeof(BITMAPINFOHEADER)
		+ pbmi.bmiHeader.biClrUsed * sizeof(RGBQUAD),
		(LPDWORD)&dwTmp, (NULL)))
	{
		//errhandler("WriteFile", hwnd);
	}
		
	//body

	if (!WriteFile(hFile, (LPSTR)data, (int)size, (LPDWORD)&dwTmp, NULL))
	{
		//errhandler("WriteFile", hwnd);
	}




	CloseHandle(hFile);
}


static uint8_t* ScaleToRGB(AVFrame* image, int* outSize,int *outW,int *outH)
{
	uint8_t* data[4] = { 0 };
	uint8_t *buf = NULL;
	int line_size[4] = { 0 };
	AVPixelFormat dstFmt = AV_PIX_FMT_BGR24;
	SwsContext *ctx = NULL;
	int ret = -1;
	int dataSize = 0;
	
	ctx = sws_getContext(image->width, image->height, (AVPixelFormat)image->format, \
		image->width, image->height, dstFmt, \
		SWS_BICUBIC, NULL, NULL, NULL);
	ret = av_image_alloc(data, line_size, image->width, image->height, dstFmt, 1);
	dataSize = ret;

	ret = sws_scale(ctx,\
		image->data, image->linesize,0, \
		image->height, data, line_size);

	//WriteBMP(TEXT("E:\\log\\1.BMP"),image->width,image->height,data[0],dataSize);

	sws_freeContext(ctx);
	
	
	buf = new uint8_t[dataSize];
	memcpy(buf,data[0],dataSize);
	av_freep(&data[0]);

	*outW = image->width;
	*outH = image->height;
	*outSize = dataSize;
	return buf;
}



void CMainDialog::ShowPicture(void *ctx, AVFrame *pRGB)
{
	CMainDialog* dlg =(CMainDialog*) ctx;
	int ret;
	HDC dstDC = NULL , hMem = NULL;
	HBITMAP hBmp = NULL;
	RECT rect;
	
	dstDC = dlg->GetDC()->GetSafeHdc();
	hMem = CreateCompatibleDC(dstDC);
	dlg->GetClientRect(&rect);


	//
	uint8_t *data = NULL;
	int dataSize = 0;
	int dstWidth, dstHeight;
	data = ScaleToRGB(pRGB, &dataSize,&dstWidth,&dstHeight);

	BITMAPINFO info;
	info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	info.bmiHeader.biWidth = dstWidth;
	info.bmiHeader.biHeight = dstHeight;
	info.bmiHeader.biPlanes = 1;
	info.bmiHeader.biBitCount = 24;
	info.bmiHeader.biCompression = BI_RGB;
	info.bmiHeader.biSizeImage = dataSize;
	info.bmiHeader.biXPelsPerMeter = 0;
	info.bmiHeader.biYPelsPerMeter = 0;
	info.bmiHeader.biClrUsed = 0;
	info.bmiHeader.biClrImportant = 0;
	
	hBmp = CreateDIBitmap(dstDC, &info.bmiHeader, CBM_INIT,data,&info, DIB_RGB_COLORS);
	HBITMAP hold = (HBITMAP)SelectObject(hMem, hBmp);
	
	SetStretchBltMode(dstDC, HALFTONE);
	ret = ::StretchBlt(dstDC,0,0,rect.right-rect.left,rect.bottom-rect.top,\
		hMem,0,0, dstWidth,dstHeight, SRCCOPY);
	
	SelectObject(hMem, hold);
	DeleteObject(hBmp);
	DeleteDC(hMem);
	delete[] data;
}

BITMAPINFO CMainDialog::GetBmpInfo()
{
	BITMAPINFO info;
	RECT rect;
	GetWindowRect(&rect);
	
	const int wWidth = rect.right - rect.left, \
		wHeight = rect.bottom - rect.top;
	
	info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	info.bmiHeader.biWidth = wWidth;
	info.bmiHeader.biHeight = wHeight;
	info.bmiHeader.biPlanes = 1;
	info.bmiHeader.biBitCount = 24;
	info.bmiHeader.biCompression = BI_RGB;
	info.bmiHeader.biSizeImage = wWidth * wHeight;
	info.bmiHeader.biXPelsPerMeter = 0;
	info.bmiHeader.biYPelsPerMeter = 0;
	info.bmiHeader.biClrUsed = 0;
	info.bmiHeader.biClrImportant = 0;

	return info;
}

void CMainDialog::PlayMusic(void *ctx, AVFrame *pPCM)
{
	CMainDialog* dlg = (CMainDialog*)ctx;

}


