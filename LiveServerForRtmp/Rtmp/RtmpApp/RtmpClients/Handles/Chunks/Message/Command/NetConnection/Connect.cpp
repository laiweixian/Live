#include "Connect.h"


CConnect::CConnect()
{

}

CConnect::~CConnect()
{

}

CConnect* CConnect::Create(AMF0::CParse* parse)
{
	CConnect* pContent = NULL;
	bool valid = false;


	return NULL;
}

CConnect* CConnect::Create(AMF3::CParse* parse)
{
	return NULL;
}

string CConnect::GetCommandName()
{
	string name = COMMAND_NAME;
	return name;
}

int CConnect::GetTransactionID()
{
	return TRANSACTION_ID;
}

CConnect::CmdObj CConnect::GetCmdObj()
{
	return m_Obj;
}


bool CConnect::CheckOut(AMF0::CParse* parse)
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

bool CConnect::CheckCommandName(AMF0::CParse* parse)
{
	return false;
}

bool CConnect::CheckTransactionID(AMF0::CParse* parse)
{
	return false;
}

bool CConnect::CheckCommandObject(AMF0::CParse* parse)
{
	return false;
}

bool CConnect::CheckOptionalUserArgumemts(AMF0::CParse* parse)
{
	return false;
}

bool CConnect::CheckOut(AMF3::CParse* parse)
{
	return false;
}

bool CConnect::CheckCommandName(AMF3::CParse* parse)
{
	return false;
}

bool CConnect::CheckTransactionID(AMF3::CParse* parse)
{
	return false;
}

bool CConnect::CheckCommandObject(AMF3::CParse* parse)
{
	return false;
}

bool CConnect::CheckOptionalUserArgumemts(AMF3::CParse* parse)
{
	return false;
}