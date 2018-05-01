#ifndef __DateException_H_
#define __DateException_H_

#include <string>

class DateException
{
	string msg;

public:
	DateException(const string& newMsg)
	{
		msg.assign(newMsg);
	}

	const string what() const
	{
		return msg;
	};
};

#endif //__DateException_H_










