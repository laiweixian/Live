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
	IMoniker *pMoniker = NULL;
	IPropertyBag *pBag = NULL;
	IBaseFilter *pFilter = NULL;
	IPin *pPin = NULL;
	CComPtr<IFilterGraph3> filterGraph;
	CComVariant  var;
	vector<CameraDevice> devs;
	CameraDevice dev;
	
	hr = devEnum.CoCreateInstance(CLSID_SystemDeviceEnum);
	if (hr != S_OK)
		return hr;

	hr = devEnum->CreateClassEnumerator(CLSID_VideoInputDeviceCategory,&enumMoniker,0);
	if (hr != S_OK || enumMoniker == NULL)
		return hr;

	while (enumMoniker->Next(1,&pMoniker,NULL) == S_OK)
	{
		hr = pMoniker->BindToStorage(NULL, NULL, IID_IPropertyBag,(void**) &pBag);
		if (hr != S_OK || pBag == NULL)
		{
			pMoniker->Release();
			pMoniker = NULL;
			continue;
		}

		hr = pMoniker->BindToObject(NULL, NULL, IID_IBaseFilter, (void**)&pFilter);
		if (hr != S_OK || pFilter == NULL)
		{
			pBag->Release();
			pBag = NULL;
			pMoniker->Release();
			pMoniker = NULL;
			continue;
		}

		hr = FinPinByCategory(pFilter, PINDIR_INPUT, PIN_CATEGORY_PREVIEW,&pPin);
		if (hr != S_OK || pPin == NULL)
		{
			pFilter->Release();
			pFilter = NULL;
			pBag->Release();
			pBag = NULL;
			pMoniker->Release();
			pMoniker = NULL;
			continue;
		}


		
		pPin->Release();
		pPin = NULL;
		pFilter->Release();
		pFilter = NULL;
		pBag->Release();
		pBag = NULL;
		pMoniker->Release();
		pMoniker = NULL;
	}
}

HRESULT CVideoCapture::InitCaptureGraphBuilder(IGraphBuilder **ppGraph, ICaptureGraphBuilder2 **ppBuilder)
{
	HRESULT ret; 
	IGraphBuilder *pGraph = NULL;
	ICaptureGraphBuilder2 *pBuild = NULL;
	

	if (!ppGraph || !ppBuilder)
		return E_POINTER;
	ret = CoCreateInstance(CLSID_CaptureGraphBuilder2, \
							NULL, CLSCTX_INPROC_SERVER, \
							IID_ICaptureGraphBuilder2, (void**)pBuild);
	if (!SUCCEEDED(ret))
		return ret;
	
	ret = CoCreateInstance(CLSID_FilterGraph, 0,\
							CLSCTX_INPROC_SERVER, \
							IID_IGraphBuilder, (void**)&pGraph);
	if (!SUCCEEDED(ret))
	{
		pBuild->Release();
		pBuild = NULL;
		return ret;
	}

	//
	pBuild->SetFiltergraph(pGraph);
		
	*ppBuilder = pBuild;
	*ppGraph = pGraph;
	return ret;
}

HRESULT CVideoCapture::FinPinByCategory(IBaseFilter *pFilter, PIN_DIRECTION pinDir, REFGUID category, IPin **ppPin)
{
	HRESULT ret = S_FALSE;
	IPin *pPin = NULL;
	CComPtr<IEnumPins> pins;
	PIN_DIRECTION pinDir2;
	bool bFound = false;

	if (!ppPin)	goto fail;

	ret = pFilter->EnumPins(&pins);
	if (ret != S_OK)	goto fail;
	while (ret = pins->Next(1,&pPin,0) , ret == S_OK)
	{
		ret = pPin->QueryDirection(&pinDir2);
		if (FAILED(ret))
			goto fail;
		bFound = PinMatchesCategory(pPin, category);
		if (bFound && pinDir2 == pinDir)
		{
			*ppPin = pPin;
			return S_OK;
		}
		else
			pPin->Release();
	}

	return S_OK;

fail:
	return ret;
}

BOOL CVideoCapture::PinMatchesCategory(IPin *pPin, REFGUID category)
{
	BOOL bFound = FALSE;

	IKsPropertySet *pKs = NULL;
	HRESULT hr = pPin->QueryInterface(IID_PPV_ARGS(&pKs));
	if (SUCCEEDED(hr))
	{
		GUID PinCategory;
		DWORD cbReturned;
		hr = pKs->Get(AMPROPSETID_Pin, AMPROPERTY_PIN_CATEGORY, NULL, 0,
			&PinCategory, sizeof(GUID), &cbReturned);
		if (SUCCEEDED(hr) && (cbReturned == sizeof(GUID)))
		{
			bFound = (PinCategory == category);
		}
		pKs->Release();
	}
	return bFound;

}