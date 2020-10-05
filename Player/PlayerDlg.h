
// PlayerDlg.h : 头文件
//

#pragma once

#include "PlayFile.h"
#include "PlayContext.h"
#include "Renderer.h"
#include "Loudspeaker.h"

#define WM_RENDERER_BITMAP (WM_USER+100)



// CPlayerDlg 对话框
class CPlayerDlg : public CDialogEx,\
				   public CRenderer,\
				   public CLoudspeaker,\
				   public IMediaEvent
{
// 构造
public:
	CPlayerDlg(CWnd* pParent = NULL);	// 标准构造函数
	virtual ~CPlayerDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PLAYER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	CButton m_PlayBtn;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBnClickedButtonPlay();
	afx_msg LRESULT OnRendererBitmap(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()

protected:
	HDC& GetRendererTarget(int* outLeft, int* outRight, int* outBottom, int *outTop);

public:
	/*
	static void VideoCallback(void* ctx, BGR24* pBmp);
	static void AudioCallback(void* ctx, PCM* pPcm);
	static void SubtitleCallback(void* ctx, AVFrame* raw);
	*/
	void OnSound(AVFrame* pcm) ;
	void OnImage(AVFrame* bgr24) ;
private:

	CPlayContext *m_PlayCtx;
};
