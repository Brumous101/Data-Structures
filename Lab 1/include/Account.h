#pragma once
#include <string>

namespace ssuds
{
	class Account
	{
	protected:
		std::string mFirstName;
		std::string mLastName;
		int mID;
		static int mNextID;
	public:
		Account(std::string firstName, std::string lastName);//First time through
		Account(std::string mFirstName, std::string mLastName, int mID);//Every other transaction
		Account();
		~Account();
		//Getters
		std::string getFirstName();
		std::string getLastName();
		int getID();
		//setters
		void setFirstName(std::string firstName);//Would this be mFirstName or would this be firstName
		void setLastName(std::string lastName);
		void setID(int iD);
	};

	std::ostream& operator<< (std::ostream& os, Account& a);
}