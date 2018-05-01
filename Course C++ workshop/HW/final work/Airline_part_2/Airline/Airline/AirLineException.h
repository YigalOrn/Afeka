#ifndef __AirLineException_H_
#define __AirLineException_H_

#include <cstring>

class AirLineException
{
	char* msg;
	
public:

	AirLineException(const char* newMsg)
	{
		msg = strdup(newMsg);
	}

	const char* what() const
	{
		return msg;
	};
};

#endif //__AirLineException_H_










