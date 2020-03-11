#include "Modules/IOStreams/TCP_IPV4/Ipv4.h"

CIPV4 G_IPV4;

CIPV4::CIPV4() : m_Active(FALSE) ,\
				 m_Ip(IPV4_IP),\
				 m_Port(IPV4_PORT),\
				 m_MaxConnect(IPV4_MAX_CONNECT),\
				 m_TimeOut(IPV4_TIME_OUT),
				 m_EventName(IPV4_EVENT_NAME)
{
	register_io_stream(this);
}

CIPV4::~CIPV4()
{

}

ULONG CIPV4::Init()
{
	return SAR_OK;
}

ULONG CIPV4::Run()
{
	return SAR_OK;
}

ULONG CIPV4::Release()
{
	return SAR_OK;
}

const char* CIPV4::GetIOStreamName()
{
	return IPV4_NAME;
}

BOOL CIPV4::Active()
{
	return m_Active;
}

ULONG CIPV4::Open()
{
	return SAR_OK;
}

ULONG CIPV4::Read(const int ioID, char* dst, const int dstLen)
{
	return SAR_OK;
}

ULONG CIPV4::Write(const int ioID, char* dst, const int dstLen)
{
	return SAR_OK;
}

ULONG CIPV4::Seek(const int ioID, EIOPos pos, const int offset)
{
	return SAR_OK;
}

ULONG CIPV4::Close(const int ioID)
{
	return SAR_OK;
}

ULONG CIPV4::InitSocket()
{
	

	return SAR_OK;
}