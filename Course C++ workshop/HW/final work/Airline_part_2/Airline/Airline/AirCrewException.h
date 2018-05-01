#ifndef __AirCrewException_H_
#define __AirCrewException_H_

#include <cstring>

class AirCrewException
{
	char* msg;

public:

	AirCrewException(const char* newMsg)
	{
		msg = strdup(newMsg);
	}

	const char* what() const
	{
		return msg;
	};
};

#endif //__AirCrewException_H_










