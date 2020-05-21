#include "ImageCapture.h"

CImageCapture::CImageCapture(IBaseFilter* filter): m_Filter(filter)
{

}

CImageCapture::~CImageCapture()
{

}

CImageCapture* CImageCapture::Create(const BSTR devName)
{
	CImageCapture* pCap = NULL;
	HRESULT hr;
	CComPtr<ICreateDevEnum> devEnum;
	CComPtr<IEnumMoniker> enumMoniker;
	IMoniker *pMoniker = NULL;
	IPropertyBag *pProperty = NULL;
	ULONG fetched;
	VARIANT var;
	IBaseFilter *pFilter = NULL;

	hr = devEnum.CoCreateInstance(CLSID_SystemDeviceEnum);
	if (FAILED(hr) || devEnum == NULL)
		goto fail;

	hr = devEnum->CreateClassEnumerator(CLSID_VideoInputDeviceCategory, &enumMoniker, 0);
	if (FAILED(hr) || enumMoniker == NULL)
		goto fail;

	while (S_OK == enumMoniker->Next(1, &pMoniker, &fetched))
	{
		if (pMoniker == NULL)
			break;

		hr = pMoniker->BindToStorage(NULL, NULL, IID_IPropertyBag, (void**)&pProperty);
		if (FAILED(hr) || pProperty == NULL)
		{
			pMoniker->Release();
			pMoniker = NULL;
			continue;
		}

		VariantInit(&var);
		hr = pProperty->Read(L"FriendlyName", &var, 0);
		if (FAILED(hr))
		{
			pMoniker->Release();
			pMoniker = NULL;
			pProperty->Release();
			pProperty = NULL;
			continue;
		}

		if (var.vt == VT_BSTR)
		{
			if (StrCmpW(var.bstrVal, devName) == 0)
			{
				hr = pMoniker->BindToObject(NULL,NULL,IID_IBaseFilter,(void**)&pFilter);
				if (hr == S_OK && pFilter != NULL)
					pCap = new CImageCapture(pFilter);
			}	
		}

		VariantClear(&var);
		pMoniker->Release();
		pMoniker = NULL;
		pProperty->Release();
		pProperty = NULL;	

		if (pCap != NULL)
			break;
	}

	return pCap;
fail:
	return NULL;
}

HRESULT CImageCapture::EnumCapture(BSTR *pDevName, int *outDevCount)
{
	HRESULT hr;
	CComPtr<ICreateDevEnum> devEnum;
	CComPtr<IEnumMoniker> enumMoniker;
	IMoniker *pMoniker = NULL;
	IPropertyBag *pProperty = NULL;
	ULONG fetched;
	VARIANT var;
	int devCount = 0;

	hr = devEnum.CoCreateInstance(CLSID_SystemDeviceEnum);
	if (FAILED(hr) || devEnum == NULL)
		goto fail;

	hr = devEnum->CreateClassEnumerator(CLSID_VideoInputDeviceCategory, &enumMoniker, 0);
	if (FAILED(hr) || enumMoniker == NULL)
		goto fail;

	while (S_OK == enumMoniker->Next(1, &pMoniker, &fetched))
	{
		if (pMoniker == NULL)
			break;
		hr = pMoniker->BindToStorage(NULL, NULL, IID_IPropertyBag, (void**)&pProperty);
		if (FAILED(hr) || pProperty == NULL)
		{
			pMoniker->Release();
			pMoniker = NULL;
			continue;
		}

		VariantInit(&var);
		hr = pProperty->Read(L"FriendlyName", &var, 0);
		if (FAILED(hr))
		{
			pMoniker->Release();
			pMoniker = NULL;
			pProperty->Release();
			pProperty = NULL;
			continue;
		}

		if (pDevName != NULL && var.vt == VT_BSTR)
		{
			pDevName[devCount] = SysAllocString(var.bstrVal);
		}
		devCount++;

		VariantClear(&var);
		pMoniker->Release();
		pMoniker = NULL;
		pProperty->Release();
		pProperty = NULL;
	}
	
	*outDevCount = devCount;
	return S_OK;

fail:
	*outDevCount = 0;
	return S_FALSE;
}