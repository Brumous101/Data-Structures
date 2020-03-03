//Name: Kyle Johnson
//Class: ETEC2101
//Section: 01
//Assignment: 5
#pragma once

#include <iostream>
#include <string>											      //Contains getline function (among other things)

namespace ssuds
{
	template <class T>
	///A templated class for ArrayList
	class ArrayList
	{
	protected:											          //This is the class definition. Our constructor will refer to this. THIS IS NEVER CALLED EXPLICITLY
		///Holds the data of a given type
		T* mData;										          //initialized as garbage
		///Holds the length of the array_list
		int mSize;										          //initialized as garbage
		///Holds the amount of memory allocated to the array_list
		int mCapacity;									          //initialized as garbage
		///The variable used to increase our dynamically allocated array
		const int mCapacityIncrease = 5;					      //initialized with starting size or make it nul and allocate

	public:
		ArrayList()											      //This is the Constructor. We will be calling this and changing the garbage values.
		{
			mSize = 0;
			mCapacity = mCapacityIncrease;                        //Initializes mCapacity to 5
			mData = new T[mCapacity];					          //new allocates more memory. T is the Type that is templated. Making an array mCapacity of long (5 big).
		}
		///The ArrayList constructor 
		ArrayList(const ArrayList& other)
		{
#if _DEBUG && SHOW_DEBUG_MSGS
			std::cout << "[[Copy Constructor]]" << std::endl;
#endif
			mCapacity = other.mCapacity;
			mData = new T[mCapacity];
			for (unsigned int i = 0; i < other.mSize; i++)
				mData[i] = other.mData[i];
			mSize = other.mSize;
		}
		///The getter to obtain the mSize variable
		int size()
		{
			return mSize;								          //Called because protected class. Only want users to have access at certain. THIS IS A GETTER
		}
		///The getter to obtain the mCapacity variable
		int capacity()
		{
			return mCapacity;							          //Called because protected class. Only want users to have access at certain. THIS IS A GETTER
		}
		///The push_back function that will add to the back of the array_list and grow the memory
		void push_back(T val)
		{
			if (mSize == mCapacity)
			{
				Grow();										      //Grow() is calling on the Grow function to increase the size of the array.
			}
			mData[mSize] = (val);							          //Note: We don't use mSize-1 because of how arrays work
			mSize++;
		}
		///The ArrayListIterator is a container data structure that will iterate through the array
		class ArrayListIterator
		{
		protected:
			///The location of our array_list
			ArrayList& mArray;
			///The indexing variable
			int mPos;
		public:
			///Points to where we are iterating
			ArrayListIterator(ArrayList& a, int p) : mArray(a) //BUG: Can never have an ArrayList that never points at nothing. Won't initialize it? Use initializer list from lab 1. the :mArray(a) should fix it 
			{
				mPos = p;
			}
			///Make sure we are at the correct index. Also need to make sure it isn't the same array. We can do this by comparing addresses
			bool operator != (const ArrayListIterator& other)
			{
				return mPos != other.mPos || &mArray != &other.mArray;
			}
			///Make sure we are at the correct index. Also need to make sure it isn't the same array. We can do this by comparing addresses
			bool operator ==(const ArrayListIterator& other)
			{
				return mPos == other.mPos || &mArray == &other.mArray;
			}
			///Overloading the pointer (dereference) operator. Allows to change the value.
			T& operator * ()
			{
				return mArray[mPos];
			}
			///overiding the ++ operator
			void operator++()
			{
				mPos++; //may not be a return
			}
		};
		///Points to the beginning of the array_list
		ArrayListIterator begin()
		{
			return ArrayListIterator(*this, 0);
		}
		///Points to the end of the array_list
		ArrayListIterator end()
		{
			return ArrayListIterator(*this, mSize);
		}
		///Allocates more memory for the array_list
		void Grow()
		{									      //This is a preprocessor instruction that will check to see what release the code is being ran in
			#ifdef _DEBUG
			std::cout << "[[GROW]]" << std::endl;
			#endif											      //Shows the end of the 
			mCapacity = mCapacity + mCapacityIncrease;
			T* temp = new T[mCapacity];						      //T * means we are making a new array to allocate. * Points to the start of the array.
			for (int i = 0; i < mSize; i++)
			{
				temp[i] = mData[i];
			}
			delete[]mData;                                        //mData HAS to have [] because compiler needs to know its a group of objects
			mData = temp;
		}
		///Deallocates memory from the array_list
		void Shrink()
		{
			mCapacity = mCapacity - mCapacityIncrease;
			T* temp = new T[mCapacity];						      //T * means we are making a new array to allocate. * Points to the start of the array.
			for (int i = 0; i < mSize; i++)
			{
				temp[i] = mData[i];
			}
			delete[]mData;                                        //mData HAS to have [] because compiler needs to know its a group of objects
			mData = temp;
		}
		///Inserts an element into the array_list
		void insert(T element, int index)
		{
			if (mSize == mCapacity)
			{
				std::cout << "[[GROW]]" << std::endl;
				Grow();
			}
			//We are inserting one. It's okay if we are at capacity because the other calls will do the same if statement at start of call
			for (int i = size(); i > index; i--)                  //If shuffling backwards i needs to decrease
			{
				mData[i] = mData[i - 1];                            //Copy the value to one bigger so shuffling everything to the right 1.

			}
			mData[index] = (element);
			mSize++;
		}
		///Removes an element from the array_list
		T remove(int index)
		{
			T temp;
			if (index < 0 || index >(size() - 1))
			{
				throw std::out_of_range("EXCEPTION. You attempted to index outside of the array");
			}
			temp = mData[index];
			for (; index < size() - 1; index++)						//If shuffling backwards i needs to decrease
			{
				if (index != size() - 1)								//if index is the last element in the array DO NOT pull
				{
					mData[index] = mData[index + 1];                  //Copy the value to one bigger so shuffling everything to the right 1.
				}
			}
			mSize--;
			if (mSize == (mCapacity - mCapacityIncrease))           //Checking to see if the capacity is unnecessarily long to save memory.
			{
				std::cout << "[SHRINK]" << std::endl;
				Shrink();
			}
			return temp;
		}
		///Clears the array_list
		void clear()
		{
			mCapacity = 5;
			mSize = 0;												 //T * means we are making a new array to allocate. * Points to the start of the array.
			delete[]mData;										     //mData HAS to have [] because compiler needs to know its a group of objects
			mData = NULL;
			mData = new T[mCapacity];
		}
		///Finds an element in an array_list given a starting index
		int find(T element, int index = 0)                           //It's always a two argument function! int index = 0 is always going to default to the start of the array
		{
			for (; index < mSize; index++)
			{
				if (index < 0 || index > mSize - 1)                   //Checking to see if it's in range
				{
					return -1;                                       //Bad user entry just shows that is not in there
				}
				if (mData[index] == element)
				{
					return index;
				}
				if (index == mSize)
				{
					return -1;										 //Bad user entry
				}
			}
			return -1;												 //Bad user entry
		}
		///Overload for the equals operator
		ArrayList& operator = (ArrayList& overloadEqualsOperator)	 //We have to overload the equals operator because this will cause problems copying over the ArrayList EXACTLY how it was. (Shadow Copy).
		{												     		 //A Shadow Copy is where we have two different instances (this case is arrays). Where anything that happens to the first instance effects the second.
			delete[]mData;											 //This is bad in particular for variables that will be used separately. We may not want to change the master/ original.
			mData = new T[overloadEqualsOperator.mCapacity];
			mSize = overloadEqualsOperator.mSize;
			mCapacity = overloadEqualsOperator.mCapacity;
			for (int i = 0; i < overloadEqualsOperator.mSize; i++)	 //Why did we not use a Getter here?
			{
				mData[i] = overloadEqualsOperator[i];
			}
			return *this;
		}
		///Overload for the brackets operator
		T& operator[](int index)
		{
			return mData[index];
		}
		///A constructor that accepts another array_list as an argument
		ArrayList(ArrayList& a)										  //A constructor that accepts an ArrayList as an argument
		{
			mData = new T[a.mCapacity];
			mSize = a.mSize;
			mCapacity = a.mCapacity;
			for (int i = 0; i < a.mSize; i++)						  //Why did we not use a Getter here?
			{
				mData[i] = a[i];
			}
		}
	};																  //You need a semi-colon here to represent the end of the class.
	template <class T>
	std::ostream& operator<< (std::ostream& os, ArrayList<T>& overloadOperator)
	{
		int i;
		os << "[";
		if (overloadOperator.size() > 0)
		{
			for (i = 0; i < overloadOperator.size() - 1; i++)
			{
				os << overloadOperator[i] << ", ";
			}
			os << overloadOperator[i];
		} 
		os << "]";
		return os;													 //What the output should be
	}
}