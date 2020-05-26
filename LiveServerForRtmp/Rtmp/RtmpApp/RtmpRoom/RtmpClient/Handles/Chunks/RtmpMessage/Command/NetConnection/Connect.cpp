#include "Connect.h"
using namespace Connect;

CContent::CContent()
{

}

CContent::~CContent()
{

}

CContent* CContent::Create(AMF0::CParse* parse)
{
	CContent* pContent = NULL;
	bool valid = false;


	return NULL;
}

CContent* CContent::Create(AMF3::CParse* parse)
{
	return NULL;
}

string CContent::GetCommandName()
{
	string name = COMMAND_NAME;
	return name;
}

int CContent::GetTransactionID()
{
	return TRANSACTION_ID;
}

CommandObject CContent::GetObject()
{
	return m_Obj;
}

bool CContent::CheckOut(AMF0::CParse* parse)
{
	bool valid = false;

	valid = parse->m_Datas.size() == 4;
	if (!valid) goto fail;

	valid = CheckCommandName(parse);
	if (!valid) goto fail;

	valid = CheckTransactionID(parse);
	if (!valid) goto fail;

	valid = CheckCommandObject(parse);
	if (!valid) goto fail;

	valid = CheckOptionalUserArgumemts(parse);
	if (!valid) goto fail;

	return valid;
fail:
	return false;
}

bool CContent::CheckCommandName(AMF0::CParse* parse)
{
	bool valid = false;
	AMF0::Data *pTempData = NULL;
	char* str = NULL;
	int len = 0;

	pTempData = parse->m_Datas.at(0);
	valid = AMF0::IsString(*pTempData);
	if (!valid)
		goto fail;
	
	AMF0::CopyString(NULL,*pTempData,&len);
	if (len <= 0)
		goto fail;

	str = new char[len];
	AMF0::CopyString(str,*pTempData,&len);
	
	if (strcmp(str,COMMAND_NAME) != 0)
		goto fail;
	if (str) delete[] str;
	return true;
fail:
	if (str) delete[] str;
	str = NULL;
	return false;
}

bool CContent::CheckTransactionID(AMF0::CParse* parse)
{
	bool valid = false;
	AMF0::Data *pTempData = NULL;
	int tranId = 0;

	pTempData = parse->m_Datas.at(1);
	valid = IsNumber(*pTempData);
	if (!valid)
		goto fail;

	tranId = pTempData->dValue.pNum->num;
	if (tranId != TRANSACTION_ID)	
		goto fail;

	return true;
fail:
	return false;
}

bool CContent::CheckCommandObject(AMF0::CParse* parse)
{
	bool valid = false;
	AMF0::Data *pTempData = NULL;
	AMF0::Object *pObj = NULL;
	AMF0::Member *pMem = NULL;
	int i = 0;
	int ret = 0;

	pTempData = parse->m_Datas.at(2);
	if (pTempData->dType != AMF0::MARKER_OBJECT)
		goto fail;
	
	pObj = pTempData->dValue.pObj;
	if (pObj->count != 10)
		goto fail;

	for (i=0;i<pObj->count;i++)
	{
		ret = AMF0::Utf8Cmp(COMMAND_OBJECT_MEMBER_NAME[i],pObj->pMems[i].name);
		if (ret != 0)
			goto fail;
	}


	
	
fail:
	return false;
}

bool CContent::CheckOptionalUserArgumemts(AMF0::CParse* parse)
{
	bool valid = false;
	AMF0::Data *pTempData = NULL;

	pTempData = parse->m_Datas.at(3);
	

	return true;
fail:
	return false;
}

bool CContent::CheckOut(AMF3::CParse* parse)
{

}

bool CContent::CheckCommandName(AMF3::CParse* parse)
{

}
bool CContent::CheckTransactionID(AMF3::CParse* parse)
{

}
bool CContent::CheckCommandObject(AMF3::CParse* parse)
{

}
bool CContent::CheckOptionalUserArgumemts(AMF3::CParse* parse)
{

}

	/*
	
	 
	 Object *pTempObj = NULL;
	bool valid = false;
	
	//check count
	
	
	//check number 1
	pTempData = pParse->m_Datas.at(0);
	
	if (!valid) goto fail;
	valid =  UTF8IsEqual(COMMAND_NAME,*(pTempData->dValue.pStr));
	if (!valid) goto fail;

	//check number 2 
	pTempData = pParse->m_Datas.at(1);
	valid = pTempData->dType == MARKER_NUMBER ;
	if (!valid) goto fail;
	valid = (pTempData->dValue.pNum->num) == TRANSACTION_ID;
	if (!valid) goto fail;

	//create new content,and copy value
	pContent = new Content;
	pContent->commandName = COMMAND_NAME;
	pContent->transactionId = TRANSACTION_ID;

	//check number 3
	pTempData = pParse->m_Datas.at(2);
	valid = pTempData->dType == MARKER_OBJECT;
	if (!valid) goto fail;
	valid = (pTempData->dValue.pObj->count) == 10;
	if (!valid) goto fail;
		// object member 
	pTempObj = pTempData->dValue.pObj;
	valid = true;
	valid &=  UTF8IsEqual(APP, pTempObj->pObjPros[0].name);				valid &= pTempObj->pObjPros[0].value.dType == MARKER_STRING;
	valid &=  UTF8IsEqual(FLASHVER, pTempObj->pObjPros[1].name);			valid &= pTempObj->pObjPros[1].value.dType == MARKER_STRING;
	valid &=  UTF8IsEqual(SWF_URL, pTempObj->pObjPros[2].name);			valid &= pTempObj->pObjPros[2].value.dType == MARKER_STRING;
	valid &=  UTF8IsEqual(TC_URL, pTempObj->pObjPros[3].name);				valid &= pTempObj->pObjPros[3].value.dType == MARKER_STRING;
	valid &=  UTF8IsEqual(FPAD, pTempObj->pObjPros[4].name);				valid &= pTempObj->pObjPros[4].value.dType == MARKER_BOOLEAN;
	valid &=  UTF8IsEqual(AUDIO_CODECS, pTempObj->pObjPros[5].name);		valid &= pTempObj->pObjPros[5].value.dType == MARKER_NUMBER;
	valid &=  UTF8IsEqual(VIDEO_CODECS, pTempObj->pObjPros[6].name);		valid &= pTempObj->pObjPros[6].value.dType == MARKER_NUMBER;
	valid &=  UTF8IsEqual(VIDEO_FUNCTION, pTempObj->pObjPros[7].name);		valid &= pTempObj->pObjPros[7].value.dType == MARKER_NUMBER;
	valid &=  UTF8IsEqual(PAGE_URL, pTempObj->pObjPros[8].name);			valid &= pTempObj->pObjPros[8].value.dType == MARKER_STRING;
	valid &=  UTF8IsEqual(OBJECT_ENCODING, pTempObj->pObjPros[9].name);	valid &= pTempObj->pObjPros[9].value.dType == MARKER_NUMBER;
	if (!valid) goto fail;
	UTF8ToString(pContent->cmdObj.app, *(pTempObj->pObjPros[0].value.dValue.pStr));
	UTF8ToString(pContent->cmdObj.flashver, *(pTempObj->pObjPros[1].value.dValue.pStr));
	UTF8ToString(pContent->cmdObj.swfUrl, *(pTempObj->pObjPros[2].value.dValue.pStr));
	UTF8ToString(pContent->cmdObj.tcUrl, *(pTempObj->pObjPros[3].value.dValue.pStr));
	
	(pContent->cmdObj.fpad )= (bool)(pTempObj->pObjPros[4].value.dValue.pBool->bol);
	pContent->cmdObj.audioCodecs =(uint16_t) (pTempObj->pObjPros[5].value.dValue.pNum->num);
	pContent->cmdObj.videoCodecs = (uint16_t)(pTempObj->pObjPros[6].value.dValue.pNum->num);
	pContent->cmdObj.videoFunction = (uint16_t)(pTempObj->pObjPros[7].value.dValue.pNum->num);
	
	UTF8ToString(pContent->cmdObj.pageUrl, *(pTempObj->pObjPros[8].value.dValue.pStr));
	
	pContent->cmdObj.objectEncoding = (uint16_t)(pTempObj->pObjPros[9].value.dValue.pNum->num);
	

	//check number 4
	pTempData = pParse->m_Datas.at(3);
	
	*/

			


