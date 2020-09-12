#include "RtmpClient.h"
#include "Rtmp/Network/SocketIO.h"
#include "ClientManager.h"

CRtmpClient::CRtmpClient(uint32_t chunkSize, CClientManager* pManager):\
		m_Manager(pManager), CChunks(chunkSize)
{

}

CRtmpClient::~CRtmpClient()
{

}

void CRtmpClient::Processing(uint8_t *buf, int bufLen)
{
	m_Read.WriteIn(buf, bufLen);
	return Processing();
}

void CRtmpClient::Processing()
{
	uint8_t *buf = NULL;
	size_t bufLength = 0 ,length = 0;
	int ret;

	buf = m_Read.GetData();
	bufLength = m_Read.GetLength();

	if (buf == NULL || bufLength == 0)
		return;

	if (HandshakeEnd() == false)
	{
		length = OnHandshake(buf, bufLength);
		if (HandshakeEnd() == true && bufLength > length)
			length += OnChunks(buf + length, bufLength-length);
	}
	else
		length = OnChunks(buf, length);
	
	m_Read.Seek(length);
	return;
}

int CRtmpClient::Send2Peer(uint8_t* src, const int srcLength)
{
	return m_Manager->WriteToUser(this, src, srcLength);
}