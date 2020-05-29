#pragma once

#include "../stdafx.h"


class CImageCapture
{
private:
	CImageCapture(IBaseFilter* filter);
	CImageCapture(HWND hwn);
	~CImageCapture();
public:
	static CImageCapture* Create(const BSTR devName);
	static CImageCapture* Create(HWND hwn);
	static HRESULT EnumCapture(BSTR *pDevName,int *outDevCount);

	void Destroy();
private:
	int InitCapture();
	int InitWnd();
	int InitInfo();

	static HRESULT InitCaptureGraphBuilder(IGraphBuilder **ppGraph, ICaptureGraphBuilder2 **ppBuild);

	
protected:
	static HRESULT QueryPins(IBaseFilter *pFilter);

	int InitRenderer();
private:
	IBaseFilter *m_Filter;
	CComPtr<ICaptureGraphBuilder2> m_Builder;
	CComPtr<IGraphBuilder> m_Graph;

	HWND m_Wnd;
};