#include "Modules/IOStreams/IOStreamModule.h"

CBaseIOStreamModule* CBaseIOStreamModule::S_IOModule = NULL;
ULONG register_io_stream(CBaseIOStream* piostream)
{
	return CBaseIOStreamModule::GetInstance()->RegisterIOStream(piostream);
}

CBaseIOStreamModule::CBaseIOStreamModule()
{
	
}

CBaseIOStreamModule::~CBaseIOStreamModule()
{

}

CBaseIOStreamModule* CBaseIOStreamModule::GetInstance()
{
	if (!S_IOModule)
		S_IOModule = new CBaseIOStreamModule;
	return S_IOModule;
}



ULONG CBaseIOStreamModule::RegisterIOStream(CBaseIOStream* piostream)
{
	auto it = m_IOStreams.begin();
	CBaseIOStream *tempIo = NULL;

	for (it = m_IOStreams.begin(); it != m_IOStreams.end();it++)
	{
		tempIo = (*it);
		if (strcmp(piostream->GetIOStreamName(), tempIo->GetIOStreamName()) == 0)
			print_log("has same iostream instance\n");
	}
	m_IOStreams.push_back(piostream);
	return SAR_OK;
}

ULONG CBaseIOStreamModule::Init()
{
	auto it = m_IOStreams.begin();
	CBaseIOStream *tempIo = NULL;
	ULONG result = SAR_OK,ret = SAR_OK;

	for (it = m_IOStreams.begin(); it != m_IOStreams.end(); it++)
	{
		tempIo = (*it);
		result = tempIo->Init();
		if (result != SAR_OK)
			OUT_ERR("iostream init error ,name:%s,code:0x%x",tempIo->GetIOStreamName(),result);
		ret |= result;
	}

	return ret;
}

ULONG CBaseIOStreamModule::Run()
{
	auto it = m_IOStreams.begin();
	CBaseIOStream *tempIo = NULL;
	ULONG result = SAR_OK, ret = SAR_OK;

	for (it = m_IOStreams.begin(); it != m_IOStreams.end(); it++)
	{
		tempIo = (*it);
		result = tempIo->Run();
		if (result != SAR_OK)
			OUT_ERR("iostream run error ,name:%s,code:0x%x", tempIo->GetIOStreamName(), result);
		ret |= result;
	}

	return ret;
}

ULONG CBaseIOStreamModule::Release()
{
	auto it = m_IOStreams.begin();
	CBaseIOStream *tempIo = NULL;
	ULONG result = SAR_OK, ret = SAR_OK;

	for (it = m_IOStreams.begin(); it != m_IOStreams.end(); it++)
	{
		tempIo = (*it);
		result = tempIo->Release();
		if (result != SAR_OK)
			OUT_ERR("iostream release error ,name:%s,code:0x%x", tempIo->GetIOStreamName(), result);
		ret |= result;
	}

	return ret;
}

const char* CBaseIOStreamModule::GetBaseModuleName()
{
	return IO_MODULE_NAME;
}