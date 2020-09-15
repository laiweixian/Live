#include "SetPeerBandwidth.h"

CSetPeerBandwidth::CSetPeerBandwidth()
{

}

CSetPeerBandwidth::~CSetPeerBandwidth()
{

}

CSetPeerBandwidth::Object* CSetPeerBandwidth::Decode(CBaseMessage* pMsg)
{
	return NULL;
}

void CSetPeerBandwidth::FreeObject(Object** ppObj)
{
	delete (*ppObj);
	*ppObj = NULL;
}

