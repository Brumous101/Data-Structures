//Name: Kyle Johnson
//Class: ETEC2101
//Section: 01
//Assignment: 5
#pragma once
#include <cassert>
#include <iostream>
#include <exception>
#include <array_list.h>

// If you set this to 0, ArrayList messages should not show.  I put this here because after this lab,
// we don't really want those debug messages cluttering things up.
#define SHOW_DEBUG_MSGS 1

namespace ssuds
{
	enum class SortedArrayListType { INCREASING, DECREASING };//The enum we will be receiving will be given in the main

	/// An ArrayList is similar to (but more simple than) std::vector.  Behind the scenes
	/// is contains a dynamically created array of T objects.  This array is resized periodically
	/// when we run out of capacity (currently by a fixed amount, although that could be changed
	/// to doubling, tripling, if desired -- that would increase the amortized efficiency, but
	/// would (drastically) increase the memory footprint).
	template<class T>
	///This is a test for the next line of code
	class SortedArrayList : public /*or private*/ ArrayList<T>
	{
	protected:
		///This is the only variables that is exclusive to the child class. All variables we need for storing data are inherited from ArrayList
		SortedArrayListType mType;
		///Determines if two elements are out of order based on which direction we want the list to be sorted
		bool out_of_order(int i, int j)
		{
			//Determines which order we are going
			if (mType == SortedArrayListType::INCREASING && ArrayList<T>::mData[i] > ArrayList<T>::mData[j]) // The enum has to be called this way because even though it's the same file it's technically a different class
			{
				return true;
			}
			else if (mType == SortedArrayListType::DECREASING && ArrayList<T>::mData[i] < ArrayList<T>::mData[j])
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	public:
		///constructor for an already sorted list
		SortedArrayList(SortedArrayListType sortType)
		{
								//base class constructor is automatically called
			mType = sortType;	// this user submitted and determines how sort is done
		}
		///constructor that takes an unsorted list as an argument
		SortedArrayList(const ArrayList<T>& A, SortedArrayListType sortType) : ArrayList<T>(A)
		{
			mType = sortType;
			sort();
		}
		///Adds the element to the start of the array_list and then sorts after the addition
		void add(T val)
		{
			//needs to do an insertion based on the correct index 
			//Alphabetically or with numbers
			//sort -> insert method parent
			ArrayList<T>::push_back(val);
			sort();
		}
		///A useless function they are overriding the parent functions because otherwise it would use the parents functions which are incorrect
		void push_back(T val) 
		{
			add(val);
		}
		///A useless function they are overriding the parent functions because otherwise it would use the parents functions which are incorrect
		void insert(T val, int index)
		{
			add(val);
		}
		///Bubble sort implementation to sort the list
		void sort()
		{
			bool swapped;
			bool bOoo;
			T temp;
			for (int i = 0; i < ArrayList<T>::mSize - 1; i++)
			{
				swapped = false;
				for (int j = 0; j < (ArrayList<T>::mSize - 1 - i); j++)//since biggest always goes to end, don’t have to check it 
				{
					bOoo = out_of_order(j, j + 1); //Which way we are going

					//They are out of order
					if(bOoo)
					{
						temp = ArrayList<T>::mData[j + 1];
						ArrayList<T>::mData[j + 1] = ArrayList<T>::mData[j];
						ArrayList<T>::mData[j] = temp;
							swapped = true;
					}
				}
				//They are not out of order list is now sorted!
				if (swapped == false)
				{
					break;
				}
			}
		}
		///Binary search implementation to find a value with a given start index
		int find(T val, int start_idx = 0)
		{
			int mid; //Because it is an int it will be chopped off to a whole number
			int left = start_idx;
			int right = ArrayList<T>::mSize;
			while (left <= right)
			{
				mid = (left + right) / 2;
				if (ArrayList<T>::mData[mid] == val)
				{
					return mid;
				}
				if (mType == SortedArrayListType:: INCREASING)
				{
					if (ArrayList<T>::mData[mid] > val)
					{
						right = mid - 1;
					}
					else
					{
						left = mid + 1;
					}
					return -1;
				}
				else //(sortType == DECREASING)
				{
					if (ArrayList<T>::mData[mid] < val)
					{
						right = mid - 1;
					}
					else
					{
						left = mid + 1;
					}
					return -2;
				}
			}
		}
	};
}