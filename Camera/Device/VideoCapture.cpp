#include "VideoCapture.h"

CVideoCapture::CVideoCapture()
{
	CoInitialize(NULL);
	Init();
}

CVideoCapture::~CVideoCapture()
{
	CoUninitialize();
}

HRESULT CVideoCapture::Init()
{
	HRESULT hr; 
	CComPtr<ICreateDevEnum> devEnum ;
	CComPtr<IEnumMoniker>   enumMoniker ;
	IMoniker *pMoniker ;
	IPropertyBag *pPropBag ;
	VARIANT var;
	HWND hList; 
	
	hr = devEnum.CoCreateInstance(CLSID_SystemDeviceEnum);
	if (hr != S_OK)
		return hr;

	hr = devEnum->CreateClassEnumerator(CLSID_VideoInputDeviceCategory,&enumMoniker,0);
	if (hr != S_OK)
		return hr;

	while (enumMoniker->Next(1,&pMoniker,NULL) == S_OK)
	{
		hr = pMoniker->BindToStorage(0,0, IID_IPropertyBag,(void**)&pPropBag);
		if (hr != S_OK)
		{
			pMoniker->Release();
			pMoniker = NULL;
			continue;
		}

		VariantInit(&var);
		hr = pPropBag->Read(L"Description",&var,NULL);
		hr = pPropBag->Read(L"FriendlyName",&var,NULL);

		VariantClear(&var);
		
		pMoniker->Release();
		pMoniker = NULL;
	}

}