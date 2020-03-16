#pragma once

#include "stdafx.h"

enum BasicHeaderType{INVALID,BASE0,BASE1,BASE2};
enum MessageHeaderType{ INVALID, MSG0,MSG1,MSG2,MSG3};
enum ExtendedTimestampType{ INVALID, EXT0,EXT1};

enum ChunkHeaderFieldType
{
	FMT,CSID,
	TIMESTAMP,TIMESTAMP_DELTA,MESSAGE_LENGTH,MESSAGE_TYPE_ID,MESSAGE_STREAM_ID,
	EXTENDED_TIMESTAMP
};

class ChunkHeaderField
{
public:
	ChunkHeaderField(ChunkHeaderFieldType fieldType,const char *data,const int dataLen) {
		m_Type = fieldType;
		m_DataLen = dataLen;
		m_Data = new char[m_DataLen];
		memcpy(m_Data,data,m_DataLen);
	}
	~ChunkHeaderField() {
		delete[] m_Data;
		m_Data = NULL;
	}

	void Copy(void* buff, int *outBuffLen)
	{
		if (!buff)
		{
			*outBuffLen = m_DataLen;
			return;
		}

		memcpy(buff,m_Data,m_DataLen);
		*outBuffLen = m_DataLen;

		return;
	}

public:
	ChunkHeaderFieldType m_Type;
	char *m_Data;
	int m_DataLen;
};



class CChunk
{
private:
	CChunk();
	~CChunk();

public:
	
	static CChunk* DeMultiplexing(char* buff,const int buffLen,int* outChunkLen);

	void Destory() ;
	
	int GetHeaderLength();
	
	BasicHeaderType GetBaseHeaderType();
	MessageHeaderType GetMessageHeaderType();
	ExtendedTimestampType GetExtendedTimestampType();

	//将信息转换成大端数据类型并返回
	int GetFMT(uint8_t *pFmt);
	int GetCSID(uint32_t *pCsid);
	int GetTimestamp(uint32_t *pTs);
	int GetTimestampDelta(uint32_t *pTsDelta);
	int GetMessageLength(uint32_t *pMsgLen);
	int GetMessageTypeID(uint8_t *pMsgTypeID);
	int GetMessageStreamID(uint32_t *pMsgStreamID);
	int GetExtendedTimestamp(uint32_t *pExTs);
private:
	void Restore();

	
	int Demux(char* buff, const int buffLen, int* outChunkLen);
	//chunk header
	int DemuxChunkHeader(char* buff, const int buffLen, int* outChunkHeaderLen);
	int DemuxBaseHeader(char* buff, const int buffLen, int* outBasicLen);
	int DemuxMsgHeader(char* buff, const int buffLen, int* outMsgLen);
	int DemuxExtendedTimestamp(char* buff, const int buffLen, int* outExtLen);
private:
	static int GetByteLength(BasicHeaderType baseType);
	static int GetByteLength(MessageHeaderType msgType);
	static int GetByteLength(ExtendedTimestampType extType);


private:


	BasicHeaderType m_BasicHeader;
	MessageHeaderType m_MsgHeader;
	ExtendedTimestampType m_ExT;
	int m_ChunkDataLen;

	CChunk *m_Prev;
	int		m_ChunkSize;

	vector<ChunkHeaderField*> m_Fields;
};
