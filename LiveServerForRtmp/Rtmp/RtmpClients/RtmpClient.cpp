#include "RtmpClient.h"
#include "Rtmp/Network/SocketIO.h"

CRtmpClient::CRtmpClient(uint32_t chunkSize, CSocketClient *io, CInstanceManager* appInstance):\
		m_IO(io), CChunks(chunkSize,appInstance)
{

}

CRtmpClient::~CRtmpClient()
{

}

void CRtmpClient::OnReceive()
{
	uint8_t *buf = NULL;
	size_t length = 0,newLength = 0,prevLength = 0,useLength = 0;
	int ret ;

	prevLength = m_Read.GetLength();
	newLength = m_IO->Read(NULL,0);
	length = prevLength + newLength;

	if (length < 0 )
		return ;

	buf = new uint8_t[length];
	m_Read.ReadOut(buf,prevLength);
	m_IO->Read(buf+prevLength,newLength);

	if (HandshakeEnd() == false)
	{
		useLength = OnHandshake(buf, length);
		m_Read.WriteIn(buf+useLength,length-useLength);
		if (HandshakeEnd() == true)
			return OnReceive();
	}
	else
	{
		useLength = OnChunks(buf, length);
		m_Read.WriteIn(buf + useLength, length - useLength);

		write2file("OnChunk", buf, useLength);
	}

	
	if (buf) delete[] buf;
	return;
}


void CRtmpClient::OnDisConnct()
{

}

void CRtmpClient::OnSockErr()
{

}
