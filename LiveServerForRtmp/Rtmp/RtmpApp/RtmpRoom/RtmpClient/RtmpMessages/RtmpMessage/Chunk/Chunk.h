#pragma once

enum BasicHeaderType{INVALID,BASE0,BASE1,BASE2};
enum MessageHeaderType{ INVALID, MSG0,MSG1,MSG2,MSG3};
enum ExtendedTimestampType{ INVALID, EXT0,EXT1};



#include "stdafx.h"

class CChunk
{
private:
	CChunk(CChunk* prev,const int chunkSize);
	~CChunk();

public:
	static int GetByteLength(BasicHeaderType baseType);
	static int GetByteLength(MessageHeaderType msgType);
	static int GetByteLength(ExtendedTimestampType extType);
	static CChunk* DeMultiplexing(CChunk* pPrev,const int chunkSize,char* buff,const int buffLen,int* outChunkLen);

	void Destory() ;
	BasicHeaderType GetBaseHeaderType();
	MessageHeaderType GetMessageHeaderType();
	ExtendedTimestampType GetExtendedTimestamp() ;

private:
	int Demux(char* buff, const int buffLen, int* outChunkLen);

	int DemuxChunkHeader(char* buff, const int buffLen, int* outChunkHeaderLen);
	int DemuxBaseHeader(char* buff, const int buffLen, int* outBasicLen);
	int DemuxMsgHeader(char* buff, const int buffLen, int* outMsgLen);
	int DemuxExtendedTimestamp(char* buff, const int buffLen, int* outExtLen);

	int DemuxChunkData(char* buff, const int buffLen, int* outChunkDataLen);

private:
	BasicHeaderType m_BasicHeader;
	MessageHeaderType m_MsgHeader;
	ExtendedTimestampType m_ExTHeader;
	int m_ChunkDataLen;

	CChunk *m_Prev;
	int		m_ChunkSize;

};
