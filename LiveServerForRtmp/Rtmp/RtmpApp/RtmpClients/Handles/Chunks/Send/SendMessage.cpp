#include "SendMessage.h"

CSendMessage::CSendMessage()
{

}

CSendMessage::~CSendMessage()
{

}

int CSendMessage::Send(CRtmpMessage* pSend)
{
	uint8_t *fmt = NULL, *csid = NULL, \
		*ts = NULL, *tsDelta = NULL, *msglen = NULL, *msgTypeId = NULL, *msgStreamId = NULL, \
		*exts = NULL;
	uint32_t fmtSize = 0, csidSize = 0, \
		tsSize = 0, tsDeltaSize = 0, msgLenSize = 0, msgTypeIdSize = 0, msgStreamIdSize = 0, \
		extsSize = 0;
	uint8_t* buf = NULL;
	uint32_t bufSize = 0;
	return -1;
}