#pragma once
#include <string>
#include <iostream>

namespace ssuds
{
	// A function to determine if a given string contains a string convertable to
	// an integer (or a float if the second parameter is true).
	bool is_number(std::string s, bool include_float = false);


	// Displays a prompt to cout and asks (using cin) for a numeric response.  If the
	// response entered isn't convertable to an integer, return the fallback_val.
	int get_integer(std::string prompt, int fallback_val = -1);


	// Displays a prompt to cout and asks (using cin) for a float response.  If the
	// response entered isn't convertable to a float, this function returns false
	// and doesn't modify value.  If it is convertable, return true and assign the 
	// typed value to the value parameter.
	bool get_float(std::string prompt, float& value);

	// Counts the number of occurrences of c in s.
	int count(char c, std::string s);
}