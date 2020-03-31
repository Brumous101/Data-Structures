#include "utility.h"

bool ssuds::is_number(std::string s, bool include_float)
{
	for (unsigned int i = 0; i < s.size(); i++)
	{
		// Integers and floats can contain digits or + or -.  Floats can additionally include
		// 'e' and '.' characters
		if (!isdigit(s[i]) && s[i] != '+' && s[i] != '-' && (!include_float || (s[i] != '.' && s[i] != 'e')))
			return false;
	}

	// If we get here, we didn't see any non-integers in the string.  
	// Only one check left: did we actually have any characters?
	return s.size() > 0;
}



int ssuds::get_integer(std::string prompt, int fallback_val)
{
	// Get whatever response the user (including garbage responses like "abc").
	// Then see if it's a valid response, using our custom function.  If it is a valid
	// response, use the C function atoi to actually convert to an integer.  Note: atoi
	// takes a char-pointer (C-style-string).  std::strings have this internally -- just
	// ask for it with the c_str() method.
	std::string s;

	std::cout << prompt;
	std::getline(std::cin, s);
	if (is_number(s))
		return atoi(s.c_str());
	else
		return fallback_val;
}



bool ssuds::get_float(std::string prompt, float& value)
{
	std::string s;

	std::cout << prompt;
	std::getline(std::cin, s);
	if (is_number(s, true))
	{
		value = (float)atof(s.c_str());
		return true;
	}
	else
		return false;
}



int ssuds::count(char c, std::string s)
{
	int num = 0;
	for (unsigned int i = 0; i < s.size(); i++)
	{
		if (s[i] == c)
			num++;
	}

	return num;
}


float ssuds::rand_float(float min, float max, int resolution)
{
	if (min <= max)
	{
		int num = rand() % (resolution - 1);	// 0...resolution-1
		float num_f = num / (float)resolution;	// 0.0...1.0
		return num_f * (max - min) + min;
	}
	else
		return 0.0f;
}