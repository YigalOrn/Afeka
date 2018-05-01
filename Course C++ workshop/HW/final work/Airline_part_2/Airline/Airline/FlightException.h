#ifndef __FlightException_H_
#define __FlightException_H_

#include <cstring>

class FlightException
{
	char* msg;

public:

	FlightException(const char* newMsg)
	{
		msg = strdup(newMsg);
	}

	const char* what() const
	{
		return msg;
	};
};

#endif //__FlightException_H_
