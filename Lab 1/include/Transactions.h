#pragma once
#include <ostream>

namespace ssuds
{
	class Transaction
	{
		protected:
			float mAmount;
			int mAccountID;
			short mDate[3]; //Day, Month, Year
		public:
			Transaction(int acct, short day, short month, short year, float amt);
			Transaction();
			int getAccount();
			short getDay();
			short getMonth();
			short getYear();
			float getAmount();
			void setAccount(int acct);
			void setDate(short day, short month, short year);
			void setAmount(float amt);
	};

	std::ostream& operator<< (std::ostream& os, Transaction& t);
}