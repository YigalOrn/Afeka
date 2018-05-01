#ifndef __DateException_H_
#define __DateException_H_

#include <cstring>

class DateException
{
	char* msg;

public:

	DateException(const char* newMsg)
	{
		msg = strdup(newMsg);
	}

	const char* what() const
	{
		return msg;
	};
};

#endif //__DateException_H_










