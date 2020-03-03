#pragma once
#include <cassert>
#include <iostream>
#include <exception>

// If you set this to 0, ArrayList messages should not show.  I put this here because after this lab,
// we don't really want those debug messages cluttering things up.
#define SHOW_DEBUG_MSGS 1

namespace ssuds
{
	/// An ArrayList is similar to (but more simple than) std::vector.  Behind the scenes
	/// is contains a dynamically created array of T objects.  This array is resized periodically
	/// when we run out of capacity (currently by a fixed amount, although that could be changed
	/// to doubling, tripling, if desired -- that would increase the amortized efficiency, but
	/// would (drastically) increase the memory footprint).
	template<class T> 
	class ArrayList
	{
	protected:
		/// The dynamically allocated array
		T* mData;
		const unsigned int msCapacityIncrease = 5;
		unsigned int mCapacity;
		unsigned int mSize;

	public:
		/// Default constructor -- allocates msCapacityIncrease
		ArrayList() : mSize(0), mData(NULL)
		{
			mCapacity = msCapacityIncrease;
			mData = new T[msCapacityIncrease];
		}

		/// Copy constructor -- make a copy of the other guy
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

		/// This is a new C++11 feature called a "move constructor".  It will get called
		/// when we're being asked to create a new ArrayList as part of a return value.  For
		/// example, if a function returns an ArrayList.  Pre-C++11, we'd create an ArrayList
		/// in the function and make a copy (using the copy constructor) above, then immediately
		/// destroy the temporary.  This sidesteps the unecessary middle step.
		ArrayList(ArrayList&& other)
		{
#if _DEBUG && SHOW_DEBUG_MSGS
			std::cout << "[[In move constructor]]" << std::endl;
#endif
			mCapacity = other.mCapacity;
			mData = other.mData;
			other.mData = NULL;
			mSize = other.mSize;
		}


		/// The destructor
		~ArrayList()
		{
			if (mData)
				delete[] mData;
		}


		/// This method is called if the uses says a = b; where a and b are ArrayLists of the same
		/// template type.  It makes a copy of b.
		ArrayList& operator = (const ArrayList & other)
		{
			// If the (silly) user assigns themself to themself, short-circuit this operation
			if (this != &other)
			{
				// Pretty much like the copy-constructor, but we need to free up our
				// memory first.  And at the end we need to return a reference to
				// ourself (in case we're in an assignment chain like a = b = c = ...)
#if _DEBUG && SHOW_DEBUG_MSGS
				std::cout << "[[Overloadied Assignment Operator]]" << std::endl;
#endif
				delete[] mData;
				mCapacity = other.mCapacity;
				mData = new T[mCapacity];
				for (unsigned int i = 0; i < other.mSize; i++)
					mData[i] = other.mData[i];
				mSize = other.mSize;
			}

			// Return a reference to ourself.
			return *this;
		}


		/// This allows us to do a[0] and similar for ArrayLists.
		T& operator [] (unsigned int index) const
		{
			if (index < mSize)
				return mData[index];
			else
				throw std::out_of_range("Invalid index");
		}

		
		/// Gets the number of available slots in the array.  Note: This is not the same as the
		/// number of *used* slots (that's the size).  Once this capacity is reached, we'll do the
		/// costly "grow" operation
		unsigned int capacity() const
		{
			return mCapacity;
		}

	protected:
		// This method should be called before adding an element.  Determines
		// if we're currently at capacity.  If we are, resize the array
		// to be of a bigger size (and return true).  Do nothing and return
		// false otherwise.
		bool check_for_capacity()
		{
			if (mSize == mCapacity)
			{
#if _DEBUG && SHOW_DEBUG_MSGS
				std::cout << "[[GROW]]" << std::endl;
#endif
				T* temp_data = new T[mCapacity + msCapacityIncrease];
				for (unsigned int i = 0; i < mSize; i++)
					temp_data[i] = mData[i];
				delete[] mData;
				mData = temp_data;
				mCapacity = mCapacity + msCapacityIncrease;
				return true;
			}
			return false;
		}

	public:
		/// Resets the array to its initial (empty) state. 
		void clear()
		{
			if (mData)
			{
				delete[] mData;
				mData = NULL;
			}
			mData = new T[msCapacityIncrease];
			mCapacity = msCapacityIncrease;
			mSize = 0;
		}


		/// Finds the first occurrence of the given index, starting at the given index.  -1 is returned
		/// if that item can't be found
		int find(const T& val, int start_index = 0) const
		{
			for (int i = start_index; i < (int)mSize; i++)
			{
				if (val == mData[i])
					return i;
			}
			return -1;
		}


		/// Inserts the given element at the given index, shifting everything to the right.  Note: You can't
		/// append using this method (use push_back for that)
		void insert(const T& item, int index)
		{
			if (index < 0 || index >= (int)mSize)
				throw std::out_of_range("Invalid index");
			check_for_capacity();
			for (int i = mSize; i > index; i--)
				mData[i] = mData[i - 1];
			mData[index] = item;
			mSize++;
		}



		/// Appends the given element to the end of the array, resizing if necessary
		void push_back(const T& item)
		{
			check_for_capacity();
			mData[mSize++] = item;
		}



		/// Removes the element at the given index.  It resizes the array if we go msCapacityIncrease below capacity
		void remove(int index)
		{
			if (index < 0 || index >= (int)mSize)
				throw std::out_of_range("Invalid index");
			// Remove that offending index by shifting everything down.  Note: the last element in the
			// array is still there!  But...we can't access it, so no worries.  For some values (ints for example), 
			// we could set that last value to 0.  But since this is a templated class, we don't know what to set it
			// to for *all* possible values.  
			for (int i = index; i < (int)mSize - 1; i++)
				mData[i] = mData[i + 1];
			mSize--;

			// I made the choice to resize if we go below capacity.  It would've been OK to just keep capacity where it was at.
			if (mCapacity - mSize >= msCapacityIncrease)
			{
				T* temp_data = new T[mCapacity - msCapacityIncrease];
				for (unsigned int i = 0; i < mSize; i++)
					temp_data[i] = mData[i];
				delete[] mData;
				mData = temp_data;
				mCapacity = mCapacity - msCapacityIncrease;
			}
		}


		/// Gets the number of *used* slots in the array.
		unsigned int size() const
		{
			return mSize;
		}



	public:
		/// This class is used to iterate through elements of an ArrayList
		class ArrayListIterator
		{
		protected:
			/// The reference to the vector we're iterating through
			const ArrayList& mArray;

			/// The spot we're currently at in the iteration process
			unsigned int mPosition;

			/// If true, we increment mPosition when we iterate.
			bool mIsForward;

		public:
			/// Main (only) constructor
			ArrayListIterator(const ArrayList& v, unsigned int start_pos, bool is_forward) : mArray(v), mPosition(start_pos), mIsForward(is_forward)
			{

			}

			/// Destructor -- nothing needed currently.
			~ArrayListIterator()
			{

			}

			/// Gets the current element's value
			T& operator*()
			{
				return mArray[mPosition];
			}

			/// Iterates (advances) the iterator
			void operator++()
			{
				if (mIsForward)
					mPosition++;
				else
					mPosition--;
			}

			/// Are we equal to another iterator?  We are if it's the same vector and if the position is the same
			bool operator ==(const ArrayListIterator& i)
			{
				return (&i.mArray == &mArray && i.mPosition == mPosition);
			}

			/// Are we not equal to the given iterator (just the reverse of ==)...not sure why we need both...
			bool operator != (const ArrayListIterator & i)
			{
				return !(&i.mArray == &mArray && i.mPosition == mPosition);
			}
		};


		ArrayListIterator rbegin() const
		{
			return ArrayListIterator(*this, mSize - 1, false);
		}


		ArrayListIterator begin() const
		{
			return ArrayListIterator(*this, 0, true);
		}



		ArrayListIterator end() const
		{
			ArrayListIterator i = ArrayListIterator(*this, mSize, true);
			return i;
		}


	};	// end of ArrayList class













	/// The stream operator for ArrayLists
	template <class T>
	std::ostream& operator<<(std::ostream& os, const ArrayList<T>& a)
	{
		os << "[";
		bool first = true;
		for (int i = 0; i < (int)a.size(); i++)
		{
			if (!first)
				os << ", ";
			else
				first = false;
			os << a[i];
		}
		os << "]";
		return os;
	}
}
