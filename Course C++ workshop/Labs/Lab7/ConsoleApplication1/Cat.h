#ifndef __Cat_h
#define __Cat_h

class Cat
{


public:

	Cat(const char* name, const char* mColor, float mLen);
	~Cat();
	Cat(const Cat& other);

	void setName(const char*);
	const char* const getName() const;

	void setMcolor(const char*);
	const char* const getMcolor() const;

	void setLen(const float len);
	float getLen() const;


	friend ostream& operator<<(ostream& os, const Cat& other);
	
	//supports multiple assignment
	Cat& operator=(const Cat& other);


private:

	char* name;
	char* mColor;
	float mLen;


	
};


#endif//__Cat_h