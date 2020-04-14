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
		ShowBitmap(NULL,0);
		break;
	default:
		return CDialogEx::OnCommand(wParam,lParam);
		break;
	}

	return 0;
}

int CMainDialog::ShowBitmap(uint8_t* data, const int dataLen)
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

	::StretchBlt(hWin,0,0,winWidth,winHeigth,hScreen,0,0,screenWidth,screenHeight,SRCCOPY);

	::DeleteObject(hBit);
	::DeleteDC(hMemory);
	::ReleaseDC(NULL,hScreen);
	::ReleaseDC(this->GetSafeHwnd(),hWin);
	return 0;
}
