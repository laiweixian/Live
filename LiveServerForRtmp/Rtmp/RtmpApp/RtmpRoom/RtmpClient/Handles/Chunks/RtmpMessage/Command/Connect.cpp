#include "Connect.h"

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

ConnCmd* CConnectCommand::Parse(uint8_t* pData, uint32_t dataLen, AMFType aType)
{
	ConnCmd *pCC = NULL;
	
	if (aType == AMF_0)
		pCC = CConnectCommand::ParseAMF0(pData,dataLen);
	else if (aType == AMF_3)
		pCC = CConnectCommand::ParseAMF3(pData,dataLen);
	else
		pCC = NULL;
	return pCC;
}

void CConnectCommand::ConnCmd_Free(ConnCmd** ppCC)
{
	if (*ppCC == NULL)	return ;

	delete (*ppCC);
	*ppCC = NULL;
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

	//command name
	valid = UTF8IsEqual(commandName, pamf->m_Amfs.at(0)->data_string);
	if (valid == false)				goto failure;				//command name is not match connect

	//transaction id
	valid = pamf->m_Amfs.at(1)->data_num == 1;				
	if (valid == false)				goto failure;				//command transaction id is not match connect
	
	//command object
	valid = pamf->m_Amfs.at(2)->data_object.MemCount == 10;
	if (valid == false)				goto failure;				//command object count not match 
	valid &= UTF8IsEqual(app, pamf->m_Amfs.at(2)->data_object.pMems[0].name);
	valid &= UTF8IsEqual(flashver, pamf->m_Amfs.at(2)->data_object.pMems[1].name);
	valid &= UTF8IsEqual(swfUrl, pamf->m_Amfs.at(2)->data_object.pMems[2].name);
	valid &= UTF8IsEqual(tcUrl, pamf->m_Amfs.at(2)->data_object.pMems[3].name);
	valid &= UTF8IsEqual(fpad, pamf->m_Amfs.at(2)->data_object.pMems[4].name);
	valid &= UTF8IsEqual(audioCodecs, pamf->m_Amfs.at(2)->data_object.pMems[5].name);
	valid &= UTF8IsEqual(videoCodecs, pamf->m_Amfs.at(2)->data_object.pMems[6].name);
	valid &= UTF8IsEqual(videoFunction, pamf->m_Amfs.at(2)->data_object.pMems[7].name);
	valid &= UTF8IsEqual(pageUrl, pamf->m_Amfs.at(2)->data_object.pMems[8].name);
	valid &= UTF8IsEqual(objectEncoding, pamf->m_Amfs.at(2)->data_object.pMems[9].name);
	if (valid == false)				goto failure;				// has one command object member no match
	
	//
	



	
	
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