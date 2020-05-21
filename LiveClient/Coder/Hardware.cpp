#include "Hardware.h"

int Min(int a, int b){	return (a > b ? b : a);}
int Max(int a, int b){	return (a > b ? a : b);}

CHardware::CHardware()
{

}

CHardware::~CHardware()
{

}


AVFrame* CHardware::CaptureScreen(HWND hwn, const int x, const int y, const int width, const int height)			//output rgb from screen
{
	//
	AVFrame *bgr24 = NULL;
	HDC hdc = NULL, hComDC = NULL;
	HBITMAP hBmp = NULL;
	HGDIOBJ hOld;
	int wndWidth = 0, wndHeight = 0;
	int targetWidth = 0, targetHeight = 0;

	hdc = GetDC(hwn);
	wndWidth = GetDeviceCaps(hdc, HORZRES);
	wndHeight = ::GetDeviceCaps(hdc, VERTRES);

	targetWidth = width == 0 ? wndWidth : Min(width, wndWidth);
	targetHeight = height == 0 ? wndHeight : Min(height, wndHeight);
	hComDC = CreateCompatibleDC(hdc);
	hBmp = CreateCompatibleBitmap(hComDC, targetWidth, targetHeight);
	hOld = SelectObject(hComDC, hBmp);

	::StretchBlt(hComDC, 0, 0, targetWidth, targetHeight, hdc, x, y, targetWidth, targetHeight, SRCCOPY);

	bgr24 = Translate(hComDC, hBmp);

	ReleaseDC(hwn, hdc);
	DeleteDC(hComDC);
	DeleteObject(hBmp);

	return bgr24;
}

AVFrame* CHardware::CaptureCamera()			//output rgb from camera
{
	HRESULT hr ;
	CComPtr<ICreateDevEnum> devEnum;
	CComPtr<IEnumMoniker> enumMoniker ;
	Filters filters;

	hr = devEnum.CoCreateInstance(CLSID_SystemDeviceEnum);
	if (FAILED(hr))	
		goto fail;

	hr = devEnum->CreateClassEnumerator(CLSID_VideoInputDeviceCategory,&enumMoniker,0);
	if (FAILED(hr))
		goto fail;

	filters = RetrieveFilter(enumMoniker);
	if (filters.size() <= 0)
		goto fail;


	return NULL;

fail:
	return NULL;
}

Filters CHardware::RetrieveFilter(IEnumMoniker* pEnumMoniker)
{
	HRESULT hr;
	Filters filters;
	DeviceFilter *pNew = NULL;
	IMoniker *pMoniker = NULL;
	IPropertyBag *pProperty = NULL;
	IBaseFilter *pBaseFilter = NULL;
	CComVariant var;
	ULONG fetched ;

	while (S_OK == pEnumMoniker->Next(1,&pMoniker,&fetched) )
	{
		hr = pMoniker->BindToStorage(NULL,NULL,IID_IPropertyBag,(void**)&pProperty);
		if (FAILED(hr))
		{
			pMoniker->Release();
			pMoniker = NULL;
			continue;
		}
		hr = pProperty->Read(L"FriendlyName",&var,0);
		if (FAILED(hr))
		{
			pMoniker->Release();
			pMoniker = NULL;
			pProperty->Release();
			pProperty = NULL;
			continue;
		}
		
		hr = pMoniker->BindToObject(NULL,NULL, IID_IBaseFilter,(void**)&pBaseFilter);
		if (FAILED(hr))
		{
			pMoniker->Release();
			pMoniker = NULL;
			pProperty->Release();
			pProperty = NULL;
			continue;
		}

		pNew = new DeviceFilter;
		pNew->FriendlyName = var;
		pNew->pFilter = pBaseFilter;
		filters.push_back(pNew);

		var.Clear();
		pMoniker->Release();
		pMoniker = NULL;
		pProperty->Release();
		pProperty = NULL;
	}

	return filters;
}

AVFrame* CHardware::CaptureLoudspeaker()		//output pcm from Loudspeaker
{
	return NULL;
}

AVFrame* CHardware::CaptureMicrophone()		//output pcm from Microphone
{
	return NULL;
}

void CHardware::EnumCamera()
{

}

void CHardware::EnumMicrophone()
{

}


AVFrame* CHardware::Translate(HDC hdc, HBITMAP hBmp)
{
	AVFrame *bgr24 = NULL;
	int ret;
	BITMAP bitmap;
	BITMAPINFOHEADER infoHeader;
	DWORD bmpSize, DIBSize;
	char *buff = NULL;

	::GetObject(hBmp, sizeof(BITMAP), &bitmap);

	infoHeader.biSize = sizeof(BITMAPINFOHEADER);
	infoHeader.biWidth = bitmap.bmWidth;
	infoHeader.biHeight = bitmap.bmHeight;
	infoHeader.biPlanes = 1;
	infoHeader.biBitCount = 24;
	infoHeader.biCompression = BI_RGB;
	infoHeader.biSizeImage = 0;
	infoHeader.biXPelsPerMeter = 0;
	infoHeader.biYPelsPerMeter = 0;
	infoHeader.biClrUsed = 0;
	infoHeader.biClrImportant = 0;

	bmpSize = ((infoHeader.biWidth * infoHeader.biBitCount + 23) / 24) * 3 * infoHeader.biHeight;
	buff = new char[bmpSize];
	GetDIBits(hdc, hBmp, 0, infoHeader.biHeight, buff, (BITMAPINFO*)&infoHeader, DIB_RGB_COLORS);

	bgr24 = av_frame_alloc();
	bgr24->format = AVPixelFormat::AV_PIX_FMT_BGR24;
	bgr24->width = infoHeader.biWidth;
	bgr24->height = infoHeader.biHeight;
	ret = av_frame_get_buffer(bgr24, 0);
	if (ret != 0)
		goto fail;

	ret = av_image_fill_arrays(bgr24->data, bgr24->linesize, (unsigned char*)buff, (AVPixelFormat)bgr24->format, bgr24->width, bgr24->height, 24);

	delete[] buff; buff = NULL;
	return bgr24;

fail:
	if (bgr24) av_frame_free(&bgr24);
	if (buff) delete[] buff; buff = NULL;
	return NULL;
}