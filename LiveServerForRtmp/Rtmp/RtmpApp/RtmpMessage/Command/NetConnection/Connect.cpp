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
	string name;

	pTempData = parse->m_Datas.at(0);
	valid = AMF0::IsString(*pTempData);
	if (!valid)
		goto fail;
	
	AMF0::CopyString(name,*pTempData);
	
	if (strcmp(name.data(),COMMAND_NAME) != 0)
		goto fail;

	return true;
fail:

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
	char *buff = NULL;
	int buffLen = 0;

	pTempData = parse->m_Datas.at(2);
	if (pTempData->dType != AMF0::MARKER_OBJECT)
		goto fail;
	
	pObj = pTempData->dValue.pObj;

	//member count
	if (pObj->count != 10)
		goto fail;

	//member name
	for (i=0;i<pObj->count;i++)
	{
		ret = AMF0::Utf8Cmp(COMMAND_OBJECT_MEMBER_NAME[i],pObj->pMems[i].name);
		if (ret != 0)
			goto fail;
	}

	//member data type
	valid &= AMF0::IsString(pObj->pMems[0].value);
	valid &= AMF0::IsString(pObj->pMems[1].value);
	valid &= AMF0::IsString(pObj->pMems[2].value);
	valid &= AMF0::IsString(pObj->pMems[3].value);
	valid &= AMF0::IsBoolean(pObj->pMems[4].value);
	valid &= AMF0::IsNumber(pObj->pMems[5].value);
	valid &= AMF0::IsNumber(pObj->pMems[6].value);
	valid &= AMF0::IsNumber(pObj->pMems[7].value);
	valid &= AMF0::IsString(pObj->pMems[8].value);
	valid &= AMF0::IsNumber(pObj->pMems[9].value);
	if (!valid)
		goto fail;

	//copy member value to local
	CopyString(m_Obj.App, pObj->pMems[0].value);
	CopyString(m_Obj.Flashver, pObj->pMems[1].value);
	CopyString(m_Obj.SwfUrl, pObj->pMems[2].value);
	CopyString(m_Obj.TcUrl, pObj->pMems[3].value);
	CopyBoolean(m_Obj.Fpad, pObj->pMems[4].value);
	CopyNumber(m_Obj.AudioCodecs, pObj->pMems[5].value);
	CopyNumber(m_Obj.VideoCodecs, pObj->pMems[6].value);
	CopyNumber(m_Obj.VideoFunction, pObj->pMems[7].value);
	CopyString(m_Obj.PageUrl, pObj->pMems[8].value);
	CopyNumber(m_Obj.ObjectEncoding, pObj->pMems[9].value);

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
	return false;
}

bool CContent::CheckCommandName(AMF3::CParse* parse)
{
	return false;
}

bool CContent::CheckTransactionID(AMF3::CParse* parse)
{
	return false;
}

bool CContent::CheckCommandObject(AMF3::CParse* parse)
{
	return false;
}

bool CContent::CheckOptionalUserArgumemts(AMF3::CParse* parse)
{
	return false;
}