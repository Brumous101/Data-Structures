#include <iostream>
#include <string>			// contains getline function (among other things)
#include <array_list.h>



int main()
{
	// Testing creation and basic methods
	ssuds::ArrayList<std::string> slist;
	std::cout << slist.size() << std::endl;							// 0
	std::cout << slist.capacity() << std::endl;						// 5 
	slist.push_back("Abe");
	slist.push_back("Barb");
	slist.push_back("Carl");
	slist.push_back("Doug");
	slist.push_back("Erin");
	slist.push_back("Frank");										// If in a debug build, we should see "[[GROW]]" here
	std::cout << slist << std::endl;								// [Abe, Barb, Carl, Doug, Erin, Frank]    I'll be grading spaces and commas too!
	std::cout << slist.size() << std::endl;							// 6
	std::cout << slist.capacity() << std::endl;						// 10 
	

	// Testing index accessor
	std::cout << "slist" << std::endl << "=====" << std::endl;		// slist
	for (int i = 0; i < (int)slist.size(); i++)						// =====
		std::cout << "\t" << slist[i] << std::endl;					//     Abe
																	//     Barb
																	//     Carl
																	//     Doug
																	//     Erin
																	//     Frank
	// ... if uncommented, these lines should throw std::out_of_range exceptions.  Once that's working, uncomment them
	//slist[-5];
	//slist[200];


	// Testing insert
	slist.insert("Xavier", 2);
	std::cout << slist << std::endl;								// [Abe, Barb, Xavier, Carl, Doug, Erin, Frank]
	

	// Testing find mechanisms
	slist.push_back("Barb");										
	slist.push_back("Gina");
	slist.push_back("Barb");
	std::cout << slist << std::endl;								// [Abe, Barb, Xavier, Carl, Doug, Erin, Frank, Barb, Gina, Barb]
	std::cout << "Carl is at " << slist.find("Carl") << std::endl;	// Carl is at 3
	std::cout << "Barbs are at..." << std::endl;					// Barbs are at...
	int find_index = 0;												//     index=1
	while (1)														//     index=7
	{																//     index=9
		find_index = slist.find("Barb", find_index);
		if (find_index >= 0)
			std::cout << "\tindex=" << find_index << std::endl;
		else
			break;
		// Add one, so we start looking for more Barb's at the index after the one we just found
		find_index++;
	}

	// Testing remove
	slist.remove(7);
	slist.remove(8);
	std::cout << slist << std::endl;								// [Abe, Barb, Xavier, Carl, Doug, Erin, Frank]
	// ... if uncommented, these lines should throw std::out_of_range exceptions.  Once that's working, uncomment them
	//slist.remove(200);

	// Testing copy mechanisms
	ssuds::ArrayList<std::string> slist_copy1;
	slist_copy1.push_back("I'm going to get deleted on the next line");
	slist_copy1 = slist;
	ssuds::ArrayList<std::string> slist_copy2(slist);
	slist.clear();
	std::cout << slist.size() << std::endl;							// 0
	std::cout << slist.capacity() << std::endl;						// 5 
	std::cout << slist_copy1 << std::endl;							// [Abe, Barb, Xavier, Carl, Doug, Erin, Frank]
	slist_copy1.clear();
	std::cout << slist_copy2 << std::endl;							// [Abe, Barb, Xavier, Carl, Doug, Erin, Frank]

	
	// Just testing another type of ArrayList
	ssuds::ArrayList<float> flist;
	flist.push_back(1.1f);
	flist.push_back(2.2f);
	// Note: this int and double constant are silenty cast to floats.
	// You should get a warning on the second one (then you can change it to a float)
	flist.push_back(3);		
	flist.push_back(4.4f);
	// Despite the 3 show by cout, a 3.0f is being store in the ArrayList
	std::cout << "flist = " << flist << std::endl;					// [1.1, 2.2, 3, 4.4]
}

