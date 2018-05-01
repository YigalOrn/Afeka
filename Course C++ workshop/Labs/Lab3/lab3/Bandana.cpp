#include <iostream>
using namespace std;

#include"Bandana.h"


/*C'tor*/
Bandana::Bandana()
{
}

/*Copy c'tor*/
Bandana::Bandana(const Bandana& other)
{
}

/*D'tor*/
Bandana::~Bandana()
{
	delete[]color;
}

void Bandana::setColor(const char const * color)
{
	memcpy(this->color, color, strlen(color)+1);
}