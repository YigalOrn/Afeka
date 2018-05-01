#ifndef __AirLineException_H_
#define __AirLineException_H_

#include <string>

class AirLineException
{
	string msg;
	
public:
	AirLineException(const string& newMsg)
	{
		msg.assign(newMsg);
	}

	const string what() const
	{
		return msg;
	};
};

#endif //__AirLineException_H_










