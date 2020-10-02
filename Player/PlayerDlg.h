
// PlayerDlg.h : ͷ�ļ�
//

#pragma once

#include "PlayFile.h"
#include "Renderer.h"
#include "Loudspeaker.h"

#define WM_RENDERER_BITMAP (WM_USER+100)



// CPlayerDlg �Ի���
class CPlayerDlg : public CDialogEx,\
				   public CRenderer,\
				   public CLoudspeaker
{
// ����
public:
	CPlayerDlg(CWnd* pParent = NULL);	// ��׼���캯��
	virtual ~CPlayerDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PLAYER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;
	CButton m_PlayBtn;

	// ���ɵ���Ϣӳ�亯��
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
	static void VideoCallback(void* ctx, AVFrame* bgr24);
	static void AudioCallback(void* ctx, AVFrame* pcm);
	static void SubtitleCallback(void* ctx, AVFrame* raw);
private:
	CPlayFile* m_PlayMedia;
	PlayContext m_PlayCtx;
};
