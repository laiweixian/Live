#pragma once


// CMainDialog �Ի���

class CMainDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CMainDialog)

public:
	CMainDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMainDialog();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MAIN_DIALOG };
	
#endif

	int ShowBitmap(uint8_t* data,const int dataLen);


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnPaint();
	BOOL OnCommand( WPARAM wParam, LPARAM lParam );


private:
	CMenu m_Menu;
public:
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
};
