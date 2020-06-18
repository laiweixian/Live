#include "Handshake.h"
#include "stdafx.h"

#define RTMP_VERSION	0x03

CHandshake::CHandshake() : m_ReceState(RECE_NONE),m_SendState(SEND_NONE),
						m_RecePack({0}),m_SendPack({0})
{
	
}

CHandshake::~CHandshake()
{

}

bool CHandshake::HandshakeEnd()
{
	const bool s = m_SendState == S2;
	const bool r = m_ReceState == C2;
	return (r&&s);
}

int CHandshake::OnHandshake(uint8_t* src, const int srcLength)
{
	int ret = HANDSHAKE_FAILURE;
	int length = 0;

	if (HandshakeEnd())
		return 0;

	ret = RecePacket(src,srcLength,&length);
	ret = SendPacket();

	write2file(TEXT("RTMP"), src, length);
	return length;
}

int CHandshake::RecePacket(uint8_t* buff, const int buffLen, int *outLen)
{
	int result = HANDSHAKE_OK;
	int length = 0;
	int len0 = 0, len1 = 0;

	if (m_ReceState == RECE_NONE)
	{
		result &= ReceC0(buff, buffLen, &len0);
		result &= ReceC1(buff + len0, buffLen - len0, &len1);
		length = len0 + len1;
	}
	else if (m_ReceState == C1)
	{
		result = ReceC2(buff, buffLen, &length);
	}
	else if (m_ReceState == C2)
	{
		return HANDSHAKE_OK;
	}
	else 
	{
		*outLen = 0;
		return HANDSHAKE_OK;
	}

	*outLen = length;
	return result;
}

int CHandshake::ReceC0(uint8_t *buff, const int buffLen, int *outLen)
{	
	const int length = 1;
	if (buffLen < length)
		return HANDSHAKE_FAILURE;
	if (m_ReceState != RECE_NONE)
		return HANDSHAKE_FAILURE;

	memcpy(m_RecePack.data0,buff,length);

	m_ReceState = C0;
	*outLen = length;
	TRACE("Receive c0 success\n");

	return HANDSHAKE_OK;
}

int CHandshake::ReceC1(uint8_t *buff, const int buffLen, int *outLen)
{
	const int length = 1536;
	if (buffLen < length)
		return HANDSHAKE_FAILURE;
	if (m_ReceState != C0)
		return HANDSHAKE_FAILURE;

	memcpy(m_RecePack.data1,buff, length);

	m_ReceState = C1;
	*outLen = length;
	TRACE("Receive c1 success\n");
	return HANDSHAKE_OK;
}

int CHandshake::ReceC2(uint8_t *buff, const int buffLen, int *outLen)
{
	const int length = 1536;
	if (buffLen < length)
		return HANDSHAKE_FAILURE;
	if (m_ReceState != C1)
		return HANDSHAKE_FAILURE;

	memcpy(m_RecePack.data2,buff,length);

	m_ReceState = C2;
	*outLen = length;
	TRACE("Receive c2 success\n");
	return HANDSHAKE_OK;
}

int CHandshake::SendPacket()
{
	int result = HANDSHAKE_FAILURE;

	if (m_SendState == SEND_NONE)
		result = SendS0();
	if (m_SendState == S0)
		result = SendS1();
	if (m_SendState == S1)
		result = SendS2();
	else 
		return HANDSHAKE_OK;

	if (m_ReceState == m_SendState && result == HANDSHAKE_OK)
		return HANDSHAKE_OK;
	
	return result;
}

int CHandshake::SendS0()
{
	int length; 

	if (m_SendState != SEND_NONE)
		return HANDSHAKE_FAILURE;
	
	
	length = Send2Peer(m_RecePack.data0,1);
	if (length == 1)
	{
		TRACE("send s0 success\n");
		m_SendState = S0;
		m_SendPack.data0[0] = 0x03;
		return HANDSHAKE_OK;
	}

	return HANDSHAKE_FAILURE;
}

int CHandshake::SendS1()
{
	int length = 0;
	uint32_t timestamp;
	uint8_t  s1[1536] = {0};

	if (m_SendState != S0)
		return HANDSHAKE_FAILURE;

	timestamp = GetTimestamp();
	timestamp = HostToBig32(timestamp);

	memcpy(s1, &timestamp, 4);				//timesamp
	memset(s1 + 4, 0, 4);					//zero
	GenRamdomByte((char*)(s1+4+4), 1528);	//random

	length = SendHandshake(s1,1536);
	if (length == 1536)
	{
		TRACE("send s1 success\n");
		m_SendState = S1;
		memcpy(m_SendPack.data1, s1, 1536);
		return HANDSHAKE_FAILURE;
	}
	return HANDSHAKE_OK;
}

int CHandshake::SendS2()
{
	int length = 0;
	uint8_t s2[1536] = {0};

	if (m_SendState != S1)
		return HANDSHAKE_FAILURE;

	memcpy(s2, m_RecePack.data1, 4);				// c1 timestamp
	memcpy(s2 + 4, m_SendPack.data1, 4);			// s1 timestamp
	memcpy(s2 + 4 + 4, m_SendPack.data1 + 8, 1528);	// s1 random 

	length = SendHandshake(s2, 1536);
	if (length == 1536)
	{
		TRACE("send s2 success\n");
		m_SendState = S2;
		memcpy(m_SendPack.data2, s2, 1536);
		return HANDSHAKE_OK;
	}
	return HANDSHAKE_FAILURE;
}

int CHandshake::SendHandshake( uint8_t *pSrc, const int srcLen)
{
	return Send2Peer(pSrc,srcLen);
}