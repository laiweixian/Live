#include "RtmpClient.h"
#include "Rtmp/RtmpApp/Network/SocketIO.h"

CRtmpClient::CRtmpClient(string appName, uint32_t chunkSize, CSocketClient *io):\
		m_IO(io), CChunks(appName,chunkSize)
{

}

CRtmpClient::~CRtmpClient()
{

}

CSocketClient* CRtmpClient::GetClietnIo()
{
	return m_IO;
}

void CRtmpClient::OnReceive()
{
	int length = 0;



	
	
	if (HandshakeEnd() == false)
	{
		length = OnHandshake(m_Buff.GetData(), m_Buff.GetLength());
		ret = m_Buff.Offset(length);
	}
	else
	{
		length = OnChunks(m_Buff.GetData(), m_Buff.GetLength());
		ret = m_Buff.Offset(length);
	}

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
