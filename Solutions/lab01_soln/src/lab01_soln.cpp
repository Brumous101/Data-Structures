#include <iostream>
#include <string>			// contains getline function (among other things)
// Include our files.  
// Note: the #include <foo.h> is more restrictive than #include "foo.h", but more predictable.  The
// former only looks in the project's additional include directories (set in project properties).  The
// latter looks in these and more.  If you want, you can do the "" form for this lab.
#include <manager.h>
#include <utility.h>



int main()
{
	// Note: I did the project re-organization, so the .sln and .vcprojx files are in a build subdirectory.
	// The path given here goes out of that and into the bin folder (where there are Debug and Release folders
	// that hold the exe -- this is the working directory set by Project Properties => Debugging => Working Directory).
	// So...the .. on the path says go out of Debug / Release and into the bin folder.  If you haven't done the project
	// re-organization and haven't changed the Working Directory, you could take the ..'s off and put the text files
	// next to your project file.
	ssuds::BankAccountManager M("../accounts.txt", "../transactions.txt");
	bool done = false;
	int menu_choice;
	bool show_menu = true;

	while (!done)
	{
		// (Re-) show the menu
		if (show_menu)
		{
			// Show the menu (at least once)
			std::cout << "Main Menu" << std::endl << "=========" << std::endl;
			std::cout << "1. Show all accounts (with balance summary)" << std::endl;
			std::cout << "2. Show all accounts (with detailed transaction record)" << std::endl;
			std::cout << "3. Remove account" << std::endl;
			std::cout << "4. Add account" << std::endl;
			std::cout << "5. Add transaction" << std::endl;
			std::cout << "9. quit" << std::endl;
			show_menu = false;
		}

		// Use our function to get the number typed in (or -1 if an invalid string is entered)
		menu_choice = ssuds::get_integer(">>> ");
	

		// Actually process the menu request
		switch (menu_choice)
		{
		case 1:
			M.printAll(std::cout, true);
			break;
		case 2:
			M.printAll(std::cout, false);
			break;
		case 3:
		{
			// Note: the curly braces here aren't necessary, but they allow us to make the temporary
			// variables we create here to have a smaller SCOPE (ask about this term if you're not
			// familiar!)
			int acct_num = ssuds::get_integer("Enter account number to remove (including all transactions): ");
			if (acct_num >= 0)
				M.removeAccount(acct_num);
			else
				std::cout << "Invalid account number -- going back to main menu." << std::endl;
			break;
		}
		case 4:
		{
			std::string fname, lname;
			std::cout << "Enter first name: ";
			std::getline(std::cin, fname);
			std::cout << "Enter last name: ";
			std::getline(std::cin, lname);
			int acct_num = M.addAccount(fname, lname);
			if (acct_num < 0)
				std::cout << "That name already has an account.  Going back to main menu." << std::endl;
			else
				std::cout << "New Account Number: " << acct_num << std::endl;
			break;
		}
		case 5:
		{
			// I'm setting all of these to negatives initially.  If they *remain*
			// negative, that indicates the user didn't enter a valid response.  The 
			// amount has to be handled a little differently (since a negative float indicates
			// a withdrawal).
			int acct_num = ssuds::get_integer("Enter account number: ");
			short day = (short)ssuds::get_integer("Enter day of transaction (1-31): ");
			short month = (short)ssuds::get_integer("Enter month of transaction (1-12): ");
			short year = (short)ssuds::get_integer("Enter year of transaction: ");

			// Check for invalid entries.  If so, reset the value
			if (day < 1 || day > 31)		day = -1;				// Lazy: not checking for the right day range per month
			if (month < 1 || month > 12)	month = -1;
			if (year < 1900 || year > 3000)	year = -1;				// Assuming our program won't last until after 3000AD :P
			float amt;
			bool amt_valid = ssuds::get_float("Enter amount (positive = deposit, negative = withdrawal), no '$': ", amt);
			if (acct_num >= 0 && day >= 0 && month >= 0 && year >= 0 && amt_valid)
				M.addTransaction(acct_num, amt, day, month, year);
			else
				std::cout << "Invalid entry.  Going back to main menu." << std::endl;

			break;
		}
		case 9:
			done = true;
			std::cout << "goodbye!" << std::endl;
			break;
		default:
			std::cout << std::endl << "INVALID menu choice" << std::endl;
			show_menu = true;
			break;
		}
	}
}

