#include "Connect.h"

//request
const char* commandName = "connect";
const char* app = "app";
const char* flashver = "flashver";
const char* swfUrl = "swfUrl";
const char* tcUrl = "tcUrl";
const char* fpad = "fpad";
const char* audioCodecs = "audioCodecs";
const char* videoCodecs = "videoCodecs";
const char* videoFunction = "videoFunction";
const char* pageUrl	= "pageUrl";
const char* objectEncoding = "objectEncoding";

//response
const char* _result = "_result";
const char* _error	 = "_error";

void ConnCmd_Free(ConnCmd** ppCC)
{
	if (*ppCC == NULL)	return;

	delete (*ppCC);
	*ppCC = NULL;
}

CConnectCommand::CConnectCommand(AMFType aType) : m_AmfType(aType),m_ConnCmd(NULL)
{

}

CConnectCommand::~CConnectCommand()
{

}

CConnectCommand* CConnectCommand::Create(uint8_t* pData, uint32_t dataLen, AMFType aType)
{
	ConnCmd *pCC = NULL;
	CConnectCommand *ptr = NULL;
	
	if (aType == AMF_0)
		pCC = CConnectCommand::ParseAMF0(pData,dataLen);
	else if (aType == AMF_3)
		pCC = CConnectCommand::ParseAMF3(pData,dataLen);
	else
		pCC = NULL;

	if (pCC != NULL)
	{
		ptr = new CConnectCommand(aType);
		ptr->m_ConnCmd = pCC;
	}

	return ptr;
}

ConnCmd* CConnectCommand::ParseAMF0(uint8_t* pData, uint32_t dataLen)
{
	ConnCmd *pCC = NULL;
	CAMF0* pamf = NULL;
	bool valid = true;
	int i;

	pamf = CAMF0::CreateAMF0(pData,dataLen);
	if (pamf == NULL)				goto failure;				//parse failure
	if (pamf->m_Amfs.size() != 4)	goto failure;				//amf0 data count failure
		
	valid &= (pamf->m_Amfs.at(0)->dType == AMF0Type::STRING);
	valid &= (pamf->m_Amfs.at(1)->dType == AMF0Type::NUMBER);
	valid &= (pamf->m_Amfs.at(2)->dType == AMF0Type::OBJECT);
	valid &= (pamf->m_Amfs.at(3)->dType == AMF0Type::OBJECT);
	if (valid == false)				goto failure;				//all amf0 type not match

	pCC = new ConnCmd;

	//command name
	valid = UTF8IsEqual(commandName, pamf->m_Amfs.at(0)->dString);
	if (valid == false)				goto failure;				//command name is not match connect
	UTF8ToString(pCC->name, pamf->m_Amfs.at(0)->dString);

	//transaction id
	valid = pamf->m_Amfs.at(1)->dNumber == 1;				
	if (valid == false)				goto failure;				//command transaction id is not match connect
	pCC->transactionID = pamf->m_Amfs.at(1)->dNumber;

	//command object
	valid = pamf->m_Amfs.at(2)->dObject.MemCount == 10;
	if (valid == false)				goto failure;				//command object count not match 
	valid &= UTF8IsEqual(app, pamf->m_Amfs.at(2)->dObject.pMems[0].name);			valid &= pamf->m_Amfs.at(2)->dObject.pMems[0].value.dType == AMF0Type::STRING;
	valid &= UTF8IsEqual(flashver, pamf->m_Amfs.at(2)->dObject.pMems[1].name);		valid &= pamf->m_Amfs.at(2)->dObject.pMems[1].value.dType == AMF0Type::STRING;
	valid &= UTF8IsEqual(swfUrl, pamf->m_Amfs.at(2)->dObject.pMems[2].name);		valid &= pamf->m_Amfs.at(2)->dObject.pMems[2].value.dType == AMF0Type::STRING;
	valid &= UTF8IsEqual(tcUrl, pamf->m_Amfs.at(2)->dObject.pMems[3].name);			valid &= pamf->m_Amfs.at(2)->dObject.pMems[3].value.dType == AMF0Type::STRING;
	valid &= UTF8IsEqual(fpad, pamf->m_Amfs.at(2)->dObject.pMems[4].name);			valid &= pamf->m_Amfs.at(2)->dObject.pMems[4].value.dType == AMF0Type::BOOLEAN;
	valid &= UTF8IsEqual(audioCodecs, pamf->m_Amfs.at(2)->dObject.pMems[5].name);	valid &= pamf->m_Amfs.at(2)->dObject.pMems[5].value.dType == AMF0Type::NUMBER;
	valid &= UTF8IsEqual(videoCodecs, pamf->m_Amfs.at(2)->dObject.pMems[6].name);	valid &= pamf->m_Amfs.at(2)->dObject.pMems[6].value.dType == AMF0Type::NUMBER;
	valid &= UTF8IsEqual(videoFunction, pamf->m_Amfs.at(2)->dObject.pMems[7].name);	valid &= pamf->m_Amfs.at(2)->dObject.pMems[7].value.dType == AMF0Type::NUMBER;
	valid &= UTF8IsEqual(pageUrl, pamf->m_Amfs.at(2)->dObject.pMems[8].name);		valid &= pamf->m_Amfs.at(2)->dObject.pMems[8].value.dType == AMF0Type::STRING;
	valid &= UTF8IsEqual(objectEncoding, pamf->m_Amfs.at(2)->dObject.pMems[9].name);valid &= pamf->m_Amfs.at(2)->dObject.pMems[9].value.dType == AMF0Type::NUMBER;
	if (valid == false)				goto failure;				// has one command object member no match
	
	UTF8ToString(pCC->obj.app, pamf->m_Amfs.at(2)->dObject.pMems[0].value.dString);
	UTF8ToString(pCC->obj.flashver, pamf->m_Amfs.at(2)->dObject.pMems[1].value.dString);
	UTF8ToString(pCC->obj.swfUrl, pamf->m_Amfs.at(2)->dObject.pMems[2].value.dString);
	UTF8ToString(pCC->obj.tcUrl, pamf->m_Amfs.at(2)->dObject.pMems[3].value.dString);
	pCC->obj.fpad = pamf->m_Amfs.at(2)->dObject.pMems[4].value.dBoolean;
	pCC->obj.audioCodes = static_cast<uint16_t> (pamf->m_Amfs.at(2)->dObject.pMems[5].value.dNumber);
	pCC->obj.videoCodes = static_cast<uint16_t> (pamf->m_Amfs.at(2)->dObject.pMems[6].value.dNumber);
	pCC->obj.videoFunction = static_cast<uint16_t> (pamf->m_Amfs.at(2)->dObject.pMems[7].value.dNumber);
	UTF8ToString(pCC->obj.pageUrl, pamf->m_Amfs.at(2)->dObject.pMems[8].value.dString);
	pCC->obj.objectEncoding = pamf->m_Amfs.at(2)->dObject.pMems[8].value.dNumber;

	//optional user arguments(自定义的内容)
	pamf->m_Amfs.at(3);

	pamf->Destroy();
	return pCC;

failure:
	if (pCC)	ConnCmd_Free(&pCC);
	if (pamf)	pamf->Destroy();
	return NULL;
}

ConnCmd* CConnectCommand::ParseAMF3(uint8_t* pData, uint32_t dataLen)
{
	ConnCmd *pCC = NULL;

	return pCC;
}

void CConnectCommand::GenRespose()
{
	if (m_AmfType == AMF_0)
	{

	}

}