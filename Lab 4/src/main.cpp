//Name: Kyle Johnson
//Class: ETEC2101
//Section: 01
//Assignment: 4
#include <iostream>
#include <string>			// contains getline function (among other things)
#include <linked_list.h>
//#include <utility.h>

int main()
{
	// Testing creation and basic methods
	ssuds::LinkedList<std::string> llist;
	std::cout << llist.size() << std::endl;							// 0

	llist.push_back("Barb");
	llist.push_back("Carl");
	llist.push_front("Abe");
	llist.push_back("Doug");
	llist.push_back("Frank");
	llist.insert("Erin", 4);
	llist.insert("Aardvark", 0);	// Same as push_front
	llist.insert("Gary", 7);		// Same as push_back
	std::cout << llist << std::endl;								// [Aardvark, Abe, Barb, Carl, Doug, Erin, Frank, Gary]    I'll be grading spaces and commas too!
	std::cout << llist.size() << std::endl;							// 6



	// Testing index accessor.  Note: This is a lot more expensive with linked lists!!
	std::cout << "llist" << std::endl << "=====" << std::endl;		// slist
	for (int i = 0; i < (int)llist.size(); i++)						// =====
		std::cout << "\t" << llist[i] << std::endl;					//     Aardvark
																	//     Abe
																	//     Barb
																	//     Carl
																	//     Doug
																	//     Erin
																	//     Frank
																	//     Gary
	// ... if uncommented, these lines should throw std::out_of_range exceptions.  Once that's working, uncomment them
	//llist[-5];
	//llist[200];


	// Testing find mechanisms
	llist.push_back("Barb");
	llist.push_back("Henrietta");
	llist.push_back("Barb");
	std::cout << llist << std::endl;								// [Aardvark, Abe, Barb, Carl, Doug, Erin, Frank, Gary, Barb, Henrietta, Barb]
	std::cout << "Carl is at " << llist.find("Carl") << std::endl;	// Carl is at 3
	std::cout << "Barbs are at..." << std::endl;					// Barbs are at...
	int find_index = 0;												//     index=2
	while (1)														//     index=8
	{																//     index=10
		find_index = llist.find("Barb", find_index);
		if (find_index >= 0)
			std::cout << "\tindex=" << find_index << std::endl;
		else
			break;
		// Add one, so we start looking for more Barb's at the index after the one we just found
		find_index++;
	}

	// Testing remove
	std::cout << "test" << std::endl;								
	std::cout << "removed " << llist.remove(8) << std::endl;		// Removed Barb
	std::cout << "removed " << llist.remove(9) << std::endl;		// Removed Barb
	std::cout << "removed " << llist.remove(0) << std::endl;		// Removed Aardvark
	std::cout << "removed " << llist.remove(7) << std::endl;		// Removed Henrietta
	std::cout << "removed " << llist.remove(1) << std::endl;		// Removed Barb
	std::cout << llist << std::endl;								// [Abe, Carl, Doug, Erin, Frank, Gary]
	// ... if uncommented, these lines should throw std::out_of_range exceptions.  Once that's working, uncomment them
	//llist.remove(200);
	std::cout << "test" << std::endl;
	
	// Testing for-each (and "normal" / "forward" iterator stuff)
	std::cout << "forward-iterator test" << std::endl;				// forward-iterator test
	std::cout << "=====================" << std::endl;				// =====================
	for (std::string s : llist)										//     Abe
		std::cout << "\t" << s << std::endl;						//     Carl
																	//	   Doug
																	//	   Erin
																	//     Frank
																	//     Gary

	// Testing reverse iterator. Unfortunately, C++ doesn't have a reverse for-each loop
	// (that I know of), so we'll do it the manual way
	std::cout << "reverse-iterator test" << std::endl;				// reverse-iterator test
	std::cout << "=====================" << std::endl;				// =====================
	ssuds::LinkedList<std::string>::LinkedListIterator it = llist.rbegin();
	while (it != llist.end())										//     Gary
	{																//     Frank
		std::cout << "\t" << *it << std::endl;						//     Erin
		++it;														//     Doug
	}																//     Carl
																	//     Abe
	ssuds::LinkedList<int> test_list{ 4, 7 ,15, 13, 12, 52, 99 };
	std::cout << test_list << std::endl;
	
	ssuds::LinkedList<std::string> test_list2{ "s1", "s2", "s3", "s4" };
	std::cout << test_list2 << std::endl;
}