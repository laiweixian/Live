// MainDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "LiveClient.h"
#include "MainDialog.h"
#include "afxdialogex.h"
#include "../EditDialog/InputDialog.h"


// CMainDialog 对话框

IMPLEMENT_DYNAMIC(CMainDialog, CDialogEx)

BEGIN_MESSAGE_MAP(CMainDialog, CDialogEx)
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_WM_PAINT()
	ON_WM_SYSCOMMAND()
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
		input.ShowInput(&url);
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

	CMedia media;
	media.Encode(this->GetDC()->GetSafeHdc(),fileHeader,infoHeader, buff,bmpSize);

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