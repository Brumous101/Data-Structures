//Name: Kyle Johnson
//Class: ETEC2101
//Section: 01
//Assignment: 5
#include <iostream>
#include <string>			// contains getline function (among other things)
#include <linked_list.h>
#include <sorted_array_list.h>
#include <queue.h>
#include <stack.h>
#include <utility.h>
#include <bouncer.h>



int main()
{
	// SORTED_ARRAY_LIST
	// ... basic methods
	ssuds::SortedArrayList<std::string> slist1(ssuds::SortedArrayListType::DECREASING);
	slist1.add("Doug");//proper order additions
	slist1.add("Abe");
	slist1.add("Frank");
	slist1.add("Barb");
	slist1.add("Henry");
	slist1.push_back("Gina");													// If using public inheritance for SortedArrayList, "re-route" this to add
	slist1.insert("Carl", 0);													// ...and this.  If not using inheritance, don't even include these methods

	std::cout << "slist1 = " << slist1 << std::endl;							// slist1 = [Henry, Gina, Frank, Doug, Carl, Barb, Abe]
	std::cout << "(inherited) iterator test" << std::endl;						// (inherited) iterator test
	std::cout << "=========================" << std::endl;						// =========================
	for (std::string s : slist1)												//     Henry
		std::cout << s << std::endl;											//     Gina
																				//     Frank
																				//     Doug
																				//     Carl
																				//     Barb
																				//     Abe
	
	// Create a non-sorted ArrayList.  Then use the copy constructor to sort it in a copy
	ssuds::ArrayList<double> unsorted_list;
	unsorted_list.push_back(2.1);
	unsorted_list.push_back(1.3);
	unsorted_list.push_back(5.6);
	unsorted_list.push_back(9.9);
	unsorted_list.push_back(0.1);
	unsorted_list.push_back(3.5);
	unsorted_list.push_back(1.4);
	std::cout << "unsorted list = " << unsorted_list << std::endl;				// unsorted_list = [2.1, 1.3, 5.6, 9.9, 0.1, 3.5, 1.4]
	ssuds::SortedArrayList<double> sorted_list(unsorted_list, ssuds::SortedArrayListType::INCREASING); // two argument constructor
	unsorted_list.clear();
	std::cout << "unsorted list = " << unsorted_list << std::endl;				// unsorted_list = []
	std::cout << "sorted list = " << sorted_list << std::endl;					// sorted_list = [0.1, 1.3, 1.4, 2.1, 3.5, 5.6, 9.9]


	
	// Create a sorted list of bouncer.  I want them sorted by increasing velocity magnitude (hint: the magnitude of a velocity vector
	// is sqrt(velocity.x ^ 2 + velocity.y ^ 2)) -- the pythagorean theorem!  In my bouncer, the
	// first two floats are the position (of the center of the circle), the next is the radius, and the last two are
	// the velocity (horizontal and vertical speed) -- these last two are what determines which order it should
	// go in the SortedArrayList
	ssuds::SortedArrayList<ssuds::Bouncer> slist2(ssuds::SortedArrayListType::INCREASING);
	slist2.add(ssuds::Bouncer(200.0f, 300.0f, 5.0f, -20.0f, 5.0f));
	slist2.add(ssuds::Bouncer(400.0f, 100.0f, 5.0f, 20.0f, 8.0f));
	slist2.add(ssuds::Bouncer(500.0f, 500.0f, 5.0f, 100.0f, -32.0f));
	slist2.add(ssuds::Bouncer(600.0f, 50.0f, 5.0f, 40.0f, 100.0f));
	slist2.add(ssuds::Bouncer(300.0f, 400.0f, 5.0f, -10.0f, 5.0f));
	slist2.add(ssuds::Bouncer(50.0f, 200.0f, 5.0f, -20.0f, 15.0f));
	while (slist2.size() > 0)
	{
		ssuds::Bouncer b = slist2.remove(0);									// <Bouncer: pos=[300, 400], vel=[-10, 5], speed=11.1803>
		std::cout << b << std::endl;											// <Bouncer: pos=[200, 300], vel=[-20, 5], speed=20.6155>
	}																			// <Bouncer: pos=[400, 100], vel=[20, 8], speed=21.5407>
																				// <Bouncer: pos=[50, 200], vel=[-20, 15], speed=25>
																				// <Bouncer: pos=[500, 500], vel=[100, -32], speed=104.995>
																				// <Bouncer: pos=[600, 60], vel=[40, 100], speed=107.703>
	
	// QUEUE
	ssuds::Queue<int> Q;
	Q.push(52);
	Q.push(11);
	Q.push(99);
	std::cout << "Q's next item to be popped: " << Q.peek() << std::endl;		// Q's next item to be popped: 52
	while (!Q.empty())															//     popping 52
		std::cout << "\tpopping " << Q.pop() << std::endl;						//     popping 11
																				//     popping 99
	
	// STACK
	ssuds::Stack<double> S;
	S.push(52.7);
	S.push(11.3);
	S.push(99.9);
	std::cout << "S's next item to be popped: " << S.peek() << std::endl;		// S's next item to be popped: 99.9
	while (!S.empty())															//     popping 99.9
		std::cout << "\tpopping " << S.pop() << std::endl;						//     popping 11/3
																				//     popping 52.7																		
}