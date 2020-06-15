#include "RtmpClient.h"
#include "Rtmp/RtmpApp/Network/SocketIO.h"

CRtmpClient::CRtmpClient(string appName, uint32_t chunkSize, CSocketClient *io):\
		m_IO(io), CChunks(appName,chunkSize),m_State(State::WAIT_HANDSHAKE)
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

}
void CRtmpClient::OnDisConnct()
{

}

void CRtmpClient::OnSockErr()
{

}



int CRtmpClient::Send2Peer(const uint8_t* src, const int srcLength)
{
	return 0;
}
