/*
http://stackoverflow.com/questions/32679584/initialization-of-objects-with-temporary-objects-in-c

https://en.wikipedia.org/wiki/Copy_elision#cite_note-C.2B.2B03_12.8.2F15-1

http://en.cppreference.com/w/cpp/language/copy_elision

*/

#include <iostream>

int n = 0;

struct C {
	explicit C(int) {}
	C(const C&) { ++n; } // the copy constructor has a visible side effect
						 // it modifies an object with static storage duration

	//C(C&&) = delete;//move c'tor

};                     

int main() {
	C c1(42); // direct-initialization, calls C::C(42)
	C c2 = C(42); // copy-initialization, calls C::C( C(42) )
	//C c3 = c1;

	std::cout << n << std::endl; // prints 0 if the copy was elided, 1 otherwise
	return 0;
}//main