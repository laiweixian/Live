#include "Handshake.h"

#define RTMP_VERSION	0x03

CHandshake::CHandshake(IHandshakeEvent* pEvent) : m_Event(pEvent),
												  m_ReceType(ReceType::NONE),m_SendType(SendType::NONE),
												  m_RecePack({0}),m_SendPack({0})
{
	
}

CHandshake::~CHandshake()
{

}

int CHandshake::OnHandshake(uint8_t* src, const int srcLength)
{
	int ret = SAR_FAILURE;
	int length = 0;
	ret = ReiceivePacket((char*)src, srcLength,&length);

	if (ret != SAR_OK)
		return 0;
	else 
		return length;
}

int CHandshake::ReiceivePacket(char* buff, const int buffLen, int *outLen)
{
	int result = SAR_FAILURE;
	int c0Len = 0 , c1Len = 0 , c2Len = 0;

	if (m_ReceType == ReceType::NONE)
	{
		result = SAR_OK;
		result &= ReceiveC0(buff, buffLen, &c0Len);
		result &= ReceiveC1(buff+c0Len,buffLen - c0Len,&c1Len);
		if (result == SAR_OK)
		{
			m_ReceType = C1;
			SendS0_S1();

			*outLen = c0Len + c1Len;
			return result;
		}
	}
	else if (m_ReceType == C1)
	{
		result = SAR_OK;
		result &= ReceiveC2(buff,buffLen,&c2Len);
		if (result == SAR_OK)
		{
			m_ReceType = C2;
			SendS2();
			*outLen = c2Len;
			return result;
		}
	}
	else
	{
		*outLen = 0 ;
		return SAR_FAILURE;
	}

	
	*outLen = 0;
	return result;
receive_complete:
	*outLen += 0;
	return SAR_OK;
}

int CHandshake::ReceiveC0(char *buff, const int buffLen, int *outLen)
{	
	const int length = sizeof(m_RecePack.data0);
	if (buffLen < length)
		return DATA_LACK;

	memcpy(m_RecePack.data0,buff, length);
	if (m_RecePack.data0[0] != RTMP_VERSION)
		return RTMP_VERSION_ERR;

	*outLen = length;
	return SAR_OK;
}

int CHandshake::ReceiveC1(char *buff, const int buffLen, int *outLen)
{
	const int length = sizeof(m_RecePack.data1);
	if (buffLen < length)
		return DATA_LACK;

	memcpy(m_RecePack.data1,buff, length);
	*outLen = length;
	return SAR_OK;
}

int CHandshake::ReceiveC2(char *buff, const int buffLen, int *outLen)
{
	const int length = sizeof(m_RecePack.data2);
	if (buffLen < length)
		return DATA_LACK;
	memcpy(m_RecePack.data2,buff,length);
	*outLen = length;
	return SAR_OK;
}

void CHandshake::SendS0_S1()
{
	uint32_t timestamp;
	char randomMark[1528] = {0};
	const char zeroMark[4] = {0};
	bool bSucc = true;

	m_SendPack.data0[0] = RTMP_VERSION;

	timestamp = GetTimestamp();
	timestamp = HostToBig32(timestamp);
	GenRamdomByte(randomMark, 1528);
	memcpy(m_SendPack.data1, &timestamp, 4);
	memcpy(m_SendPack.data1 + 4, zeroMark, 4);
	memcpy(m_SendPack.data1 + 4+4, randomMark, 1528);

	m_SendType = S1;
	
	bSucc &= m_Event->OnSendHandshake(m_SendPack.data0,1);
	bSucc &= m_Event->OnSendHandshake(m_SendPack.data1,1536);
	
}

void CHandshake::SendS2()
{
	bool bSucc = true;

	memcpy(m_SendPack.data2, m_SendPack.data1, 4);;
	memcpy(m_SendPack.data2 + 4, m_SendPack.data1, 4);
	memcpy(m_SendPack.data2 + 4 + 4, m_SendPack.data1 + 8, 1528);

	m_SendType = S2;
	bSucc &= m_Event->OnSendHandshake(m_SendPack.data2, 1536);
}	