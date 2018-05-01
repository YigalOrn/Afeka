#include "Airline.h"

Airline::Airline(
	const string name,
	int maxNumberOfFlights,
	int maxNumberOfPlanes,
	int maxNumberOfCustomers,
	int maxNumberOfCrewMembers,
	int maxNumberOfOrders) :
	maxNumberOfFlights(maxNumberOfFlights),
	maxNumberOfPlanes(maxNumberOfPlanes),
	maxNumberOfCustomers(maxNumberOfCustomers),
	maxNumberOfCrewMembers(maxNumberOfCrewMembers),
	maxNumberOfOrders(maxNumberOfOrders)
{
	setName(name);
	numberOfPlanes = 0;
}

Airline::~Airline()
{
	vector<AirCrew*>::iterator crewIter = crewVec.begin();
	for (; crewIter < crewVec.end(); ++crewIter)
	{
		delete (*crewIter);
	}
}//calls planesList d'tor and airlineName string

void Airline::setName(const string name) throw(AirLineException)
{
	if (!name.empty())
	{
		airlineName.assign(name);
	}
	else
	{
		throw AirLineException(string("# Airline Name cannot be empty #"));
	}
}

void Airline::addFlight(const Flight& f) throw(AirLineException, const string&)
{
	Plane* plane = 0;

	if (flightsVec.size() >= maxNumberOfFlights)
	{
		throw AirLineException(
			string("# Number of flights exceeded its max capacity #"));
	}

	plane = &(planesList.isElementOfList(*f.getPlane()));

	
	vector<Flight>::iterator flightIter =
		find(flightsVec.begin(), flightsVec.end(), f);

	/*
	vector<Flight>::iterator flightIter = flightsVec.begin();
	for (; flightIter < flightsVec.end(); ++flightIter)
	{
		if (*flightIter == f)
		{
			break;
		}
	}
	*/

	if (flightIter == flightsVec.end())
	{
		flightsVec.push_back( Flight(f, plane) );
	}
}

void Airline::addPlane(const Plane& p) throw (AirLineException)
{
	if (numberOfPlanes >= maxNumberOfPlanes)
	{
		throw AirLineException(
			string("# Number of planes exceeded its max capacity #"));
	}

	try
	{
		planesList.isElementOfList(p);
	}
	catch (const string& ex)
	{
		planesList.insertAfterTail(p);
		numberOfPlanes++;
	}
}
void Airline::addCustomer(const Customer& c) throw (AirLineException)
{

	if (customersVec.size() >= maxNumberOfCustomers)
	{
		throw AirLineException(
			string("# Number of customers exceeded its max capacity #"));
	}

	vector<Customer>::iterator custIter =
		find(customersVec.begin(), customersVec.end(), c);

	if (custIter == customersVec.end())
	{
		customersVec.push_back(Customer(c));
	}
}

void Airline::addCrewMember(const AirCrew& ac) throw (AirLineException)
{
	if (crewVec.size() >= maxNumberOfCrewMembers)
	{
		throw AirLineException(
			string("# Number of crew members exceeded its max capacity #"));
	}
	
	vector<AirCrew*>::iterator crewIter = crewVec.begin();
	for (; crewIter < crewVec.end(); ++crewIter)
	{
		if (*(*crewIter) == ac) 
		{
			break;
		}
	}

	if (crewIter == crewVec.end())
	{
		crewVec.push_back(ac.clone());
	}
}

int Airline::addOrder(const Date& date, const Customer& cust)
throw (AirLineException)
{
	if (ordersVec.size() >= maxNumberOfOrders)
	{
		throw AirLineException(
			string("# Number of orders exceeded its max capacity #"));
	}

	vector<Customer>::iterator custIter =
		find(customersVec.begin(), customersVec.end(), cust);

	if (custIter != customersVec.end())
	{
		Order o(Order(date, &(*custIter)));

		/*
		cout << "11111111111111"<<endl<< o << endl;/DEBUG
		*/

		ordersVec.push_back(o);
		return ordersVec.back().getOrderId();
	}
	else
	{
		string msg(cust.getName());
		msg.append(" is not a customer of the airline");
		throw AirLineException(msg);
	}
}

Order* Airline::getOrder(int orderId) throw (AirLineException)
{
	typedef vector<Order>::iterator Iter;
	for (Iter orderIter = ordersVec.begin(); orderIter < ordersVec.end();
	++orderIter)
	{
		if (orderIter->getOrderId() == orderId)
		{
			return &(*orderIter);
		}
	}


	string msg; 
	stringstream sstm;
	sstm << "# Order with id : " << orderId << " does't exist #";
	msg = sstm.str();

	throw AirLineException(msg);
	return NULL;
}

ostream& operator<<(ostream& out, const Airline& a)
{
	out << "*************************************************" << endl;
	out << "Airline name : " << a.getAirlineName() << endl;
	out << "*************************************************" << endl;

	out << "Planes : " << endl;
	out << "*************************************************" << endl;
	
	a.getPlanes().print(out);
	
	out << endl;
	out << "*************************************************" << endl;

	
	out << "Flights : " << endl;
	out << "*************************************************" << endl;

	ostream_iterator<Flight> flightsToPrint(out,"");
	copy(a.flightsVec.begin(), a.flightsVec.end(), flightsToPrint);

	out << "*************************************************" << endl;


	out << "AirCrew size: " << a.getAirCrewsAmount() << endl;
	out << "AirCrews : " << endl;
	out << "*************************************************" << endl;
	vector<AirCrew*>::const_iterator crewIter = a.crewVec.begin();
	for (; crewIter < a.crewVec.end(); ++crewIter)
	{
		out << *(*crewIter) << endl;
	}
	out << "*************************************************" << endl;


	out << "Orders : " << endl;
	ostream_iterator<Order> ordersToPrint(out,"");
	copy(a.ordersVec.begin(), a.ordersVec.end(), ordersToPrint);
	out << "*************************************************" << endl;


	out << "Customers : " << endl;
	out << "*************************************************" << endl;

	ostream_iterator<Customer> customersToPrint(out,"");
	copy(a.customersVec.begin(), a.customersVec.end(), customersToPrint);

	out << "*************************************************" << endl;
	return out;
}


const vector<Flight>& Airline::getFlights() const
{
	return flightsVec;
}

int Airline::getFlightsAmount() const
{
	return flightsVec.size();
}

const List<Plane>& Airline::getPlanes() const
{
	return planesList;
}

int Airline::getPlanesAmount() const
{
	return numberOfPlanes;
}

const vector<Customer>& Airline::getCustomers() const
{
	return customersVec;
}

int Airline::getCustomersAmount() const
{
	return customersVec.size();
}

const vector<AirCrew*>& Airline::getAirCrews() const
{
	return crewVec;
}

int Airline::getAirCrewsAmount() const
{
	return crewVec.size();
}

const vector<Order>& Airline::getOrders() const
{
	return ordersVec;
}

int Airline::getOrdersAmount() const
{
	return ordersVec.size();
}

int Airline::getAmountOfTicketsInFlight(const Flight& f) const
{
	typedef vector<Flight>::const_iterator Iter;
	for (Iter flightIter = flightsVec.begin(); flightIter < flightsVec.end();
	++flightIter)
	{
		if (*flightIter == f)
		{
			return flightIter->getAmountOfTakenSeats();
		}
	}
}

void Airline::addStaffMemberToFlight(AirCrew& ac, Flight& f)
throw (AirLineException, FlightException)
{

	vector<Flight>::iterator flightIter = flightsVec.begin();
	for (; flightIter < flightsVec.end() ; ++flightIter)
	{
		if (*flightIter == f) 
		{
			break;
		}
	}

	vector<AirCrew*>::iterator crewIter = crewVec.begin();
	for (; crewIter < crewVec.end(); ++crewIter)
	{
		if ( *(*crewIter) == ac)
		{
			break;
		}
	}


	if (flightIter != flightsVec.end() && crewIter != crewVec.end())
	{
		
		//cout << **crewIter << endl;

		//add new crew member
		flightIter->addStaffMember( *(*crewIter) );
	}
	else
	{
		throw AirLineException(string("# Either flight or staff does not exist in airline #"));
	}
}

void Airline::removeStaffMemberFromFlight(AirCrew& ac, const Flight& f)
throw (AirLineException, FlightException)
{
	vector<Flight>::iterator flightIter = flightsVec.begin();
	for (; flightIter < flightsVec.end(); ++flightIter)
	{
		if (*flightIter == f)
		{
			break;
		}
	}

	vector<AirCrew*>::iterator crewIter = crewVec.begin();
	for (; crewIter < crewVec.end(); ++crewIter)
	{
		if (*(*crewIter) == ac)
		{
			break;
		}
	}

	if (flightIter != flightsVec.end() && crewIter != crewVec.end())
	{
		flightIter->removeStaffMember(**crewIter);
	}
	else
	{
		throw AirLineException(string("# Either flight or staff does not exists in airline #"));
	}
}

const Ticket Airline::createTicketForFlight(Flight& f)
throw (AirLineException, FlightException)
{
	vector<Flight>::iterator flightIter =
		find(flightsVec.begin(), flightsVec.end(), f);

	return Ticket(*flightIter,
		flightIter->getNextFreeSeat(),
		flightIter->getFlightDate());
}

void Airline::cancelOrder(const Order& o) throw(AirLineException)
{
	vector<Order>::iterator orderIter =
		find(ordersVec.begin(), ordersVec.end(), o);
	ordersVec.erase(orderIter);
}


Array<Flight>* Airline::getWantedFlights(const string& destToSearch, const Date& dateToSearch) const throw(AirLineException)
{

	Array<Flight>* wantedFlights = new Array<Flight>();
	vector<Flight>::const_iterator itr = flightsVec.begin();

	for (; itr!= flightsVec.end(); ++itr)
	{
		if ((*itr).getFlightDate() <= dateToSearch 
			&& (*itr).getDestination() == destToSearch) 
		{
			wantedFlights->push_back( (*itr) );
		}
	}
	return wantedFlights;
}
