
// PlayerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Player.h"
#include "PlayerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
	
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CPlayerDlg 对话框



CPlayerDlg::CPlayerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_PLAYER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_PlayCtx.ctx = this;
	m_PlayCtx.pa = CPlayerDlg::AudioCallback;
	m_PlayCtx.pv = CPlayerDlg::VideoCallback;
	m_PlayCtx.ps = CPlayerDlg::SubtitleCallback;

	string path("E:\\media.flv");

	m_PlayMedia = CPlayFile::Create(path, &m_PlayCtx);
}

CPlayerDlg::~CPlayerDlg()
{
	if (m_PlayMedia) m_PlayMedia->Destory();
}

void CPlayerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_PLAY, m_PlayBtn);
}

BEGIN_MESSAGE_MAP(CPlayerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_PLAY, &CPlayerDlg::OnBnClickedButtonPlay)
	ON_MESSAGE(WM_RENDERER_BITMAP, CPlayerDlg::OnRendererBitmap)
END_MESSAGE_MAP()


// CPlayerDlg 消息处理程序

BOOL CPlayerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CPlayerDlg::OnBnClickedButtonPlay()
{
	if (m_PlayMedia)
		m_PlayMedia->Play();
}

void CPlayerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CPlayerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CPlayerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

HDC& CPlayerDlg::GetRendererTarget(int* outLeft, int* outRight, int* outBottom, int *outTop)
{
	RECT rect;
	HDC hdc;

	this->GetClientRect(&rect);
	hdc = this->GetDC()->GetSafeHdc();

	*outLeft = rect.left;
	*outRight = rect.right;
	*outTop = rect.top;
	*outBottom = rect.bottom;
	return hdc;
}

void CPlayerDlg::VideoCallback(void* ctx, AVFrame* bgr24)
{
	CPlayerDlg* pdl = (CPlayerDlg*)ctx;
	pdl->SendMessage(WM_RENDERER_BITMAP, 0, (LPARAM)bgr24);
}

void CPlayerDlg::AudioCallback(void* ctx, AVFrame* pcm)
{
	CPlayerDlg* pdl = (CPlayerDlg*)ctx;
}

void CPlayerDlg::SubtitleCallback(void* ctx, AVFrame* raw)
{
	CPlayerDlg* pdl = (CPlayerDlg*)ctx;
}

LRESULT CPlayerDlg::OnRendererBitmap(WPARAM wParam, LPARAM lParam)
{
	int t = wParam;
	AVFrame* bgr24 = (AVFrame*)lParam;

	av_freep(&(bgr24->data[0]));
	av_frame_free(&bgr24);
	return 0;
}
