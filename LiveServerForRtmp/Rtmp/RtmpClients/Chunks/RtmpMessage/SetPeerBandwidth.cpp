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

CBaseMessage* CSetPeerBandwidth::Encode(uint32_t timestamp, uint32_t msid, Object obj)
{
	CBaseMessage *pMsg = NULL;
	uint8_t *payload = NULL;
	uint32_t payloadLength = 0;

	payload = CSetPeerBandwidth::TranslatePayload(obj, &payloadLength);

	pMsg = new CBaseMessage(SET_PEER_BADNWIDTH_TYPE_ID,payloadLength,timestamp,msid,payload,payloadLength);
	return pMsg; 
}

uint8_t* CSetPeerBandwidth::TranslatePayload(Object obj,uint32_t* outLen)
{
	uint8_t *payload = NULL;
	uint32_t payloadLength = 0;
	uint32_t bigNum = 0;

	bigNum = HostToBig32(obj.ackWinSize);
	payloadLength = 5;
	payload = new uint8_t[5];

	memcpy(payload,&bigNum,4);
	memcpy(payload+4,&(obj.limitType),1);

	*outLen = payloadLength;
	return payload;
}

