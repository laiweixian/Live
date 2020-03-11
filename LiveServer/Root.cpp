#include "Root.h"

CRoot* CRoot::S_Root = NULL;

ULONG register_base_module(CBaseModule *pBase)
{
	return CRoot::GetInstance()->RegisterBaseModule(pBase);
}

CRoot::CRoot()
{

}

CRoot::~CRoot()
{

}

CRoot* CRoot::GetInstance()
{
	if (!S_Root)
		S_Root = new CRoot;
	return S_Root;
}

void CRoot::Destory()
{
	delete this;
	S_Root = NULL;
}

ULONG CRoot::RegisterBaseModule(CBaseModule* pModule)
{
	//��֤ģ��Ψһ��(root�Ѿ���ȫ���˰�������Ĺ���)
	if (!pModule)
		return ROOT_MODULE_NULL;

	const char* name = pModule->GetBaseModuleName();
	vector<CBaseModule*>::iterator it;
	CBaseModule *tempModule = NULL;
	int maxLen = 0;

	for (it = m_BaseModules.begin();it != m_BaseModules.end(); it++)
	{
		tempModule = *it;
		if (strcmp(name, tempModule->GetBaseModuleName()) == 0)
			return ROOT_MODULE_REPEAT;
	}
	m_BaseModules.push_back(pModule);
}