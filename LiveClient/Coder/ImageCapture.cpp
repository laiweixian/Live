#include "ImageCapture.h"

CImageCapture::CImageCapture(IBaseFilter* filter): m_Filter(filter),m_Wnd(NULL)
{
	InitCapture();
}

CImageCapture::CImageCapture(HWND hwn) : m_Filter(NULL),m_Wnd(hwn)
{
	InitWnd();
}

CImageCapture::~CImageCapture()
{
	if (m_Filter) m_Filter->Release();
	m_Filter = NULL;
}

void CImageCapture::Destroy()
{
	delete this;
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
				{
					pFilter->AddRef();
					pCap = new CImageCapture(pFilter);
				}
					
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

CImageCapture* CImageCapture::Create(HWND hwn)
{
	return new CImageCapture(hwn);
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

HRESULT CImageCapture::InitCaptureGraphBuilder(
	IGraphBuilder **ppGraph,  // Receives the pointer.
	ICaptureGraphBuilder2 **ppBuild  // Receives the pointer.
)
{
	if (!ppGraph || !ppBuild)
	{
		return E_POINTER;
	}
	IGraphBuilder *pGraph = NULL;
	ICaptureGraphBuilder2 *pBuild = NULL;

	// Create the Capture Graph Builder.
	HRESULT hr = CoCreateInstance(CLSID_CaptureGraphBuilder2, NULL,
		CLSCTX_INPROC_SERVER, IID_ICaptureGraphBuilder2, (void**)&pBuild);
	if (SUCCEEDED(hr))
	{
		// Create the Filter Graph Manager.
		hr = CoCreateInstance(CLSID_FilterGraph, 0, CLSCTX_INPROC_SERVER,
			IID_IGraphBuilder, (void**)&pGraph);
		if (SUCCEEDED(hr))
		{
			// Initialize the Capture Graph Builder.
			pBuild->SetFiltergraph(pGraph);

			// Return both interface pointers to the caller.
			*ppBuild = pBuild;
			*ppGraph = pGraph; // The caller must release both interfaces.
			return S_OK;
		}
		else
		{
			pBuild->Release();
		}
	}
	return hr; // Failed

}

int CImageCapture::InitWnd()
{
	
	return 0;
}

int CImageCapture::InitCapture()
{
	HRESULT hr = S_FALSE;
	CComPtr<IEnumPins> enumPins;
	CComBSTR vCap = L"Video Capture";
	
	if (m_Filter == NULL)
		goto fail;

	hr = InitCaptureGraphBuilder(&m_Graph,&m_Builder);
	if (!SUCCEEDED(hr))
		goto fail;

	hr = m_Graph->AddFilter(m_Filter, vCap);
	if (!SUCCEEDED(hr))
		goto fail;

	hr = InitCompressor(&m_Compressor);
	if (!SUCCEEDED(hr))
		goto fail;

	hr = m_Builder->RenderStream(&PIN_CATEGORY_PREVIEW, &MEDIATYPE_Video,m_Filter, NULL, NULL);
	if (!SUCCEEDED(hr))
		goto fail;
	


	return S_OK;
fail:
	return hr;
}

HRESULT CImageCapture::QueryPins(IBaseFilter *pFilter)
{
	HRESULT hr = S_FALSE;
	CComPtr<IEnumPins> enumPins;
	IPin* pPin = NULL;

	PIN_DIRECTION dir;
	vector<PIN_DIRECTION> dirs;

	hr = pFilter->EnumPins(&enumPins);
	if (!SUCCEEDED(hr))
		goto fail;

	while (enumPins->Next(1,&pPin,NULL) == S_OK)
	{
		hr = pPin->QueryDirection(&dir);
		if (!SUCCEEDED(hr))
		{
			pPin->Release();
			pPin = NULL;
			continue;
		}

		dirs.push_back(dir);

		pPin->Release();
		pPin = NULL;
	}
	return hr;
fail:
	return hr;
}

HRESULT CImageCapture::InitCompressor(IBaseFilter** ppCompre)
{
	HRESULT hr;
	IBaseFilter* pCompre = NULL;
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

	hr = devEnum->CreateClassEnumerator(CLSID_VideoCompressorCategory, &enumMoniker, 0);
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

		VariantClear(&var);
		pMoniker->Release();
		pMoniker = NULL;
		pProperty->Release();
		pProperty = NULL;

		
		
	}

	return S_OK;

fail:
	return S_FALSE;
}