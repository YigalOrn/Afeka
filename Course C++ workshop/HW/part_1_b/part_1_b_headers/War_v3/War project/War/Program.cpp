#include <iostream>
#include <typeinfo>
using namespace std;

#include "War.h"
#include "Army.h"
#include "Soldier.h"
#include "Infantry.h"
#include "Pilot.h"
#include "MonStars.h"
#include "DogZilla.h"
#include "SiamAmurai.h"
#include "GodZilla.h"
#include "AmmunitionType.h"


//relevant to all char arrays.
const int MAX_STR_LEN = 20;


//prototypes
template<typename T>
static void initArmy(T**);


int main(void)
{
	//prototypes
	void printMenu();

	void  createWar(War**);
	void finishWar(War&);
	void hit(War&);
	void showWarStatistics(War&);
	void supplyAmmunition(War&);
	void refuelAirCraft(War&);
	void feedForce(War&);
	void lineUpTheTroops(War&);
	void addFighter(War&);
	//------------------

	int choice;//switch parameter
	bool proceed = true;//while flag

	War* warPtr = 0;

	do
	{
		printMenu();
		cin >> choice;//notice default catches all other inputs...
		cout << "Your choice is : " << choice << endl;

		switch (choice)
		{
		case 1:
		{
			createWar(&warPtr);
			cout << "# War has started #" << endl;
			break;
		}
		case 2:
		{
			hit(*warPtr);
			break;
		}
		case 3:
		{
			showWarStatistics(*warPtr);
			break;
		}
		case 4:
		{
			supplyAmmunition(*warPtr);
			break;
		}
		case 5:
		{
			refuelAirCraft(*warPtr);
			break;
		}
		case 6:
		{
			feedForce(*warPtr);
			break;
		}
		case 7:
		{
			addFighter(*warPtr);
			break;
		}
		case 8:
		{
			lineUpTheTroops(*warPtr);
			break;
		}
		case 9:
		{
			proceed = false;

			//check if war has started	
			if (warPtr->areWeAtWar() == true)
			{
				finishWar(*warPtr);
			}
			else
			{
				//in case the player/user enters and exit right a way
				cout << "# We live in peace! #" << endl;
			}


			//free allocation, do housekeeping
			delete warPtr;
			warPtr = 0;

			break;
		}
		default:
		{
			//implementation dependent could be an exception
			cout << "# Your choice is undefined #" << endl;
			break;
		}

		} //switch

	} while (proceed);

	return 0;
}

void createWar(War** warPtrPtr)
{
	
	Army* armyPtr = 0;
	MonStars* monStarsPtr = 0;

	initArmy(&armyPtr);//template
	initArmy(&monStarsPtr);//template

	//if you want check memory allocation using exceptions

	*warPtrPtr = new War(armyPtr, monStarsPtr);//*..Ptr on heap
	(*warPtrPtr)->setWarStarted(true);

	return;
}//createWar

template<typename T>
void initArmy(T** campPtr)
{
	char name[MAX_STR_LEN];
	cout << "Enter the name for " << (typeid(**campPtr).name() + 6) << " camp : " << endl;
	cin.getline(name, MAX_STR_LEN);

	//soldiers/animals array is dynamic i.e its size is controlled by class Army object, on heap.
	*campPtr = new T(name);

}//initArmy
//------------------------------------------

void finishWar(War& warRef)
{
	//prototypes
	void showWarStatistics(War&);

	warRef.setWarStarted(false);
	showWarStatistics(warRef);
	
}//finishWar

void hit(War& warRef)
{
	//policy : the user will need to create at least one fighter at each camp (using the menu options) before attempting to hit. 
	//check this in hit(), could use an exception
	//the return is a string telling the user who was the attacker and who was the casualty 
	cout << warRef.hit() << endl;
}//hit

void showWarStatistics(War& warRef)
{
	cout << warRef << endl;
}//showWarStatistics

void supplyAmmunition(War& warRef)
{
	int index;
	static char* str =
		"# Ammunition is scarce Commander... #\n"
		"Choose ammunition type to supply : ";
	cout << str << endl;
	for (int i = 0; i < ammunitionTypesSize; i++)
	{
		//showing available ammunition types as strings
		cout << (i + 1) << ")" << ammunitionTypes[i] << endl;
	}//for_i
	cin >> index;

	//the war class/manager class should infer using the ammunition type to whom she should supply
	warRef.supplyAmmunition((AmmunitionType)(index - 1));
}//supplyAmmunition

void refuelAirCraft(War& warRef)
{
	int amount;
	static char* str =
		"# We are out of fuel Commander ! our planes are falling like flies...#\n"
		"Please enter the amount of fuel : ";
	cout << str << endl;
	cin >> amount;
	warRef.refuelAirCraft(amount);
}//refuelAirCraft

void feedForce(War& warRef)
{
	float amount;
	static char* str =
		"# The soldiers are hungry Commander... #\n"
		"Please enter the amount of food (in kg) : ";
	cout << str << endl;
	cin >> amount;
	warRef.feedForce(amount);
}//feedForce

void lineUpTheTroops(War& warRef)
{
	cout << "# Roger that, attention! #" << endl;
	cout << warRef.lineUpTheTroops() << endl;;
}//lineUpTheTroops

void addFighter(War& warRef)
{
	int choice;
	static char* str =
		"Please choose a fighter : \n"
		"1)Army Infantry\n"
		"2)Army Pilot\n"
		"3)MonStars DogZilla\n"
		"4)MonStars GodZilla\n"
		"5)MonStars SiamAmurai";
	cout << str << endl;
	cin >> choice;

	switch (choice)
	{
	case 1:
	{
		char name[MAX_STR_LEN];
		int armyNumber;
		float foodKgAmount;
		int numOfHoursBeingAwake;

		cout << "Enter Infantry name:" << endl;
		cin.getline(name, MAX_STR_LEN);
		cin.ignore();
		cout << "Enter Soldier id, food amount, hours being awake: " << endl;
		cin >> armyNumber >> foodKgAmount >> numOfHoursBeingAwake;

		Soldier *soldierPtr = new Infantry(name, armyNumber, foodKgAmount, numOfHoursBeingAwake);
		warRef.addSoldier(soldierPtr);
		
		break;
	}
	case 2:
	{
		char name[MAX_STR_LEN];
		int armyNumber;
		float foodKgAmount;
		int numOfHoursFlied;

		cout << "Enter Pilot name:" << endl;
		cin.getline(name, MAX_STR_LEN);
		cin.ignore();
		cout << "Enter Soldier id, food amount, num of hours flied: " << endl;
		cin >> armyNumber >> foodKgAmount >> numOfHoursFlied;

		Soldier *soldierPtr = new Infantry(name, armyNumber, foodKgAmount, numOfHoursFlied);
		warRef.addSoldier(soldierPtr);
		
		break;
	}
	case 3:
	{

		char name[MAX_STR_LEN];
		int amountOfSoldiersKilled;
		int stomachSize;

		cout << "Enter DogZilla name:" << endl;
		cin.getline(name, MAX_STR_LEN);
		cin.ignore();
		cout << "Enter amount of soldiers killed, stomach size: " << endl;
		cin >> amountOfSoldiersKilled >> stomachSize;


		Animal *animalPtr = new DogZilla(name, amountOfSoldiersKilled, stomachSize);
		warRef.addAnimal(animalPtr);
		
		break;
	}
	case 4:
	{

		char name[MAX_STR_LEN];
		int amountOfSoldiersKilled;
		int stomachSize;
		int clutchesSharpness;
		int fireHeatPower;

		cout << "Enter GodZilla name:" << endl;
		cin.getline(name, MAX_STR_LEN);
		cin.ignore();
		cout << "Enter amount of soldiers killed, stomach size, clutches sharpness, firePower: " << endl;
		cin >> amountOfSoldiersKilled >> stomachSize >> clutchesSharpness >> fireHeatPower;

		Animal *animalPtr = new GodZilla(name, amountOfSoldiersKilled, stomachSize, clutchesSharpness, fireHeatPower);
		warRef.addAnimal(animalPtr);
		
		break;
	}
	case 5:
	{
		char name[MAX_STR_LEN];
		int amountOfSoldiersKilled;
		int clutchesSharpness;

		cout << "Enter SiamAmurai name:" << endl;
		cin.getline(name, MAX_STR_LEN);
		cin.ignore();
		cout << "Enter amount of soldiers killed, clutches sharpness: " << endl;
		cin >> amountOfSoldiersKilled >> clutchesSharpness;

		Animal *animalPtr = new SiamAmurai(name, amountOfSoldiersKilled, clutchesSharpness);
		warRef.addAnimal(animalPtr);

		break;
	}
	default:
	{
		//implementation dependent, could loop...
		cout << "# Your choice is undefined #" << endl;
		break;
	}

	}//switch

}//addFighter

void printMenu()
{
	static char* menuStr =
		"Please enter your choice : \n"
		"1 - start the war\n"
		"2 - hit\n"
		"3 - show war statistics\n"
		"4 - supply ammunition\n"
		"5 - refuel the aircraft\n"
		"6 - feed the force\n"
		"7 - add a fighter\n"
		"8 - line up the troops\n"
		"9 - end the war and exit\n";
	cout << menuStr << endl;
} // printMenu

