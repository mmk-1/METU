#include "Passenger.h"

Passenger::Passenger(std::string firstname, std::string lastname)
{
    this->firstname = firstname;
    this->lastname = lastname;
}

const std::string &Passenger::getFirstname() const
{
    return firstname;
}

const std::string &Passenger::getLastname() const
{
    return lastname;
}

bool Passenger::operator<(const Passenger &rhs) const
{
    /* TODO */
    std::string lhsLastname = lastname, rhsLastname = rhs.lastname;

    for (int i = 0; i < (int) lhsLastname.size(); i++)
    {
        lhsLastname[i] = tolower(lhsLastname[i]);
    }
    for (int i = 0; i < (int) rhsLastname.size(); i++)
    {
        rhsLastname[i] = tolower(rhsLastname[i]);
    }

    if (lhsLastname < rhsLastname)
    {
        return true;
    }
    else if (lhsLastname > rhsLastname)
    {
        return false;
    }
    else
    {

        std::string lhsFirstname = firstname, rhsFirstname = rhs.firstname;

        for (int i = 0; i < (int) lhsFirstname.size(); i++)
        {
            lhsFirstname[i] = tolower(lhsFirstname[i]);
        }
        for (int i = 0; i < (int) rhsFirstname.size(); i++)
        {
            rhsFirstname[i] = tolower(rhsFirstname[i]);
        }
        if (lhsFirstname < rhsFirstname)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    return false;
}

bool Passenger::operator>(const Passenger &rhs) const
{
    return rhs < *this;
}

bool Passenger::operator==(const Passenger &rhs) const
{
    return firstname == rhs.firstname && lastname == rhs.lastname;
}

bool Passenger::operator!=(const Passenger &rhs) const
{
    return !(rhs == *this);
}

std::ostream &operator<<(std::ostream &os, const Passenger &passenger)
{
    os << "Passenger(firstname: " << passenger.firstname;
    os << ", lastname: " << passenger.lastname << ")";
    return os;
}
