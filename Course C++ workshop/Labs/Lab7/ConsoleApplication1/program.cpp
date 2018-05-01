#include <iostream>
using namespace std;

#include "Cat.h"
#include "SiamiCat.h"
#include "StreetCat.h"
#include "SiamiStreetCat.h"


int main(void)
{

	//-----------------------------------
	Cat cat1("Gogo", "Yellow", 5);
	cout << cat1 << endl;
	//-----------------------------------


	cout << "--------------------------------" << endl;

	//-----------------------------------
	StreetCat streetCat1("Gogo", "Yellow", 5, 10);
	cout << streetCat1 << endl;

	StreetCat streetCat2(cat1, 10);
	cout << streetCat2 << endl;

	StreetCat streetCat3 = streetCat2 = streetCat1;//copy c'tor
	cout << streetCat3 << endl;
	//-----------------------------------


	cout << "--------------------------------" << endl;

	//-----------------------------------
	SiamiCat siamiCat1("Gogo", "Yellow", 5, "Tuna");
	cout << siamiCat1 << endl;

	SiamiCat siamiCat2(cat1, "Tuna");
	cout << siamiCat2 << endl;

	SiamiCat siamiCat3 = siamiCat2 = siamiCat1;
	cout << siamiCat3 << endl;
	//-----------------------------------

	cout << "--------------------------------" << endl;

	//-----------------------------------
	SiamiStreetCat siamiStreetCat1("Gogo", "Yellow", 5.3f, 10, "Tuna");
	cout << siamiStreetCat1 << endl;

	SiamiStreetCat siamiStreetCat2(streetCat1, siamiCat1);
	cout << siamiStreetCat2 << endl;
	//-----------------------------------

	return 0;
}