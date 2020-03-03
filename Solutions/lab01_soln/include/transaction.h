#pragma once
#include <ostream>

namespace ssuds
{
	class Transaction
	{
	protected:
		int mAccountID;
		short mDate[3];		// day, month, year
		float mAmount;
	public:
		Transaction(int acct, short d, short m, short y, float amt);
		Transaction();
		int getAccount() const;
		short getDay() const;
		short getMonth() const;
		short getYear() const;
		float getAmount() const;
		void setAccount(int acct);
		void setDate(short d, short m, short y);
		void setAmount(float amt);
	};

	std::ostream& operator<< (std::ostream& os, const Transaction& t);
}

