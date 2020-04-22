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



CConnectCommand::Context* CConnectCommand::Create(uint8_t* pData, uint32_t dataLen, AMFType aType)
{
	CConnectCommand::Context *pContent = NULL;
	
	if (aType == AMF_0)
		pContent = CConnectCommand::ParseAMF0(pData,dataLen);
	else if (aType == AMF_3)
		pContent = CConnectCommand::ParseAMF3(pData,dataLen);
	else
		pContent = NULL;

	return pContent;
}

CConnectCommand::Context* CConnectCommand::ParseAMF0(uint8_t* pData, uint32_t dataLen)
{
	CConnectCommand::Context *pContent = NULL;
	CAMF0* pamf = NULL;
	AMF0Data *pAmfData = NULL;
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

	pContent = new CConnectCommand::Context;

	//command name
	pAmfData = (pamf->m_Amfs.at(0));
	valid = UTF8IsEqual(commandName, pAmfData->dString);
	if (valid == false)				goto failure;				//command name is not match connect
	UTF8ToString(pContent->name, pAmfData->dString);

	//transaction id
	pAmfData = (pamf->m_Amfs.at(1));
	valid = pAmfData->dNumber == 1;
	if (valid == false)				goto failure;				//command transaction id is not match connect
	pContent->transactionID = pAmfData->dNumber;

	//command object
	pAmfData = (pamf->m_Amfs.at(2));
	valid = pAmfData->dObject.MemCount == 10;
	if (valid == false)				goto failure;				//command object count not match 
	valid &= UTF8IsEqual(app, pAmfData->dObject.pMems[0].name);			valid &= pAmfData->dObject.pMems[0].value.dType == AMF0Type::STRING;
	valid &= UTF8IsEqual(flashver, pAmfData->dObject.pMems[1].name);		valid &= pAmfData->dObject.pMems[1].value.dType == AMF0Type::STRING;
	valid &= UTF8IsEqual(swfUrl, pAmfData->dObject.pMems[2].name);		valid &= pAmfData->dObject.pMems[2].value.dType == AMF0Type::STRING;
	valid &= UTF8IsEqual(tcUrl, pAmfData->dObject.pMems[3].name);			valid &= pAmfData->dObject.pMems[3].value.dType == AMF0Type::STRING;
	valid &= UTF8IsEqual(fpad, pAmfData->dObject.pMems[4].name);			valid &= pAmfData->dObject.pMems[4].value.dType == AMF0Type::BOOLEAN;
	valid &= UTF8IsEqual(audioCodecs, pAmfData->dObject.pMems[5].name);	valid &= pAmfData->dObject.pMems[5].value.dType == AMF0Type::NUMBER;
	valid &= UTF8IsEqual(videoCodecs, pAmfData->dObject.pMems[6].name);	valid &= pAmfData->dObject.pMems[6].value.dType == AMF0Type::NUMBER;
	valid &= UTF8IsEqual(videoFunction, pAmfData->dObject.pMems[7].name);	valid &= pAmfData->dObject.pMems[7].value.dType == AMF0Type::NUMBER;
	valid &= UTF8IsEqual(pageUrl, pAmfData->dObject.pMems[8].name);		valid &= pAmfData->dObject.pMems[8].value.dType == AMF0Type::STRING;
	valid &= UTF8IsEqual(objectEncoding, pAmfData->dObject.pMems[9].name);valid &= pAmfData->dObject.pMems[9].value.dType == AMF0Type::NUMBER;
	if (valid == false)				goto failure;				// has one command object member no match
	
	UTF8ToString(pContent->obj.app, pAmfData->dObject.pMems[0].value.dString);
	UTF8ToString(pContent->obj.flashver, pAmfData->dObject.pMems[1].value.dString);
	UTF8ToString(pContent->obj.swfUrl, pAmfData->dObject.pMems[2].value.dString);
	UTF8ToString(pContent->obj.tcUrl, pAmfData->dObject.pMems[3].value.dString);
	pContent->obj.fpad = pAmfData->dObject.pMems[4].value.dBoolean;
	pContent->obj.audioCodes = static_cast<uint16_t> (pAmfData->dObject.pMems[5].value.dNumber);
	pContent->obj.videoCodes = static_cast<uint16_t> (pAmfData->dObject.pMems[6].value.dNumber);
	pContent->obj.videoFunction = static_cast<uint16_t> (pAmfData->dObject.pMems[7].value.dNumber);
	UTF8ToString(pContent->obj.pageUrl, pAmfData->dObject.pMems[8].value.dString);
	pContent->obj.objectEncoding = pAmfData->dObject.pMems[8].value.dNumber;

	//optional user arguments(�Զ��������)
	pAmfData = (pamf->m_Amfs.at(3));
	pContent->optional.memCount = pAmfData->dObject.MemCount;
	pContent->optional.pMembers = new BaseCommand::ObjectMember[pContent->optional.memCount];

	for (i=0;i<pAmfData->dObject.MemCount;i++)
	{
		UTF8ToString(pContent->optional.pMembers[i].name, pAmfData->dObject.pMems[i].name);
		if (pAmfData->dObject.pMems[i].value.dType == AMF0Type::NUMBER)
		{
			pContent->optional.pMembers[i].dType = BaseCommand::DataType::INT;

		}
		else if (pAmfData->dObject.pMems[i].value.dType == AMF0Type::BOOLEAN)
		{
			pContent->optional.pMembers[i].dType = BaseCommand::DataType::BOOLEAN;
		}
		else if (pAmfData->dObject.pMems[i].value.dType == AMF0Type::STRING)
		{
			pContent->optional.pMembers[i].dType = BaseCommand::DataType::STRING;
		}
		else continue;
	}

	pamf->Destroy();
	return pContent;

failure:
	if (pContent)	delete pContent;
	if (pamf)	pamf->Destroy();
	return NULL;
}

CConnectCommand::Context* CConnectCommand::ParseAMF3(uint8_t* pData, uint32_t dataLen)
{
	CConnectCommand::Context *pContent = NULL;

	return pContent;
}

