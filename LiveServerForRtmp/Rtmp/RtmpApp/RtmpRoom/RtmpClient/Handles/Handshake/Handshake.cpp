#include "Handshake.h"

#define RTMP_VERSION	0x03

CHandshake::CHandshake() : m_ReceType(ReceType::NONE),m_SendType(SendType::NONE),
						m_RecePack({0}),m_SendPack({0})
{
	
}

CHandshake::~CHandshake()
{

}

int CHandshake::OnHandshake(uint8_t* src, const int srcLength, uint32_t *outLen)
{
	int ret = HANDSHAKE_FAILURE;
	int length = 0;
	const bool receEnd = m_ReceType == ReceType::C2;
	const bool sendEnd = m_SendType == SendType::S2;

	if (receEnd && sendEnd)
		goto ReceSendEnd;

	ret = RecePacket(src,srcLength,&length);
	ret = SendPacket();

	*outLen = length;
	return HANDSHAKE_OK ;

ReceSendEnd:
	*outLen = 0;
	return ERROR_HANDSHAKE_END;
	
}

int CHandshake::RecePacket(uint8_t* buff, const int buffLen, int *outLen)
{
	int result = HANDSHAKE_FAILURE;
	int len = 0;
	ReceType rType = ReceType::NONE;

	if (buff == NULL || buffLen <= 0)	goto noData;
	
	switch (m_ReceType)
	{
	case CHandshake::NONE:
		result = ReceC0(buff, buffLen, &len);
		rType = ReceType::C0;
		break;
	case CHandshake::C0:
		result = ReceC1(buff, buffLen, &len);
		rType = ReceType::C1;
		break;
	case CHandshake::C1:
		result = ReceC2(buff, buffLen, &len);
		rType = ReceType::C2;
		break;
	case CHandshake::C2:
		rType = ReceType::C2;
		goto receEnd;
		break;
	default:
		rType = ReceType::C2;
		goto receEnd;
		break;
	}

	if (result != HANDSHAKE_OK)	goto outResult;

	m_ReceType = rType;
	*outLen += len;
	return RecePacket(buff+len,buffLen-len,outLen);

receEnd:
	*outLen += 0;
	return HANDSHAKE_OK;
outResult:
	*outLen += 0;
	return result;
noData:
	*outLen += 0;
	return HANDSHAKE_OK;
}

int CHandshake::ReceC0(uint8_t *buff, const int buffLen, int *outLen)
{	
	const int length = sizeof(m_RecePack.data0);
	if (buffLen < length)
		return ERROR_DATA_LOSS;

	if (*buff != RTMP_VERSION)
		return ERROR_VERSION;

	m_RecePack.data0 = *buff;

	*outLen = length;
	return HANDSHAKE_OK;
}

int CHandshake::ReceC1(uint8_t *buff, const int buffLen, int *outLen)
{
	const int length = sizeof(m_RecePack.data1);
	if (buffLen < length)
		return ERROR_DATA_LOSS;

	memcpy(m_RecePack.data1,buff, length);

	*outLen = length;
	return HANDSHAKE_OK;
}

int CHandshake::ReceC2(uint8_t *buff, const int buffLen, int *outLen)
{
	const int length = sizeof(m_RecePack.data2);
	if (buffLen < length)
		return ERROR_DATA_LOSS;
	memcpy(m_RecePack.data2,buff,length);
	*outLen = length;
	return HANDSHAKE_OK;
}

int CHandshake::SendPacket()
{
	int result = HANDSHAKE_FAILURE;
	const bool s0 = m_SendType == SendType::NONE && m_ReceType >= C0;
	const bool s1 = m_SendType == SendType::S1 && m_ReceType >= C1;
	const bool s2 = m_SendType == SendType::S2 && m_ReceType == C2;

	if (s0)
		result = SendS0();
	else if (s1)
		result = SendS1();
	else if (s2)
		result = SendS2();
	else 
		return HANDSHAKE_OK;

	return SendPacket();
}

int CHandshake::SendS0()
{
	const bool isSend = m_SendType >= SendType::S0;
	int length = 0;
	uint8_t version = RTMP_VERSION;
		
	if (isSend)		goto SEND;

	length = SendHandshake(&version,1);
	if (length != 1)
		return ERROR_SEND_HANDSHAKE;

	m_SendType = SendType::S0;
	m_SendPack.data0 = version;
	return HANDSHAKE_OK;

SEND:
	return HANDSHAKE_OK;
}
int CHandshake::SendS1()
{
	const bool isSend = m_SendType >= SendType::S1;
	int length = 0;
	uint32_t timestamp;
	uint8_t  s1[1536] = {0};

	if (isSend)		goto SEND;

	timestamp = GetTimestamp();
	timestamp = HostToBig32(timestamp);

	memcpy(s1, &timestamp, 4);				//timesamp
	memset(s1 + 4, 0, 4);					//zero
	GenRamdomByte((char*)(s1+4+4), 1528);	//random

	length = SendHandshake(s1,1536);
	if (length != 1536)
		return ERROR_SEND_HANDSHAKE;

	m_SendType = SendType::S1;
	memcpy(m_SendPack.data1,s1,1536);
	return HANDSHAKE_OK;

SEND:
	return HANDSHAKE_OK;
}

int CHandshake::SendS2()
{
	const bool isSend = m_SendType >= SendType::S2;
	int length = 0;
	uint8_t s2[1536] = {0};

	if (isSend)	goto SEND;

	memcpy(s2, m_RecePack.data1, 4);				// c1 timestamp
	memcpy(s2 + 4, m_SendPack.data1, 4);			// s1 timestamp
	memcpy(s2 + 4 + 4, m_SendPack.data1 + 8, 1528);	// s1 random 

	length = SendHandshake(s2, 1536);
	if (length != 1536)
		return ERROR_SEND_HANDSHAKE;

	m_SendType = SendType::S2;
	memcpy(m_SendPack.data2,s2,1536);
	return HANDSHAKE_OK;

SEND:
	return HANDSHAKE_OK;
}

int CHandshake::SendHandshake(const uint8_t *pSrc, const int srcLen)
{

}