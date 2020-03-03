#include <account.h>

// Initializes the static attribute of the Account class --it must be done here (not in the class 
// declaration or a constructor)
int ssuds::Account::mNextID = 1000;

// Allow one of our Account Objects to be sent to a stream
std::ostream& ssuds::operator<<(std::ostream& os, const Account& a)
{
	os << a.getID() << " " << a.getFirstName() << " " << a.getLastName();
	return os;
}

ssuds::Account::Account(std::string fname, std::string lname) : mFirstName(fname), mLastName(lname)
{
	mID = mNextID++;
}


ssuds::Account::Account(std::string fname, std::string lname, int id) : mFirstName(fname), mLastName(lname)
{
	mID = id;
	if (mID >= mNextID)
		mNextID = mID + 1;
}


ssuds::Account::Account()
{
	mID = mNextID++;
}



ssuds::Account::~Account()
{
	// Nothing here since we didn't dynamically allocate memory and don't need to shut anything down.
}


std::string ssuds::Account::getFirstName() const
{
	return mFirstName;
}


std::string ssuds::Account::getLastName() const
{
	return mLastName;
}


void ssuds::Account::setFirstName(std::string fname)
{
	mFirstName = fname;
}


void ssuds::Account::setLastName(std::string lname)
{
	mLastName = lname;
}


int ssuds::Account::getID() const
{
	return mID;
}