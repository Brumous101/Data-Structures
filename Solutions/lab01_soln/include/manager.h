#pragma once
#include <ostream>
#include <transaction.h>
#include <account.h>

namespace ssuds
{

	class BankAccountManager
	{
	protected:
		std::string mAccountFName;
		std::string mTransactionFName;
		Transaction* mTransactions;
		int mNumTransactions;
		Account* mAccounts;
		int mNumAccounts;

	public:
		BankAccountManager(std::string acct_fname, std::string trans_fname);
		~BankAccountManager();
		int addAccount(std::string fname, std::string lname, int acct = -1);
		void addTransaction(int acct, float amount, short d, short m, short y);
		void removeAccount(int acct);
		int getNumAccounts();
		//Account& getAccount(int index);
		//int getNumTransactions();
		//Transaction& getTransaction(int index);
		void printAll(std::ostream& os, bool totals_only);
		void clearAll();

	protected:
		//int findAccountIndex(int account_id);
		void loadFiles();
		void saveFiles();

	};

}



