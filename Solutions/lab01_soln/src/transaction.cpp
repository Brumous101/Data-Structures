#include <transaction.h>


std::ostream& ssuds::operator<< (std::ostream& os, const Transaction& t)
{
	os << t.getAmount() << " " << t.getMonth() << "/" << t.getDay() << "/" << t.getYear() << " " << t.getAccount();
	return os;
}




ssuds::Transaction::Transaction(int acct, short d, short m, short y, float amt) : mAccountID(acct), mAmount(amt)
{
	mDate[0] = d;
	mDate[1] = m;
	mDate[2] = y;
}


ssuds::Transaction::Transaction() : mAccountID(-1), mAmount(0.0f)
{
	mDate[0] = mDate[1] = mDate[2] = -1;
}


int ssuds::Transaction::getAccount() const
{
	return mAccountID;
}


short ssuds::Transaction::getDay() const
{
	return mDate[0];
}


short ssuds::Transaction::getMonth() const
{
	return mDate[1];
}


short ssuds::Transaction::getYear() const
{
	return mDate[2];
}


float ssuds::Transaction::getAmount() const
{
	return mAmount;
}


void ssuds::Transaction::setAccount(int acct)
{
	mAccountID = acct;
}


void ssuds::Transaction::setDate(short d, short m, short y)
{
	mDate[0] = d;
	mDate[1] = m;
	mDate[2] = y;
}


void ssuds::Transaction::setAmount(float amt)
{
	mAmount = amt;
}
