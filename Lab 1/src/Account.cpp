#include <Account.h>
#include <iostream>

int ssuds::Account::mNextID = 1000;

ssuds::Account::~Account()
{
    //Destructor, will be empty
}

ssuds::Account::Account(std::string firstName, std::string lastName)
{
    //The two variables are different to the compiler
    mFirstName = firstName;
    mLastName = lastName;//this is initializing the attributes
}

ssuds::Account::Account(std::string firstName, std::string lastName, int iD)
{
    std::string mFirstName = firstName;
    std::string mLastName = lastName;
    int mID = iD;
    mNextID++;
}

ssuds::Account::Account()
{
    //empty
}

std::string ssuds::Account::getFirstName()
{
    return mFirstName;
}

std::string ssuds::Account::getLastName()
{
    return mLastName;
}

int ssuds::Account::getID()
{
    return mID;
}


void ssuds::Account::setFirstName(std::string firstName)
{
    mFirstName = firstName;
}

void ssuds::Account::setLastName(std::string lastName)
{
    mLastName = lastName;
}

void ssuds::Account::setID(int iD)
{
    mID = iD;
}

std::ostream& ssuds::operator<<(std::ostream& os, Account& a)
{
    os << a.getID() << " " << a.getFirstName() << " " << a.getLastName();
    return os;
}
