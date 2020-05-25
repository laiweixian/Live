#include "Connect.h"
using namespace Connect;

Content* Connect::ParseConnect(AMF0::CParse *pParse)
{
	Content* pContent = NULL;
	AMF0::Data *pTempData = NULL;
	AMF0::Object *pTempObj = NULL;
	bool valid = false;
	
	//check count
	valid = pParse->m_Datas.size() == 4;
	if (!valid) goto fail;
	
	//check number 1
	pTempData = pParse->m_Datas.at(0);
	valid = pTempData->dType == MARKER_STRING || pTempData->dType == MARKER_LONG_STRING;
	if (!valid) goto fail;
	valid = AMF0::UTF8IsEqual(COMMAND_NAME,*(pTempData->dValue.pStr));
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
	valid &= AMF0::UTF8IsEqual(APP, pTempObj->pObjPros[0].name);				valid &= pTempObj->pObjPros[0].value.dType == MARKER_STRING;
	valid &= AMF0::UTF8IsEqual(FLASHVER, pTempObj->pObjPros[1].name);			valid &= pTempObj->pObjPros[1].value.dType == MARKER_STRING;
	valid &= AMF0::UTF8IsEqual(SWF_URL, pTempObj->pObjPros[2].name);			valid &= pTempObj->pObjPros[2].value.dType == MARKER_STRING;
	valid &= AMF0::UTF8IsEqual(TC_URL, pTempObj->pObjPros[3].name);				valid &= pTempObj->pObjPros[3].value.dType == MARKER_STRING;
	valid &= AMF0::UTF8IsEqual(FPAD, pTempObj->pObjPros[4].name);				valid &= pTempObj->pObjPros[4].value.dType == MARKER_BOOLEAN;
	valid &= AMF0::UTF8IsEqual(AUDIO_CODECS, pTempObj->pObjPros[5].name);		valid &= pTempObj->pObjPros[5].value.dType == MARKER_NUMBER;
	valid &= AMF0::UTF8IsEqual(VIDEO_CODECS, pTempObj->pObjPros[6].name);		valid &= pTempObj->pObjPros[6].value.dType == MARKER_NUMBER;
	valid &= AMF0::UTF8IsEqual(VIDEO_FUNCTION, pTempObj->pObjPros[7].name);		valid &= pTempObj->pObjPros[7].value.dType == MARKER_NUMBER;
	valid &= AMF0::UTF8IsEqual(PAGE_URL, pTempObj->pObjPros[8].name);			valid &= pTempObj->pObjPros[8].value.dType == MARKER_STRING;
	valid &= AMF0::UTF8IsEqual(OBJECT_ENCODING, pTempObj->pObjPros[9].name);	valid &= pTempObj->pObjPros[9].value.dType == MARKER_NUMBER;
	if (!valid) goto fail;
	UTF8ToString(pContent->cmdObj.app, *(pTempObj->pObjPros[0].value.dValue.pStr));
	UTF8ToString(pContent->cmdObj.flashver, *(pTempObj->pObjPros[1].value.dValue.pStr));
	UTF8ToString(pContent->cmdObj.swfUrl, *(pTempObj->pObjPros[2].value.dValue.pStr));
	UTF8ToString(pContent->cmdObj.tcUrl, *(pTempObj->pObjPros[3].value.dValue.pStr));
	/*
	(pContent->cmdObj.fpad )= (bool)(pTempObj->pObjPros[4].value.dValue.pBool->bol);
	pContent->cmdObj.audioCodecs =(uint16_t) (pTempObj->pObjPros[5].value.dValue.pNum->num);
	pContent->cmdObj.videoCodecs = (uint16_t)(pTempObj->pObjPros[6].value.dValue.pNum->num);
	pContent->cmdObj.videoFunction = (uint16_t)(pTempObj->pObjPros[7].value.dValue.pNum->num);
	*/
	UTF8ToString(pContent->cmdObj.pageUrl, *(pTempObj->pObjPros[8].value.dValue.pStr));
	/*
	pContent->cmdObj.objectEncoding = (uint16_t)(pTempObj->pObjPros[9].value.dValue.pNum->num);
	*/

	//check number 4
	pTempData = pParse->m_Datas.at(3);

			
fail:
	if (pContent) delete pContent;
	pContent = NULL;
	return NULL;
}

Content* Connect::ParseConnect(AMF3::CParse *pParse)
{

}