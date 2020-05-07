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

CConnectCmd::CConnectCmd() : m_Content(NULL)
{

}
CConnectCmd::~CConnectCmd()
{
	if (m_Content)
		delete m_Content;
	m_Content = NULL;
}

CConnectCmd* CConnectCmd::Create(uint8_t* pData, uint32_t dataLen, AMFType aType)
{
	CConnectCmd *pCmd = NULL;
	Content *pContent = NULL;
	
	if (aType == AMF_0)
		pContent = CConnectCmd::ParseAMF0(pData,dataLen);
	else if (aType == AMF_3)
		pContent = CConnectCmd::ParseAMF3(pData,dataLen);
	else
		pContent = NULL;

	if (pContent)
	{
		pCmd = new CConnectCmd;
		pCmd->m_Content = pContent;
	}
		
	return pCmd;
}

CConnectCmd::Content* CConnectCmd::ParseAMF0(uint8_t* pData, uint32_t dataLen)
{
	CConnectCmd::Content *pContent = NULL;
	AMF0::CParse *pParse = NULL;
	AMF0::Data *pAmfData = NULL;
	bool valid = true;
	int i;

	pParse = AMF0::CParse::Create(pData,dataLen);
	if (pParse == NULL)				goto failure;				//parse failure
	if (pParse->m_Datas.size()!= 4)	goto failure;				//amf0 data count failure
		
	valid &= (pParse->m_Datas.at(0)->dType == AMF0::DataType::STRING);
	valid &= (pParse->m_Datas.at(1)->dType ==  AMF0::DataType::NUMBER);
	valid &= (pParse->m_Datas.at(2)->dType ==  AMF0::DataType::OBJECT);
	valid &= (pParse->m_Datas.at(3)->dType ==  AMF0::DataType::OBJECT);
	if (valid == false)				goto failure;				//all amf0 type not match

	pContent = new Content;

	//command name
	pAmfData = (pParse->m_Datas.at(0));
	valid = AMF0::UTF8IsEqual(commandName,pAmfData->dValue.pStr->utf8);
	if (valid == false)				goto failure;				//command name is not match connect
	AMF0::UTF8ToString(pContent->commandName, pAmfData->dValue.pStr->utf8);

	//transaction id
	pAmfData = (pParse->m_Datas.at(1));
	valid = (pAmfData->dValue.pNum->num) == 1;
	if (valid == false)				goto failure;				//command transaction id is not match connect
	pContent->transactionID = (pAmfData->dValue.pNum->num);

	//command object
	pAmfData = (pParse->m_Datas.at(2));
	valid = pAmfData->dValue.pObj->count == 10;
	if (valid == false)				goto failure;				//command object count not match 
	valid &= AMF0::UTF8IsEqual(app,pAmfData->dValue.pObj->pObjPros[0].name);			valid &= pAmfData->dValue.pObj->pObjPros[0].value.dType ==  AMF0::DataType::STRING;
	valid &= AMF0::UTF8IsEqual(flashver,pAmfData->dValue.pObj->pObjPros[1].name);		valid &= pAmfData->dValue.pObj->pObjPros[1].value.dType ==  AMF0::DataType::STRING;
	valid &= AMF0::UTF8IsEqual(swfUrl,pAmfData->dValue.pObj->pObjPros[2].name);			valid &= pAmfData->dValue.pObj->pObjPros[2].value.dType ==  AMF0::DataType::STRING;
	valid &= AMF0::UTF8IsEqual(tcUrl,pAmfData->dValue.pObj->pObjPros[3].name);			valid &= pAmfData->dValue.pObj->pObjPros[3].value.dType ==  AMF0::DataType::STRING;
	valid &= AMF0::UTF8IsEqual(fpad,pAmfData->dValue.pObj->pObjPros[4].name);			valid &= pAmfData->dValue.pObj->pObjPros[4].value.dType ==  AMF0::DataType::BOOLEAN;
	valid &= AMF0::UTF8IsEqual(audioCodecs,pAmfData->dValue.pObj->pObjPros[5].name);	valid &= pAmfData->dValue.pObj->pObjPros[5].value.dType ==  AMF0::DataType::NUMBER;
	valid &= AMF0::UTF8IsEqual(videoCodecs,pAmfData->dValue.pObj->pObjPros[6].name);	valid &= pAmfData->dValue.pObj->pObjPros[6].value.dType ==  AMF0::DataType::NUMBER;
	valid &= AMF0::UTF8IsEqual(videoFunction,pAmfData->dValue.pObj->pObjPros[7].name);	valid &= pAmfData->dValue.pObj->pObjPros[7].value.dType ==  AMF0::DataType::NUMBER;
	valid &= AMF0::UTF8IsEqual(pageUrl,pAmfData->dValue.pObj->pObjPros[8].name);		valid &= pAmfData->dValue.pObj->pObjPros[8].value.dType ==  AMF0::DataType::STRING;
	valid &= AMF0::UTF8IsEqual(objectEncoding,pAmfData->dValue.pObj->pObjPros[9].name);valid &= pAmfData->dValue.pObj->pObjPros[9].value.dType ==  AMF0::DataType::NUMBER;
	if (valid == false)				goto failure;				// has one command object member no match
	AMF0::UTF8ToString(pContent->obj.app, (pAmfData->dValue.pObj->pObjPros[0].value.dValue.pStr->utf8));
	AMF0::UTF8ToString(pContent->obj.flashver, (pAmfData->dValue.pObj->pObjPros[1].value.dValue.pStr->utf8));
	AMF0::UTF8ToString(pContent->obj.swfUrl, (pAmfData->dValue.pObj->pObjPros[2].value.dValue.pStr->utf8));
	AMF0::UTF8ToString(pContent->obj.tcUrl, (pAmfData->dValue.pObj->pObjPros[3].value.dValue.pStr->utf8));
	pContent->obj.fpad = (pAmfData->dValue.pObj->pObjPros[4].value.dValue.pBool->bol);
	pContent->obj.audioCodes =static_cast<uint16_t>(pAmfData->dValue.pObj->pObjPros[5].value.dValue.pNum->num);
	pContent->obj.videoCodes = static_cast<uint16_t> (pAmfData->dValue.pObj->pObjPros[6].value.dValue.pNum->num);
	pContent->obj.videoFunction = static_cast<uint16_t>( pAmfData->dValue.pObj->pObjPros[7].value.dValue.pNum->num);
	AMF0::UTF8ToString(pContent->obj.pageUrl, (pAmfData->dValue.pObj->pObjPros[8].value.dValue.pStr->utf8));
	pContent->obj.objectEncoding = static_cast<uint16_t>( pAmfData->dValue.pObj->pObjPros[9].value.dValue.pNum->num);

	//optional user arguments(自定义的内容)
	pAmfData = (pParse->m_Datas.at(3));

	if (pParse)		pParse->Destroy();
	return pContent;

failure:
	if (pContent)	delete pContent;
	if (pParse)		pParse->Destroy();
	return NULL;
}



