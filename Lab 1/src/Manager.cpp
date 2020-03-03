#include <manager.h>
#include <Transactions.h>
#include <Account.h>
#include <fstream>
#include <string>
#include <iostream>

void ssuds::Manager::loadFiles(std::string accounts, std::string transactions)
{
	
	std::ifstream incomingAccountStream(accounts);//Going through the accounts.txt
	if(incomingAccountStream.is_open())
	{
		while(1)
		{
			//Accounts
			int accountNumber;
			std::string accountFirstName;
			std::string accountLastName;
			std::string line;
			incomingAccountStream >> accountNumber;

			//hits a space and forced to stop

			incomingAccountStream >> accountFirstName;

			//hits a space and forced to stop

			incomingAccountStream >> accountLastName;

			//New Line
			std::getline(incomingAccountStream, line);
			if (incomingAccountStream.eof())
			{
				break;
			}
			addAccount(accountFirstName, accountLastName);// Make this!
		}
		incomingAccountStream.close();
		incomingAccountStream.clear();
	}
	else
		std::cout << "Error opening Accounts.txt" << std::endl;

	std::ifstream incomingStream(transactions);//Going through the transactions.txt
	if(incomingStream.is_open())
	{
		while (1)
		{
			//Transactions 
			short month;
			short day;
			short year;
			std::string line;
			float tempAmount;
			int acct_num;
			incomingStream >> tempAmount;
			//hits a space and forced to stop
			incomingStream >> month;
			incomingStream.ignore(1);
			incomingStream >> day;
			incomingStream.ignore(1);
			incomingStream >> year;
			//hits a space and forced to stop
			incomingStream >> acct_num;
			//New Line
			std::getline(incomingStream, line);
			if (incomingStream.eof())
			{
				break;
			}
			addTransaction(acct_num, tempAmount, day, month, year);
			//incomingStream >> Acc number idk what
			//CALL THE TRANSACTION CONSTRUCTOR FROM HERE NOTICE ALL 5 GET PASSED TO IT
			//THIS JUST READS 
			//MANAGER HAS AN ADDTRANSACTION FUNCTION THAT DOES THE DYNAMIC ALLOCATION
		}
		incomingStream.close();
		incomingStream.clear();
	}
	else
		std::cout << "Error opening Transactions.txt" << std::endl;
}

ssuds::Manager::Manager(std::string accounts, std::string transactions)
{
	loadFiles(accounts, transactions);
}

ssuds::Manager::~Manager()
{
	/*
	int i;
	for (i = 0; i < mNumAccounts; i++)
	{
		clearAll();
		delete
		//removeAccount(getNumAccounts[i]);
	}
	*/
	//Destructor, will call clearAll and delete (same thing as free in C) all accounts
	//Also, calls removeAccount which will make the array one shorter and dynamically reallocate.
}

void ssuds::Manager::printAll(std::ostream& os, bool showTransactions)
{
	int i;
	for(i = 0; i < mNumAccounts; i++)
	{
		os << mAccounts[i] << std::endl;
	}
}

int ssuds::Manager::addAccount(std::string firstName, std::string lastName)
{
	//This is allocating memory through when there is zero things in the array AS WELL AS any time we want to add a new account we make more memory.
	Account* temp = new Account[mNumAccounts + 1]; 
	for(int i = 0; i < mNumAccounts; i++)
	{
		temp[i] = mAccounts[i];//the copy 
		//step 2 Add the new accounts 
		if (mAccounts[i].getID() < 1000)
		{
			temp[mNumAccounts] = Account(firstName, lastName);
		}//Does not need {} as what follows is one command/instruction
		else
			temp[mNumAccounts] = Account(firstName, lastName, mAccounts[i].getID()); //second constructor 
		//step 3 
		if(mAccounts != nullptr)
		{
			delete[] mAccounts;
		}//Does not need {} as what follows is one command/instruction
		mAccounts = temp;
		mNumAccounts++;
	}
	return temp[mNumAccounts-1].getID();// -1 because array
}

int ssuds::Manager::addTransaction(int acct_num, float amt, short day, short month, short year)
{
	Transaction* temp = new Transaction[mNumAccounts + 1];
	for (int i = 0; i < mNumAccounts; i++)
	{
		temp[i] = mTransactions[i];//the copy 
		//step 2 Add the new accounts 
		if(mAccounts[i].getID() < 1000)
		{
			temp[mNumAccounts] = Transaction(acct_num, amt, day, month, year);
		}//Does not need {} as what follows is one command/instruction
		else
			temp[mNumAccounts] = Transaction(mTransactions[i].getAccount(), mTransactions[i].getAmount(), mTransactions[i].getDay(), mTransactions[i].getMonth(), mTransactions[i].getYear()); //second constructor 
		//step 3 
		if (mTransactions != nullptr)
		{
			delete[] mTransactions;
		}//Does not need {} as what follows is one command/instruction
		mTransactions = temp;
		mNumAccounts++;
	}
	return 0;
}
/*
int getNumAccounts()
{
	//not sure what to do with this
	//return mNumAccounts;
}
*/
void clearAll()
{
	//clear the Account and Transaction arrays. Call this from the destructor (and possibly when resizing the arrays)
}

//has to have a destructor because most of our works takes place here. its where we do the memory allocation and deallocation
void ssuds::Manager::removeAccount(int acct_num)
{
	//Call on Accounts destructor
	//From the acct_num that gets passed we will dynamically allocate the array to be one shorter than
}