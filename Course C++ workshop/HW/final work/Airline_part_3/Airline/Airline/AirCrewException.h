#ifndef __AirCrewException_H_
#define __AirCrewException_H_

#include <string>

class AirCrewException
{
	string msg;

public:
	AirCrewException(const string& newMsg)
	{
		msg.assign(newMsg);
	}

	const string what() const
	{
		return msg;
	};
};

#endif //__AirCrewException_H_










