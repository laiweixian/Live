#include "RtmpClient.h"
#include "Rtmp/RtmpApp/Network/SocketIO.h"

CRtmpClient::CRtmpClient(uint32_t chunkSize, CSocketClient *io, CInstanceManager* appInstance):\
		m_IO(io), CChunks(chunkSize),m_AppInstance(appInstance)
{

}

CRtmpClient::~CRtmpClient()
{

}

CSocketClient* CRtmpClient::GetClietnIo()
{
	return m_IO;
}

CInstanceManager* CRtmpClient::GetRtmpInstance()
{
	return m_AppInstance;
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
		if (useLength < length)
			m_Read.WriteIn(buf+useLength,length-useLength);
		if (HandshakeEnd() == true)
			return OnReceive();
	}
	else
	{
		useLength = OnChunks(buf, length);
		if (useLength < length)
			m_Read.WriteIn(buf + useLength, length - useLength);
	}

	if (buf) delete[] buf;
	TRACE("Handle Dta:%d\n", length);

	return;
}


void CRtmpClient::OnDisConnct()
{

}

void CRtmpClient::OnSockErr()
{

}

int CRtmpClient::Send2Peer( uint8_t* src, const int srcLength)
{
	return m_IO->Write(src,srcLength);
}
