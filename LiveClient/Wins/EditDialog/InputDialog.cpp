// C:\Users\Administrator\source\repos\laiweixian\Live\LiveClient\Wins\EditDialog\InputDialog.cpp : 实现文件
//


#include "stdafx.h"
#include "LiveClient.h"
#include "InputDialog.h"
#include "afxdialogex.h"


// CInputDialog 对话框

IMPLEMENT_DYNAMIC(CInputDialog, CDialogEx)

CInputDialog::CInputDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_INPUT_DIALOG, pParent)
{

}

CInputDialog::~CInputDialog()
{
}

void CInputDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ENTER, m_Etr);
	DDX_Control(pDX, IDC_EDIT, m_Edt);
}


BEGIN_MESSAGE_MAP(CInputDialog, CDialogEx)
	ON_WM_CREATE()
END_MESSAGE_MAP()


// CInputDialog 消息处理程序


int CInputDialog::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	
	
	return 0;
}

int CInputDialog::ShowInput(wstring* url)
{
	INT_PTR resp;
	
	resp = this->DoModal();
	
	*url = m_Text;
	
	return 0;
}

BOOL CInputDialog::OnCommand(WPARAM wParam, LPARAM lParam)
{
	const WORD heigth = HIWORD(wParam) , low = LOWORD(wParam);
	WCHAR buff[1024] = { 0 };

	if (low == IDC_ENTER)
	{
		m_Edt.GetLine(0, buff, 1024);
		m_Text = buff;
		EndDialog(IDOK);
		return 0;
	}

	return CDialogEx::OnCommand(wParam, lParam);
}
