#include "Connect.h"
using namespace Connect;

Content* Connect::ParseConnect(AMF0::CParse *pParse)
{
	Content* pContent = NULL;
	AMF0::Data *pData = NULL;
	bool valid = false;
	
	//check count
	valid = pParse->m_Datas.size() == 4;
	if (!valid) goto fail;
	
	//check number 1
	pData = pParse->m_Datas.at(0);
	valid = pData->dType == AMF0::MARKER_STRING || pData->dType == AMF0::MARKER_LONG_STRING;
	if (!valid) goto fail;
	valid = AMF0::UTF8IsEqual(COMMAND_NAME,(pData->dValue.pStr->utf8));
	if (!valid) goto fail;

	//check number 2 
	pData = pParse->m_Datas.at(1);

	//check number 3
	pData = pParse->m_Datas.at(2);

	//check number 4
	pData = pParse->m_Datas.at(3);

			
fail:
	if (pContent) delete pContent;
	pContent = NULL;
	return NULL;
}

Content* Connect::ParseConnect(AMF3::CParse *pParse)
{

}