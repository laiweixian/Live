#include "Acknowledgement.h"

CAcknowledgement::CAcknowledgement()
{

}

CAcknowledgement::~CAcknowledgement()
{

}

int CAcknowledgement::Handle(CBaseMessage* pMsg)
{
	uint8_t buf[4] = {0};
	uint32_t sequenceNumber = 0;

	memcpy(buf,pMsg->GetData(),4);
	sequenceNumber = BigToHost32(buf);

	return AcknowledgementHandle(sequenceNumber);
}
