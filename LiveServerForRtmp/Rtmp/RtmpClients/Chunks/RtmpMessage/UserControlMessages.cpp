#include "UserControlMessages.h"

CUserControlMessages::CUserControlMessages()
{

}

CUserControlMessages::~CUserControlMessages()
{

}

CUserControlMessages::Object* CUserControlMessages::Decode(CBaseMessage* pMsg)
{
	CBaseMessage::Payload payload = pMsg->GetPayload();
	uint16_t eventType = 0;
	uint8_t eType[2] = {0};
	Object* pObj = NULL;

	pObj = new Object;

	memcpy(eType, payload.buf, 2);
	eventType = ::BigToHost16(eType);

	switch (eventType)
	{
	case E_T_STREAM_BEGIN:
		pObj->eType = STREAM_BEGIN;
		pObj->eData = CStreamBegin::Decode(pMsg);
		break;
	case E_T_STREAM_EOF:
		pObj->eType = STREAM_EOF;
		pObj->eData = CStreamEOF::Decode(pMsg);
		break;
	case E_T_STREAM_DRY:
		pObj->eType = STREAM_DRY;
		pObj->eData = CStreamDry::Decode(pMsg);
		break;
	case E_T_SET_BUFFER_LENGTH:
		pObj->eType = SET_BUFFER_LENGTH;
		pObj->eData = CSetBufferLength::Decode(pMsg);
		break;
	case E_T_STREAM_IS_RECORDED:
		pObj->eType = STREAM_IS_RECORDED;
		pObj->eData = CStreamIsRecorded::Decode(pMsg);
		break;
	case E_T_PING_REQUEST:
		pObj->eType = PING_REQUEST;
		pObj->eData = CPingRequest::Decode(pMsg);
		break;
	case E_T_PING_RESPONSE:
		pObj->eType = PING_RESPONSE;
		pObj->eData = CPingResponse::Decode(pMsg);
		break;
	default:
		break;
	}

	return pObj;
}

CBaseMessage* CUserControlMessages::Encode(uint32_t timestamp, uint32_t msid, CUserControlMessages::Object obj)
{
	return NULL;
}

void CUserControlMessages::FreeObject(CUserControlMessages::Object** ppObj)
{
	Object *pObj = *ppObj;
	CStreamBegin::Object *pEventData0 = NULL;
	CStreamEOF::Object *pEventData1 = NULL;
	CStreamDry::Object *pEventData2 = NULL;
	CSetBufferLength::Object *pEventData3 = NULL;
	CStreamIsRecorded::Object *pEventData4 = NULL;
	CPingRequest::Object *pEventData5 = NULL;
	CPingResponse::Object *pEventData6 = NULL;

	switch (pObj->eType)
	{
	case STREAM_BEGIN:
		pEventData0 =(CStreamBegin::Object *) pObj->eData;
		CStreamBegin::FreeObject(&pEventData0);
		break;

	case STREAM_EOF:
		pEventData1 = (CStreamEOF::Object *) pObj->eData;
		CStreamEOF::FreeObject(&pEventData1);
		break;

	case STREAM_DRY:
		pEventData2 = (CStreamDry::Object *) pObj->eData;
		CStreamDry::FreeObject(&pEventData2);
		break;

	case SET_BUFFER_LENGTH:
		pEventData3 = (CSetBufferLength::Object *) pObj->eData;
		CSetBufferLength::FreeObject(&pEventData3);
		break;

	case STREAM_IS_RECORDED:
		pEventData4 = (CStreamIsRecorded::Object *) pObj->eData;
		CStreamIsRecorded::FreeObject(&pEventData4);
		break;

	case PING_REQUEST:
		pEventData5 = (CPingRequest::Object *) pObj->eData;
		CPingRequest::FreeObject(&pEventData5);
		break;

	case PING_RESPONSE:
		pEventData6 = (CPingResponse::Object *) pObj->eData;
		CPingResponse::FreeObject(&pEventData6);
		break;

	default:
		break;
	}
	
	pObj->eData = NULL;
	delete (*ppObj);
	*ppObj = NULL;
}






