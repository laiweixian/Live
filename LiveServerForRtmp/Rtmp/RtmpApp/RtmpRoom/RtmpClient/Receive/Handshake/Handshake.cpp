#include "Handshake.h"

#define RTMP_VERSION	0x03

CHandshake::CHandshake(IHandshakeRespose *pRespose) : m_Respose(pRespose)
{
	m_ReceivePacket = {0};
	m_SendPacket = {0};
	m_RecieveType = HandshakeReceiveType::INVALID;
	m_SendType = HandshakeSendType::INVALID;
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



	if (m_RecieveType == HandshakeReceiveType::INVALID)
	{
		result = SAR_OK;
		result &= ReceiveC0(buff, buffLen, &c0Len);
		result &= ReceiveC1(buff+c0Len,buffLen - c0Len,&c1Len);
		if (result == SAR_OK)
		{
			m_RecieveType = C1;
			result = SendS0_S1();

			*outLen = c0Len + c1Len;
			return result;
		}
	}
	else if (m_RecieveType == C1)
	{
		result = SAR_OK;
		result &= ReceiveC2(buff,buffLen,&c2Len);
		if (result == SAR_OK)
		{
			m_RecieveType = C2;
			result = SendS2();
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
	const int length = sizeof(m_ReceivePacket.data0);
	if (buffLen < length)
		return DATA_LACK;

	memcpy(m_ReceivePacket.data0,buff, length);
	if (m_ReceivePacket.data0[0] != RTMP_VERSION)
		return RTMP_VERSION_ERR;

	*outLen = length;
	return SAR_OK;
}

int CHandshake::ReceiveC1(char *buff, const int buffLen, int *outLen)
{
	const int length = sizeof(m_ReceivePacket.data1);
	if (buffLen < length)
		return DATA_LACK;

	memcpy(m_ReceivePacket.data1,buff, length);
	*outLen = length;
	return SAR_OK;
}

int CHandshake::ReceiveC2(char *buff, const int buffLen, int *outLen)
{
	const int length = sizeof(m_ReceivePacket.data2);
	if (buffLen < length)
		return DATA_LACK;
	memcpy(m_ReceivePacket.data2,buff,length);
	*outLen = length;
	return SAR_OK;
}

void CHandshake::SendS0_S1()
{
	uint32_t timestamp;
	char randomMark[1528] = {0};
	const char zeroMark[4] = {0};

	m_SendPacket.data0[0] = RTMP_VERSION;

	timestamp = GetTimestamp();
	timestamp = HostToBig32(timestamp);
	GenRamdomByte(randomMark, 1528);
	memcpy(m_SendPacket.data1, &timestamp, 4);	
	memcpy(m_SendPacket.data1 + 4, zeroMark, 4);
	memcpy(m_SendPacket.data1 + 4+4, randomMark, 1528);

	m_SendType = S1;
	m_Respose->S0(m_SendPacket.data0,1);
	m_Respose->S1(m_SendPacket.data1, 1536);
}

void CHandshake::SendS2()
{
	memcpy(m_SendPacket.data2, m_ReceivePacket.data1, 4);;
	memcpy(m_SendPacket.data2 + 4, m_SendPacket.data1, 4);
	memcpy(m_SendPacket.data2 + 4 + 4, m_SendPacket.data1 + 8, 1528);

	m_SendType = S2;
	m_Respose->S2(m_SendPacket.data2, 1536);
}	