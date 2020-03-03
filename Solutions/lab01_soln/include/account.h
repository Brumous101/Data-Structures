#pragma once
#include <string>
#include <ostream>

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
		Account(std::string fname, std::string lname);
		Account(std::string fname, std::string lname, int id);
		Account();
		~Account();
		std::string getFirstName() const;
		std::string getLastName() const;
		void setFirstName(std::string fname);
		void setLastName(std::string lname);
		int getID() const;
	};

	std::ostream& operator<<(std::ostream& os, const Account& a);

}