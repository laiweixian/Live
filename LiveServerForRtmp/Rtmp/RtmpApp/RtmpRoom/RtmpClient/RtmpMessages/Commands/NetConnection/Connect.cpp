#include "Connect.h"

ConnectCommand* CConnect::Parse(CAMF0* pamf)
{
	ConnectCommand *pcc = NULL;
	const vector<AMF0Data*> amfs = pamf->m_Amfs;
	const int amfDataCount = amfs.size();
	AMF0Data *pData = NULL;
	bool isInvalid = true;
	int i = 0;

	string commandName;
	int transactionID ;
	string name;

	if (amfDataCount != 4)
		return pcc;

	isInvalid = isInvalid && amfs.at(0)->dType == AMF0Type::STRING;
	isInvalid = isInvalid && amfs.at(1)->dType == AMF0Type::NUMBER;
	isInvalid = isInvalid && amfs.at(2)->dType == AMF0Type::OBJECT;
	isInvalid = isInvalid && amfs.at(3)->dType == AMF0Type::OBJECT;
	if (!isInvalid)
		return pcc;

	pcc = new ConnectCommand;

	//½«amf0 string ×ª»¯
	pData = amfs.at(0);
	commandName.copy((char*)pData->data_string.buff,pData->data_string.buffLength);

	pData = amfs.at(1);
	transactionID = static_cast<int>(pData->data_num);

	pData = amfs.at(2);
	for (i=0;i<pData->data_object.objCount; i++)
	{
		name.clear();
		name.copy((char*)pData->data_object.pObjs[i].name.buff,pData->data_object.pObjs[i].name.buffLength);
		
		if (name.compare("app") == 0)
		{
			if (pData->data_object.pObjs[i].data.dType != AMF0Type::STRING)	return NULL;
			pcc->commandObject.app.copy((char*)pData->data_object.pObjs[i].data.data_string.buff, pData->data_object.pObjs[i].data.data_string.buffLength);
		}
		else if (name.compare("flashver") == 0)
		{
			if (pData->data_object.pObjs[i].data.dType != AMF0Type::STRING)	return NULL;
			pcc->commandObject.flashver.copy((char*)pData->data_object.pObjs[i].data.data_string.buff, pData->data_object.pObjs[i].data.data_string.buffLength);
		}
		else if (name.compare("swfUrl") == 0)
		{
			if (pData->data_object.pObjs[i].data.dType != AMF0Type::STRING)	return NULL;
			pcc->commandObject.swfUrl.copy((char*)pData->data_object.pObjs[i].data.data_string.buff, pData->data_object.pObjs[i].data.data_string.buffLength);
		}
		else if (name.compare("tcUrl") == 0)
		{
			if (pData->data_object.pObjs[i].data.dType != AMF0Type::STRING)	return NULL;
			pcc->commandObject.tcUrl.copy((char*)pData->data_object.pObjs[i].data.data_string.buff, pData->data_object.pObjs[i].data.data_string.buffLength);
		}
		else if (name.compare("fpad") == 0)
		{
			if (pData->data_object.pObjs[i].data.dType != AMF0Type::BOOLEAN)	return NULL;
			pcc->commandObject.fpad = pData->data_object.pObjs[i].data.data_bool;
		}
		else if (name.compare("audioCodecs") == 0)
		{
			if (pData->data_object.pObjs[i].data.dType != AMF0Type::NUMBER)	return NULL;
			pcc->commandObject.audioCodecs = static_cast<int>(pData->data_object.pObjs[i].data.data_num);
		}
		else if (name.compare("videoCodecs") == 0)
		{
			if (pData->data_object.pObjs[i].data.dType != AMF0Type::NUMBER)	return NULL;
			pcc->commandObject.videoCodecs = static_cast<int>(pData->data_object.pObjs[i].data.data_num);
		}
		else if (name.compare("videoFunction") == 0)
		{
			if (pData->data_object.pObjs[i].data.dType != AMF0Type::NUMBER)	return NULL;
			pcc->commandObject.videoFunction = static_cast<int>(pData->data_object.pObjs[i].data.data_num);
		}
		else if (name.compare("pageUrl") == 0)
		{
			if (pData->data_object.pObjs[i].data.dType != AMF0Type::STRING)	return NULL;
			pcc->commandObject.pageUrl.copy((char*)pData->data_object.pObjs[i].data.data_string.buff, pData->data_object.pObjs[i].data.data_string.buffLength);
		}
		else if (name.compare("objectEncoding") == 0)
		{
			if (pData->data_object.pObjs[i].data.dType != AMF0Type::NUMBER)	return NULL;
			pcc->commandObject.objectEncoding = static_cast<int>(pData->data_object.pObjs[i].data.data_num);
		}
		else
		{
			return NULL;
		}
	}


	
	return pcc;
}

ConnectCommand* CConnect::Parse(CAMF3* pamf)
{

}

void CConnect::ConnectCommand_Free(ConnectCommand** ppcc)
{
	if (*ppcc == NULL)
		return;

	delete (*ppcc);
	*ppcc = NULL;
}