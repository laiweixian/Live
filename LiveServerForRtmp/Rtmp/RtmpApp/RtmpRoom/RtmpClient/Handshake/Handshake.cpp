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

int CHandshake::OnReceive(char *buff, const int buffLen)
{
	int receLen = 0 , sendLen = 0;
	int receResult = SAR_FAILURE , sendResult = SAR_FAILURE;

	if (m_SendStatus == S2 && m_RecieveStatus == C2)
		return 0;

	receResult = ReiceivePacket(buff,buffLen,&receLen);
	sendResult = SendPakcet(&sendLen);

	if (receResult != SAR_OK)
		return 0;
	
	return (OnReceive(buff+receLen,buffLen-receLen) + receLen);
}

int CHandshake::ReiceivePacket(char *buff, const int buffLen, int *outLen)
{
	int receLen = 0;
	int result = SAR_FAILURE;

	if (m_RecieveStatus == C2)
		return 0;

	switch (m_RecieveStatus)
	{
	case NO_RECEIVE:
		result = ReceiveC0(buff, buffLen,&receLen);
		if (result == SAR_OK)
			m_RecieveStatus = C0;
		break;
	case C0:
		result = ReceiveC1(buff, buffLen, &receLen);
		if (result == SAR_OK)
			m_RecieveStatus = C1;
		break;
	case C1:
		result = ReceiveC2(buff, buffLen, &receLen);
		if (result == SAR_OK)
			m_RecieveStatus = C2;
		break;
	case C2:
		result = SAR_OK;
		break;
	default:
		result = SAR_OK;
		break;
	}

	*outLen = receLen;
	return result;
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

int CHandshake::SendPakcet(int *outLen)
{
	int sendLen = 0;
	int result = SAR_FAILURE;

	if (m_SendStatus == S2)
		return 0;
	
	switch (m_SendStatus)
	{
	case NO_SEND:
		result = SendS0(&sendLen);
		if (result == SAR_OK)
			m_SendStatus = S0;
		break;
	case S0:
		result = SendS1(&sendLen);
		if (result == SAR_OK)
			m_SendStatus = S1;
		break;
	case S1:
		result = SendS2(&sendLen);
		if (result == SAR_OK)
			m_SendStatus = S2;
		break;
	case S2:
		result = SAR_OK;
		break;
	default:
		result = SAR_OK;
		break;
	}

	*outLen = sendLen;
	return result;
}

int CHandshake::SendS0(int *outLen)
{
	int sendLen = 0;
	const int length = sizeof(m_Send.data0);
	const char rtmpVersion = RTMP_VERSION;
	memcpy(m_Send.data0,&rtmpVersion,length);

	sendLen = SendToPeer((char*)m_Send.data0,length);	
	if (sendLen != length)
		return SEND_DATA_FAILURE;
	
	*outLen = sendLen;
	return SAR_OK;
}

int CHandshake::SendS1(int *outLen)
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
	sendLen = SendToPeer((char*)m_Send.data1, length);
	if (sendLen != length)
		return SEND_DATA_FAILURE;
	*outLen = sendLen;
	return SAR_OK;
}

int CHandshake::SendS2(int *outLen)
{
	int sendLen = 0;
	const int length = sizeof(m_Send.data2);
	int offset = 0;

	memcpy(m_Send.data2,m_Receive.data1,4);		offset += 4;
	memcpy(m_Send.data2+offset,m_Send.data1,4); offset += 4;
	memcpy(m_Send.data2+offset,m_Send.data1+8,1528); offset += 1528;
	sendLen = SendToPeer((char*)m_Send.data2, length);
	if (sendLen != length)
		return SEND_DATA_FAILURE;
	*outLen = sendLen;
	return SAR_OK;
}