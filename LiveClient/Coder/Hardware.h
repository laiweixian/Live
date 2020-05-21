#pragma once
#include "../stdafx.h"

struct DeviceFilter 
{
	CComVariant FriendlyName;
	IBaseFilter *pFilter;
};

typedef vector<DeviceFilter*> Filters;

class CHardware
{
public:
	CHardware();
	~CHardware();

	static AVFrame* CaptureScreen(const HWND hwn = NULL, const int x = 0, const int y = 0, const int width = 0, const int height = 0);			//output rgb from screen
	static AVFrame* CaptureCamera();			//output rgb from camera
	static AVFrame* CaptureLoudspeaker();		//output pcm from Loudspeaker
	static AVFrame* CaptureMicrophone();		//output pcm from Microphone
	static void EnumCamera();
	static void EnumMicrophone();

private:
	static AVFrame* Translate(HDC hdc, HBITMAP hBmp);
	static Filters RetrieveFilter(IEnumMoniker* pEnumMoniker);
};


