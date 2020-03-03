#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main()
{
    cout << "Hello World!\n";
    vector<string> slist;
    slist.push_back("Abe");
    slist.push_back("Bob");
    slist.push_back("Carl");
    slist.push_back("Doug");
    for (int i = 0; i < slist.size(); i++)
        cout << "slist[" << i << "] = " << slist[i] << endl;

    // Print all elements using an iterator
    vector<string>::iterator cur = slist.begin();   // iterator object
    //auto cur = slist.begin(); // the lazy way to determine the type of a variable
    while (cur != slist.end())
    {
        // Get / process the current element.  
        std::string temp = *cur;
        // If we change temp to this, we are getting
        // a REFERENCE to a string.  That means if we
        // change temp, we change the original where
        // it refers to.
        //std::string& temp = *cur;       // Call the * operator
        //if (temp == "Bob")
        //    temp = "Not Bob";
        cout << temp << endl;

        // Advance the iterator
        ++cur;
    }

    // Prettier interface to iterators -- needs all of the
    // functionality from above to work.  A "for-each" loop
    for (string s : slist)
        cout << s << endl;
}

