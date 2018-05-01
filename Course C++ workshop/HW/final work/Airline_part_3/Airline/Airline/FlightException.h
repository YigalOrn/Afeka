#ifndef __FlightException_H_
#define __FlightException_H_

#include <string>

class FlightException
{
	string msg;

public:

	FlightException(const string& newMsg)
	{
		msg.assign(newMsg);
	}

	const string what() const
	{
		return msg;
	};
};

#endif //__FlightException_H_
