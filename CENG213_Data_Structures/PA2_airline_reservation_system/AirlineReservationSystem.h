#ifndef AIRLINERESERVATIONSYSTEM_H
#define AIRLINERESERVATIONSYSTEM_H

#include "BST.h"
#include "Queue.h"
#include "Passenger.h"
#include "Flight.h"
#include "Ticket.h"

class AirlineReservationSystem
{
public: // DO NOT CHANGE THIS PART.
    AirlineReservationSystem() {}

    void addPassenger(const std::string &firstname, const std::string &lastname);

    Passenger *searchPassenger(const std::string &firstname, const std::string &lastname);

    void addFlight(const std::string &flightCode, const std::string &departureTime, const std::string &arrivalTime, const std::string &departureCity, const std::string &arrivalCity, int economyCapacity, int businessCapacity);

    std::vector<Flight *> searchFlight(const std::string &departureCity, const std::string &arrivalCity);

    void issueTicket(const std::string &firstname, const std::string &lastname, const std::string &flightCode, TicketType ticketType);

    void saveFreeTicketRequest(const std::string &firstname, const std::string &lastname, const std::string &flightCode, TicketType ticketType);

    void executeTheFlight(const std::string &flightCode);

    void print() const;

private: // YOU MAY ADD YOUR OWN UTILITY MEMBER FUNCTIONS HERE.
    // checks if passenger exists
    bool checkPassengers(BSTNode<Passenger> *r, const std::string &firstname, const std::string &lastname)
    {
        if (r != NULL)
        {
            if (r->data.getFirstname() == firstname && r->data.getLastname() == lastname)
            {
                return false;
            }
            return checkPassengers(r->left, firstname, lastname) && checkPassengers(r->right, firstname, lastname);
        }
        else
        {
            return true;
        }
    }
    Flight *searchFlightCode(BSTNode<Flight> *r, const std::string &flightCode)
    {
        if (r != NULL)
        {
            if (r->data.getFlightCode() == flightCode)
            {
                return &(r->data);
            }
            else if (r->data.getFlightCode() > flightCode)
            {
                return searchFlightCode(r->left, flightCode);
            }
            else
            {
                return searchFlightCode(r->right, flightCode);
            }
        }
        return NULL;
    }
    void searchFlightHelper(BSTNode<Flight> *r, const std::string &departureCity, const std::string &arrivalCity, std::vector<Flight *> &res)
    {
        if (r != NULL)
        {
            if (r->data.getDepartureCity() == departureCity && r->data.getArrivalCity() == arrivalCity)
            {
                res.push_back(&(r->data));
            }
            searchFlightHelper(r->left, departureCity, arrivalCity, res);
            searchFlightHelper(r->right, departureCity, arrivalCity, res);
        }
    }

private: // DO NOT CHANGE THIS PART.
    BST<Passenger> passengers;
    BST<Flight> flights;

    Queue<Ticket> freeTicketRequests;
};

#endif // AIRLINERESERVATIONSYSTEM_H
