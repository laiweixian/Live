#pragma once

//Process ,when connect done
//1.(Receive) Command Message (createStream)
//2.(Send) Command Message (_result)

class CCreateStreamMission
{
public:
	struct Object { };
protected:
	CCreateStreamMission();
	virtual ~CCreateStreamMission();

};
