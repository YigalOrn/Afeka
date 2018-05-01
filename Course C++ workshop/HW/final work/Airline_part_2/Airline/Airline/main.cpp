/*This is a tester/driver program only*/

#include <iostream>
using namespace std;

#include "Airline.h"
#include "AirLineException.h"
#include "FlightException.h"


void main()
{

	//Create Airline
	Airline airline("EL-AL");


	//Create Planes
	Plane p1(50), p2, p3(200);

	airline.addPlane(p1);
	airline.addPlane(p2);
	airline.addPlane(p3);

	//Create Staff Members
	Pilot** pilots = new Pilot*[3];
	Attendant** attendants = new Attendant*[3];

	pilots[0] = new Pilot(Person("Ross", 32), 5, 35000, 2);
	pilots[1] = new Pilot(Person("Joey", 41), 11, 42000, 3);
	pilots[2] = new Pilot(Person("Chandler", 55), 25, 70000, 5);

	attendants[0] = new Attendant(Person("Phoebe", 20), 1, 5000);
	attendants[1] = new Attendant(Person("Rachel", 22), 2, 5750);
	attendants[2] = new Attendant(Person("Monica", 28), 3, 7000);

	//add some languages
	attendants[2]->addLanguage("Spanish");
	attendants[2]->addLanguage("French");


	for (int i = 0; i < 3; i++)
		airline.addCrewMember(*pilots[i]);
	for (int i = 0; i < 3; i++)
		airline.addCrewMember(*attendants[i]);

	//Create Flights
	Flight f1(&p1, Date(1, 2, 2025), "London");
	Flight f2(&p2, Date(11, 12, 2035), "Tomsk");
	Flight f3(&p1, Date(4, 9, 2045), "Rome");
	Flight f4(&p3, Date(13, 7, 2025), "Tel-Aviv");

	airline.addFlight(f1);
	airline.addFlight(f2);
	airline.addFlight(f3);
	airline.addFlight(f4);

	//add pilots
	airline.addStaffMemberToFlight(*pilots[0], f1);
	airline.addStaffMemberToFlight(*pilots[1], f2);
	airline.addStaffMemberToFlight(*pilots[2], f3);
	airline.addStaffMemberToFlight(*pilots[0], f4);

	//add crew members
	airline.addStaffMemberToFlight(*attendants[1], f1);
	airline.addStaffMemberToFlight(*attendants[0], f1);
	airline.addStaffMemberToFlight(*pilots[1], f1);

	airline.addStaffMemberToFlight(*attendants[1], f2);
	airline.addStaffMemberToFlight(*attendants[2], f2);

	airline.addStaffMemberToFlight(*attendants[0], f3);
	airline.addStaffMemberToFlight(*pilots[1], f3);

	airline.addStaffMemberToFlight(*pilots[2], f4);

	try
	{
		//remove crew members
		airline.removeStaffMemberFromFlight(*attendants[0], f1);
		airline.removeStaffMemberFromFlight(*attendants[0], f2); // should not work
		airline.removeStaffMemberFromFlight(*attendants[0], f3);
	}
	catch (FlightException& ex) {
		cout << ex.what() << endl;
	}
	catch (...)
	{
		cout << "catch(...)" << endl;
	}

	//Create Customers
	Customer** customers = new Customer*[3];

	customers[0] = new Customer(Person("Koko", 37));
	customers[1] = new Customer(Person("Momo", 21));
	customers[2] = new Customer(Person("Gogo", 45));

	for (int i = 0; i < 3; i++)
	{
		airline.addCustomer(*customers[i]);
	}


	//Create Orders
	cout << "Your order number is : "
		<< airline.addOrder(Date(1, 1, 2019), *customers[0]) << endl;
	int num;
	cout << "Enter order number : " << endl;
	cin >> num;
	if (airline.getOrder(num))
	{
		*airline.getOrder(num) += airline.createTicketForFlight(f1);
		*airline.getOrder(num) += airline.createTicketForFlight(f1);
		*airline.getOrder(num) += airline.createTicketForFlight(f2);
	}


	cout << "Your order number is : "
		<< airline.addOrder(Date(2, 1, 2019), *customers[1]) << endl;
	cout << "Enter order number : " << endl;
	cin >> num;
	if (airline.getOrder(num))
	{
		*airline.getOrder(num) += airline.createTicketForFlight(f2);
		*airline.getOrder(num) += airline.createTicketForFlight(f3);
	}


	cout << "Your order number is : "
		<< airline.addOrder(Date(2, 1, 2019), *customers[1]) << endl;
	cout << "Enter order number : " << endl;
	cin >> num;
	if (airline.getOrder(num))
	{
		*airline.getOrder(num) += airline.createTicketForFlight(f2);
		*airline.getOrder(num) += airline.createTicketForFlight(f3);
		*airline.getOrder(num) -= *(airline.getOrder(num)->getTickets()[1]);
	}

	//Cancel an order
	try
	{
		airline.cancelOrder(*airline.getOrder(num));
		airline.cancelOrder(*airline.getOrder(-888));//should not work
	}
	catch (AirLineException& ex)
	{
		cout << endl << ex.what() << endl;
	}
	catch (...)
	{
		cout << "catch(...)" << endl;
	}


	cout << airline << endl;

	//Free the allocations
	for (int i = 0; i < 3; i++)
		delete pilots[i];
	delete[]pilots;

	for (int i = 0; i < 3; i++)
		delete attendants[i];
	delete[]attendants;

	for (int i = 0; i < 3; i++)
		delete customers[i];
	delete[] customers;


	try
	{
		// Try some operators
		//operators +, ()
		Date d(1, 1, 2018);
		cout << d << endl;
		d = d + 5;
		cout << d << endl;
		d = 2 + d;
		cout << d << endl;
		d(2, 2, 2016);//operator()
		cout << d << endl;


		Date dateTest(1, 1, 2014);//this date has passed, should not work
	}
	catch (DateException& ex)
	{
		cout << ex.what() << endl;
	}
	catch (...)
	{
		cout << "catch(...)" << endl;
	}

	// operator []
	cout << endl << "Find employee by name.. Enter a name : " << endl;
	char name[100];
	cin.ignore();
	cin.getline(name, 100);
	int size = airline.getFlightsAmount();

	Flight*const* flights = airline.getFlights();


	int flag = 0;
	for (int i = 0; i < size; i++)
	{
		const AirCrew* const ac = (*flights[i])[name];
		if (ac != NULL)
		{
			flag = 1;
			cout << *ac << endl;
		}
	}//for

	if (!flag)
	{
		cout << "Did not found any staff member by the name " << name << endl;
	}



	cout << "# END OF PROGRAM #" << endl;

}//main