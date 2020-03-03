#include "manager.h"
#include <fstream>
#include <utility.h>
#include <sstream>

ssuds::BankAccountManager::BankAccountManager(std::string acct_fname, std::string trans_fname) : mAccountFName(acct_fname), mTransactionFName(trans_fname),
		mAccounts(NULL), mNumAccounts(0), mTransactions(NULL), mNumTransactions(0)
{
	loadFiles();
}


ssuds::BankAccountManager::~BankAccountManager()
{
	saveFiles();
	clearAll();
}


int ssuds::BankAccountManager::addAccount(std::string fname, std::string lname, int acct)
{
	// I'm being lazy here.  I allocate the array to be one bigger than it currently is,
	// copy over the old data (if any), and then make the new array the *real* array.
	// A more efficient approach (that we'll use in our data structures) is to 
	// make it significantly bigger than it currently is so we delay this COSTLY
	// operation and only do it occasionally
	Account* new_accounts = new Account[mNumAccounts + 1];
	for (int i = 0; i < mNumAccounts; i++)
		new_accounts[i] = mAccounts[i];
	if (acct > 0)
		new_accounts[mNumAccounts] = Account(fname, lname, acct);
	else
		new_accounts[mNumAccounts] = Account(fname, lname);
	

	// Now that we've copied out all the data from the old array -- very important!
	// If you leave this off, you have a serious memory leak!
	delete[] mAccounts;

	// This part updates our *real* variables
	mAccounts = new_accounts;
	mNumAccounts++;

	return mAccounts[mNumAccounts - 1].getID();
}


void ssuds::BankAccountManager::addTransaction(int acct, float amount, short d, short m, short y)
{
	// Similar approach to addAccount
	Transaction* new_transactions = new Transaction[mNumTransactions + 1];
	for (int i = 0; i < mNumTransactions; i++)
		new_transactions[i] = mTransactions[i];
	new_transactions[mNumTransactions].setAccount(acct);
	new_transactions[mNumTransactions].setDate(d, m, y);
	new_transactions[mNumTransactions].setAmount(amount);

	// Delete the old data
	delete[] mTransactions;

	// Replace the old values with the new
	mTransactions = new_transactions;
	mNumTransactions++;
}


void ssuds::BankAccountManager::removeAccount(int acct)
{
	// First, remove any transactions that go along with that account
	int num_trans_deleted = 0;
	for (int i = 0; i < mNumTransactions; i++)
	{
		if (mTransactions[i].getAccount() == acct)
		{
			// Here's the tricky part.  In an array, we have to move anything that comes
			// *after* this element down one index to take up the spot of this element we're
			// trying to delete
			for (int j = i + 1; j < mNumTransactions; j++)
				mTransactions[i - 1] = mTransactions[i];

			// We now have one fewer transaction than we did and one more deleted item
			mNumTransactions--;
			num_trans_deleted++;

			// Here's another tricky part -- we now have a new element at position i.  We have
			// to check it because it could very well have the target account# too.  By decrementing i, we
			// cancel out the increment operation that the for loop will do
			i--;
		}
	}

	// Resize the transaction array -- if we deleted anything, there's actually more memory
	// allocated to that array than needed
	if (num_trans_deleted > 0)
	{
		Transaction* new_transactions = new Transaction[mNumTransactions];
		for (int i = 0; i < mNumTransactions; i++)
			new_transactions[i] = mTransactions[i];
		delete[] mTransactions;
		mTransactions = new_transactions;
	}

	// Now go through and remove the (single) element from mAccounts that matches.  There's a chance that 
	// the account number they gave us isn't really in the array.
	bool found_account = false;
	for (int i = 0; i < mNumAccounts; i++)
	{
		if (mAccounts[i].getID() == acct)
		{
			// Same as with transactions -- move everything down an index
			for (int j = i + 1; j < mNumAccounts; j++)
				mAccounts[j - 1] = mAccounts[j];

			found_account = true;

			// We don't need to look anymore -- we found it.
			break;
		}
	}

	// If we found the account, resize the array
	if (found_account)
	{
		Account* new_accounts = new Account[mNumAccounts - 1];
		for (int i = 0; i < mNumAccounts - 1; i++)
			new_accounts[i] = mAccounts[i];

		mNumAccounts--;
		delete[] mAccounts;
		mAccounts = new_accounts;
	}
}


int ssuds::BankAccountManager::getNumAccounts()
{
	return mNumAccounts;
}




void ssuds::BankAccountManager::printAll(std::ostream& os, bool totals_only)
{
	for (int i = 0; i < mNumAccounts; i++)
	{
		float total = 0.0f;
		for (int j = 0; j < mNumTransactions; j++)
		{
			if (mTransactions[j].getAccount() == mAccounts[i].getID())
				total += mTransactions[j].getAmount();
		}

		os << mAccounts[i] << " $" << total << std::endl;
		if (!totals_only)
		{
			for (int j = 0; j < mNumTransactions; j++)
			{
				if (mTransactions[j].getAccount() == mAccounts[i].getID())
					os << "\t" << mTransactions[j] << std::endl;
			}
		}
	}
}


void ssuds::BankAccountManager::clearAll()
{
	if (mAccounts != NULL)
		delete[] mAccounts;
	mAccounts = NULL;
	mNumAccounts = 0;

	if (mTransactions != NULL)
		delete[] mTransactions;
	mTransactions = NULL;
	mNumTransactions = 0;
}




void ssuds::BankAccountManager::loadFiles()
{
	clearAll();

	std::ifstream fin(mAccountFName);
	std::string line;

	if (!fin.is_open())
	{
		std::cout << "Problem opening '" << mAccountFName << "' -- aborting load." << std::endl;
		return;
	}

	// Get the accounts
	do
	{
		std::getline(fin, line);
		if (ssuds::count(' ', line) == 2)
		{
			std::stringstream ss(line);
			std::string fname, lname;
			int acct;

			ss >> acct >> fname >> lname;
			addAccount(fname, lname, acct);
		}
	} while (!fin.eof());
	fin.close();
	fin.clear();

	// Get the transactions
	fin.open(mTransactionFName);
	if (!fin.is_open())
	{
		std::cout << "Problem opening '" << mTransactionFName << "' -- aborting load." << std::endl;
		return;
	}

	do
	{
		std::getline(fin, line);
		if (ssuds::count(' ', line) == 2 && ssuds::count('/', line) == 2)
		{
			std::stringstream ss(line);
			float amt;
			short day, month, year;
			int acct;
			ss >> amt >> month;
			ss.ignore(1);
			ss >> day;
			ss.ignore(1);
			ss >> year >> acct;

			addTransaction(acct, amt, day, month, year);
		}
	} while (!fin.eof());
	fin.close();
	fin.clear();
}


void ssuds::BankAccountManager::saveFiles()
{
	std::ofstream fout(mAccountFName);
	for (int i = 0; i < mNumAccounts; i++)
		fout << mAccounts[i] << std::endl;
	fout.close();
	fout.clear();

	fout.open(mTransactionFName);
	for (int i = 0; i < mNumTransactions; i++)
		fout << mTransactions[i] << std::endl;
	fout.close();
	fout.clear();

}