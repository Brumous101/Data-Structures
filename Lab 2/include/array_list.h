#pragma once

#include <iostream>
#include <string>											      //Contains getline function (among other things)

namespace ssuds
{
	template <class T>
	class ArrayList
	{
	protected:											          //This is the class definition. Our constructor will refer to this. THIS IS NEVER CALLED EXPLICITLY
		T* mData;										          //initialized as garbage
		int mSize;										          //initialized as garbage
		int mCapacity;									          //initialized as garbage
		const int mCapacityIncrease = 5;					      //initialized with starting size or make it nul and allocate

	public:
		ArrayList()											      //This is the Constructor. We will be calling this and changing the garbage values.
		{
			mSize = 0;
			mCapacity = mCapacityIncrease;                        //Initializes mCapacity to 5
			mData = new T[mCapacity];					          //new allocates more memory. T is the Type that is templated. Making an array mCapacity of long (5 big).
		}
		int size()
		{
			return mSize;								          //Called because protected class. Only want users to have access at certain. THIS IS A GETTER
		}
		int capacity()
		{
			return mCapacity;							          //Called because protected class. Only want users to have access at certain. THIS IS A GETTER
		}
		void push_back(T val)
		{
			if(mSize == mCapacity)
			{											    
				Grow();										      //Grow() is calling on the Grow function to increase the size of the array.
			}
			mData[mSize]=(val);							          //Note: We don't use mSize-1 because of how arrays work
			mSize++;
		}
		void Grow()
		{														  //This is a preprocessor instruction that will check to see what release the code is being ran in
			#ifdef _DEBUG
				std::cout << "[[GROW]]" << std::endl;
			#endif											      //Shows the end of the 
			mCapacity = mCapacity + mCapacityIncrease;
			T* temp = new T[mCapacity];						      //T * means we are making a new array to allocate. * Points to the start of the array.
			memcpy(temp, mData, sizeof(T) * mSize);               //third argument must be the size in bytes
			delete[]mData;                                        //mData HAS to have [] because compiler needs to know its a group of objects
			mData = temp;
		}
		void Shrink()
		{
			mCapacity = mCapacity - mCapacityIncrease;
			T* temp = new T[mCapacity];						      //T * means we are making a new array to allocate. * Points to the start of the array.
			memcpy(temp, mData, sizeof(T) * mSize);               //third argument must be the size in bytes
			delete[]mData;                                        //mData HAS to have [] because compiler needs to know its a group of objects
			mData = temp;
		}
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
				mData[i] = mData[i-1];                            //Copy the value to one bigger so shuffling everything to the right 1.

			}
			mData[index] = (element);
			mSize++;
		}
		void remove(int index)
		{
			if (index < 0 || index >(size() - 1))
			{
				throw std::out_of_range("EXCEPTION. You attempted to index outside of the array");
			}
			for (; index < size()-1; index++)						//If shuffling backwards i needs to decrease
			{
				if(index != size()-1)								//if index is the last element in the array DO NOT pull
					mData[index] = mData[index+1];                  //Copy the value to one bigger so shuffling everything to the right 1.
			}
			mSize--;
			if (mSize == (mCapacity - mCapacityIncrease))           //Checking to see if the capacity is unnecessarily long to save memory.
			{
				std::cout << "[SHRINK]" << std::endl;
				Shrink();
			}
		}
		void clear()
		{
			mCapacity = 5;
			mSize = 0;
			T* temp = new T[mCapacity];								 //T * means we are making a new array to allocate. * Points to the start of the array.
			delete[]mData;										     //mData HAS to have [] because compiler needs to know its a group of objects
			mData = temp;
		}
		int find(T element, int index = 0)                           //It's always a two argument function! int index = 0 is always going to default to the start of the array
		{
			for (; index < mSize; index++)
			{
				if (index < 0 || index > mSize -1)                   //Checking to see if it's in range
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
		T& operator[](int index)
		{
			return mData[index];
		}
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
		for (i = 0; i < overloadOperator.size() -1; i++)
			os << overloadOperator[i] << ", ";
		os << overloadOperator[i] << "]";
		return os;													 //What the output should be
	}
}