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
	int length = 0;
	UpdateReadBuff();

	if (m_Readable.GetLength() <= 0)
		return;

	if (HandshakeEnd() == false)
		length = OnHandshake(m_Readable.GetData(), m_Readable.GetLength());
	else
		length = OnChunks(m_Readable.GetData(),m_Readable.GetLength());

	m_Readable.Seek(length);
	
	if (m_Readable.GetLength() > 0)
		return OnReceive();

	return;
}

void CRtmpClient::UpdateReadBuff()
{
	int length = 0;
	uint8_t *buf = NULL;

	length = m_IO->Read(NULL, 0);
	if (length <= 0 )
		return;

	buf = new uint8_t[length];
	length = m_IO->Read(buf,length);
	m_Readable.Append(buf,length);
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
