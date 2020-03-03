#pragma once
#include <string>
#include <account.h>
#include <transactions.h>

namespace ssuds
{
	class Manager
	{
	protected:
		std::string mAccountFName;
		std::string mTransactionFName;
		Account* mAccounts;
		Transaction* mTransactions;
		int mNumAccounts; //size of the accounts array
		int mNumTransactions; //size of the transactions array
	public:
		Manager(std::string accounts, std::string transactions);
		~Manager();//Destructor must be made in header since we will be doing dynamic allocation in the manager function
		void loadFiles(std::string accounts, std::string transactions);
		void printAll(std::ostream& os, bool showTransactions);//false just shows balance
		void removeAccount(int acct_num); // should this be a return type int? look at main program 
		int addAccount(std::string mFirstName, std::string mLastName);//must resize the array
		int addTransaction(int acct_num, float amt, short day, short month, short year);
		int getNumAccounts();
		void clearAll();
	};
}