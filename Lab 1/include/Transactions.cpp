#include <Transactions.h>

ssuds::Transaction::Transaction(int acct, short day, short month, short year, float amt)
{
	mAmount = NULL;
	mAccountID = NULL;
	mDate[0] = month;
	mDate[1] = day;
	mDate[2] = year;
	mAmount = amt;
}

ssuds::Transaction::Transaction()
{
	mAmount = NULL;
	mAccountID = NULL;
	mDate[3]; //Day, Month, Year Also, initialized as garbage
}

int ssuds::Transaction::getAccount()
{
	return mAccountID;
}

short ssuds::Transaction::getMonth()
{
	return mDate[0];
}
short ssuds::Transaction::getDay()
{
	return mDate[1];
}
short ssuds::Transaction::getYear()
{
	return mDate[2];
}

float ssuds::Transaction::getAmount()
{
	return mAmount;
}

void ssuds::Transaction::setAccount(int acct)
{
	mAccountID = acct;
}

void ssuds::Transaction::setDate(short day, short month, short year)
{
	mDate[0] = month;
	mDate[1] = day;
	mDate[2] = year;
}

void ssuds::Transaction::setAmount(float amt)
{
	mAmount = amt;
}

std::ostream& ssuds::operator<<(std::ostream& os, Transaction& t)
{
	os << t.getAmount() << " " << t.getMonth() << "/" << t.getDay() << "/" << t.getYear() << " " << t.getAccount();
	return os;
}
