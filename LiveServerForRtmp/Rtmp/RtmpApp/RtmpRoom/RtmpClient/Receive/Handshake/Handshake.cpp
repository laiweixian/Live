#include "Handshake.h"

#define RTMP_VERSION	0x03

CHandshake::CHandshake() 
{
	m_Receive = {0};
	m_Send = {0};
	m_RecieveStatus = NO_RECEIVE;
	m_SendStatus = NO_SEND;
}

CHandshake::~CHandshake()
{

}

int CHandshake::OnRequest(uint8_t* src, const int srcLength)
{
	int ret = SAR_FAILURE;
	int length = 0;
	ret = ReiceivePacket((char*)src, srcLength,&length);

	if (ret != SAR_OK)
		return 0;
	else 
		return length;
}

DataHandleType CHandshake::GetType()
{
	return DataHandleType::HANDSHAKE;	
}

void* CHandshake::GetResponse(int* outLen) const
{

}

int CHandshake::ReiceivePacket(char* buff, const int buffLen, int *outLen)
{
	int receLen = 0 ;
	int result = SAR_FAILURE;

	if (m_RecieveStatus == C2 || !buff || buffLen <= 0)
		goto receive_complete;
		
	switch (m_RecieveStatus)
	{
	case NO_RECEIVE:
		result = ReceiveC0(buff, buffLen,&receLen);
		if (result == SAR_OK)
		{
			m_RecieveStatus = C0;
			InitS0();
		}
			
		break;
	case C0:
		result = ReceiveC1(buff, buffLen, &receLen);
		if (result == SAR_OK)
		{
			m_RecieveStatus = C1;
			InitS1();
		}
			
		break;
	case C1:
		result = ReceiveC2(buff, buffLen, &receLen);
		if (result == SAR_OK)
		{
			m_RecieveStatus = C2;
			InitS2();
		}
			
		break;
	case C2:
		goto receive_complete;
		break;
	default:
		goto receive_complete;
		break;
	}

	*outLen += receLen;
	if (result == SAR_OK)
		return  ReiceivePacket(buff + receLen,buffLen-receLen, outLen);
	else
	{
		*outLen += 0;
		return result;
	}

receive_complete:
	*outLen += 0;
	return SAR_OK;
}

int CHandshake::ReceiveC0(char *buff, const int buffLen, int *outLen)
{	
	const int length = sizeof(m_Receive.data0);
	if (buffLen < length)
		return DATA_LACK;

	memcpy(m_Receive.data0,buff, length);
	if (m_Receive.data0[0] != RTMP_VERSION)
		return RTMP_VERSION_ERR;

	*outLen = length;
	return SAR_OK;
}

int CHandshake::ReceiveC1(char *buff, const int buffLen, int *outLen)
{
	const int length = sizeof(m_Receive.data1);
	if (buffLen < length)
		return DATA_LACK;

	memcpy(m_Receive.data1,buff, length);
	*outLen = length;
	return SAR_OK;
}

int CHandshake::ReceiveC2(char *buff, const int buffLen, int *outLen)
{
	const int length = sizeof(m_Receive.data2);
	if (buffLen < length)
		return DATA_LACK;
	memcpy(m_Receive.data2,buff,length);
	*outLen = length;
	return SAR_OK;
}


int CHandshake::InitS0()
{
	int sendLen = 0;
	const int length = sizeof(m_Send.data0);
	const char rtmpVersion = RTMP_VERSION;
	memcpy(m_Send.data0,&rtmpVersion,length);
	m_SendStatus = SendHandshakeType::S0;
	return SAR_OK;
}

int CHandshake::InitS1()
{
	int sendLen = 0;
	const int length = sizeof(m_Send.data1);
	uint32_t timestamp ; 
	char zeroMark[4] = {0};
	char randomMark[1528] = {0};
	int offset = 0;

	timestamp = GetTimestamp();
	timestamp = HostToBig32(timestamp);
	GenRamdomByte(randomMark,1528);

	memcpy(m_Send.data1,&timestamp,4);	offset += 4;
	memcpy(m_Send.data1+offset,zeroMark,4); offset+= 4;
	memcpy(m_Send.data1+offset,randomMark,1528); offset += 1528;
	m_SendStatus = SendHandshakeType::S1;
	return SAR_OK;
}

int CHandshake::InitS2()
{
	int sendLen = 0;
	const int length = sizeof(m_Send.data2);
	int offset = 0;
	memcpy(m_Send.data2,m_Receive.data1,4);		offset += 4;
	memcpy(m_Send.data2+offset,m_Send.data1,4); offset += 4;
	memcpy(m_Send.data2+offset,m_Send.data1+8,1528); offset += 1528;
	m_SendStatus = SendHandshakeType::S2;
	return SAR_OK;
}