#pragma once

#include "../stdafx.h"

class CImageCapture
{
private:
	CImageCapture(IBaseFilter* filter);
	~CImageCapture();
public:
	static CImageCapture* Create(const BSTR devName);
	static HRESULT EnumCapture(BSTR *pDevName,int *outDevCount);
private:
	IBaseFilter *m_Filter;
};