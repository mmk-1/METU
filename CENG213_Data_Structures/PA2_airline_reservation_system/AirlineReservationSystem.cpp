#include "AirlineReservationSystem.h"

void AirlineReservationSystem::addPassenger(const std::string &firstname, const std::string &lastname)
{
    /* TODO */
    BSTNode<Passenger> *r = this->passengers.getRoot();
    if (checkPassengers(r, firstname, lastname))
    {
        this->passengers.insert(Passenger(firstname, lastname));
    }
    else
    {
        return;
    }
}

Passenger *AirlineReservationSystem::searchPassenger(const std::string &firstname, const std::string &lastname)
{
    /* TODO */

    BSTNode<Passenger> *searchRes = this->passengers.search(Passenger(firstname, lastname));
    if (searchRes == NULL)
    {
        return NULL;
    }
    Passenger *res = &(searchRes->data);

    return res;
}

void AirlineReservationSystem::addFlight(const std::string &flightCode, const std::string &departureTime, const std::string &arrivalTime, const std::string &departureCity, const std::string &arrivalCity, int economyCapacity, int businessCapacity)
{
    /* TODO */
    Flight newFlight(flightCode, departureTime, arrivalTime, departureCity, arrivalCity, economyCapacity, businessCapacity);
    if (this->flights.search(newFlight) != NULL)
    {
        return;
    }
    this->flights.insert(newFlight);
}

std::vector<Flight *> AirlineReservationSystem::searchFlight(const std::string &departureCity, const std::string &arrivalCity)
{
    /* TODO */
    std::vector<Flight *> res;
    BSTNode<Flight> *r = this->flights.getRoot();
    searchFlightHelper(r, departureCity, arrivalCity, res);
    return res;
}

void AirlineReservationSystem::issueTicket(const std::string &firstname, const std::string &lastname, const std::string &flightCode, TicketType ticketType)
{
    /* TODO */
    Passenger *thePassenger = searchPassenger(firstname, lastname);
    BSTNode<Flight> *r = this->flights.getRoot();
    Flight *theFlight = searchFlightCode(r, flightCode);
    if (thePassenger != NULL && theFlight != NULL)
    {
        Ticket newTicket(thePassenger, theFlight, ticketType);
        theFlight->addTicket(newTicket);
    }
}

void AirlineReservationSystem::saveFreeTicketRequest(const std::string &firstname, const std::string &lastname, const std::string &flightCode, TicketType ticketType)
{
    /* TODO */
    Passenger *thePassenger = searchPassenger(firstname, lastname);
    BSTNode<Flight> *r = this->flights.getRoot();
    Flight *theFlight = searchFlightCode(r, flightCode);
    if (thePassenger != NULL && theFlight != NULL)
    {
        Ticket newTicket(thePassenger, theFlight, ticketType);
        this->freeTicketRequests.enqueue(newTicket);
    }
}

void AirlineReservationSystem::executeTheFlight(const std::string &flightCode)
{
    /* TODO */
    BSTNode<Flight> *r = this->flights.getRoot();
    Flight *theFlight = searchFlightCode(r, flightCode);
    if (theFlight != NULL)
    {
        int queueSize = this->freeTicketRequests.size();
        for (int i = 0; i < queueSize; i++)
        {
            Ticket myTicket = this->freeTicketRequests.dequeue();
            if (myTicket.getFlight()->getFlightCode() != flightCode || theFlight->addTicket(myTicket) == false)
            {
                this->freeTicketRequests.enqueue(myTicket);
            }
        }
        theFlight->setCompleted(true);
    }
}

void AirlineReservationSystem::print() const
{
    std::cout << "# Printing the airline reservation system ..." << std::endl;

    std::cout << "# Passengers:" << std::endl;
    passengers.print(inorder);

    std::cout << "# Flights:" << std::endl;
    flights.print(inorder);

    std::cout << "# Free ticket requests:" << std::endl;
    freeTicketRequests.print();

    std::cout << "# Printing is done." << std::endl;
}
