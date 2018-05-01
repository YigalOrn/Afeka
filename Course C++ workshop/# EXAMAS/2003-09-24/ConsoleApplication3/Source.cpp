class A
{
	int i;
public:
	A(int j) : i(j)
	{}
	operator int()
	{
		return i;
	}
};//A

class B :public A
{
	int j;
public:
	B(A a) : A(a), j(a)
	{}

	void operator=(const B& otherB) {}

};//B

void main()
{
	B Bobj(31);
	A Aobj(36);

	Aobj = Bobj;
	Bobj = Aobj;

	B *p = &Aobj;

}//main