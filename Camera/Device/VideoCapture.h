#pragma once
#include "../stdafx.h"

struct CameraDevice
{
	wstring devName;
};

class CVideoCapture
{
public:
	CVideoCapture();
	~CVideoCapture();
private:
	HRESULT Init(); 
	static HRESULT InitCaptureGraphBuilder(IGraphBuilder **ppGraph,ICaptureGraphBuilder2 **ppBuilder);
	static HRESULT FinPinByCategory(IBaseFilter *pFilter,PIN_DIRECTION pinDir,REFGUID category,IPin **ppPin);
	static BOOL PinMatchesCategory(IPin *pPin,REFGUID category);
};
