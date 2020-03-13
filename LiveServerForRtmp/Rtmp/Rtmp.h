#pragma once

#include "../CoreModule.h"
#include "RtmpApp/RtmpApp.h"
#include "../SocketIO/IOBase.h"

class CRtmp : public CCoreModule ,
				public IIOMsg	
{
public:
	CRtmp();
	~CRtmp();
private:

	//CCoreModule
	 int InitCore() ;
	 int RunCore() ;
	 int RemoveCore();

	 //IIOMsg
	 void OnConnect(const int ioId) = 0;
	 void OnReceive(const int ioId) = 0;
	 void OnSend(const int ioId) = 0;
	 void OnClose(const int ioId) = 0;
	 void OnError(const int ioId) = 0;
	 
private:
	vector<CRtmpModule*> m_Apps;
	
};