#include "Airline.h"
#include <iostream>
using namespace std;

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

	for (int i = 0; i < 3; i++)
		airline.addCrewMember(*pilots[i]);
	for (int i = 0; i < 3; i++)
		airline.addCrewMember(*attendants[i]);

	//Create Flights
	Flight f1(&p1, Date(1, 2, 2015), "London", pilots[0]);
	Flight f2(&p2, Date(11, 12, 2015), "Tomsk", pilots[1]);
	Flight f3(&p1, Date(4, 9, 2015), "Rome", pilots[2]);
	Flight f4(&p3, Date(1, 2, 2015), "Tel-Aviv", pilots[0]);

	airline.addFlight(f1);
	airline.addFlight(f2);
	airline.addFlight(f3);
	airline.addFlight(f4);

	//add crew members
	airline.addStaffMemberToFlight(*attendants[1], f1);
	airline.addStaffMemberToFlight(*attendants[0], f1);
	airline.addStaffMemberToFlight(*pilots[1], f1);

	airline.addStaffMemberToFlight(*attendants[1], f2);
	airline.addStaffMemberToFlight(*attendants[2], f2);

	airline.addStaffMemberToFlight(*attendants[0], f3);
	airline.addStaffMemberToFlight(*pilots[1], f3);

	airline.addStaffMemberToFlight(*pilots[2], f4);

	//remove crew members
	airline.removeStaffMemberFromFlight(*attendants[0], f1);
	airline.removeStaffMemberFromFlight(*attendants[0], f2); // should not work
	airline.removeStaffMemberFromFlight(*attendants[0], f3);

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
	Order o1(Date(1, 1, 2015), customers[0]);
	o1 += airline.createTicketForFlight(f1);
	o1 += airline.createTicketForFlight(f1);
	o1 += airline.createTicketForFlight(f2);

	Order o2(Date(2, 1, 2015), customers[1]);
	o2 += airline.createTicketForFlight(f2);
	o2 += airline.createTicketForFlight(f3);

	Order o3(Date(11, 5, 2015), customers[2]);
	o3 += airline.createTicketForFlight(f2);
	o3 += airline.createTicketForFlight(f3);
	o3 += airline.createTicketForFlight(f4);

	Order o4(Date(5, 2, 2015), customers[2]);
	o4 += airline.createTicketForFlight(f2); // operator +=
	o4 += airline.createTicketForFlight(f3);

	airline.addOrder(o1);
	airline.addOrder(o2);
	airline.addOrder(o3);

	//remove some tickets
	o3 -= *(o3.getTickets()[2]); // operator -=
	o1 -= *(o1.getTickets()[1]);

	//Cancel an order
	airline.cancelOrder(o4);

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



	// Try some operators

	//operators +, ()
	Date d(1, 1, 2015);
	cout << d << endl;
	d = d + 5;
	cout << d << endl;
	d = 2 + d;
	cout << d << endl;
	d(2, 2, 2016);//operator()
	cout << d << endl;


	// operator []
	cout << "Find employee by name.. Enter a name : " << endl;
	char name[100];
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
			cout << ac << endl;
		}
	}//for

	if (!flag)
	{
		cout << "Did not found any staff member by the name " << name << endl;
	}



}//main