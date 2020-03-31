#pragma once
#include <array_list.h>

namespace ssuds
{
	/// An enum used to identify if this is an increasing-order (small to big) or decreasing-
	/// order SortedArrayList
	enum class SortedArrayListType { INCREASING, DECREASING };

	template <class T>
	class SortedArrayList : public ArrayList<T>
	{
	// Note: since we're using inheritance, we only put the *new* attributes here
	protected:
		/// The type of SortedArrayList 
		SortedArrayListType mType;

	public:

		/// Basic constructor
		SortedArrayList(SortedArrayListType tp) : mType(tp)
		{
			// The base-class constructor did most of the work here.
		}

		/// Copy constructor -- make a copy of the other guy
		SortedArrayList(const SortedArrayList& other) : ArrayList<T>(), mType(other.mType)
		{
			// The base-class constructor did everything
			int x = 15;
		}


		/// Copy constructor for (non-sorted) ArrayList
		SortedArrayList(const ArrayList<T>& other, SortedArrayListType tp) : mType(tp), ArrayList<T>(other)
		{
			// The base-class constructor put a copy of all data into our array

			// Apply the bubble-sort algorithm
			for (int i = 0; i < (int)ArrayList<T>::mSize; i++)
			{
				bool in_order = true;
				for (int j = 0; j < (int)ArrayList<T>::mSize - 1 - i; j++)
				{
					if (out_of_order(j, j + 1))
					{
						swap(j, j + 1);
						in_order = false;
					}
				}
				if (in_order)
					break;			// early-exit!
			}
		}



		/// This method is called if the uses says a = b; where a and b are ArrayLists of the same
		/// template type.  It makes a copy of b.
		SortedArrayList& operator = (const SortedArrayList & other)
		{
			// If the (silly) user assigns themself to themself, short-circuit this operation
			if (this != &other)
			{
				// Pretty much like the copy-constructor, but we need to free up our
				// memory first.  And at the end we need to return a reference to
				// ourself (in case we're in an assignment chain like a = b = c = ...)
				delete[] Array::mData;
				Array::mCapacity = other.mCapacity;
				Array::mData = new T[Array::mCapacity];
				for (unsigned int i = 0; i < other.mSize; i++)
					Array::mData[i] = other.mData[i];
				Array::mSize = other.mSize;
			}

			// Return a reference to ourself.
			return *this;
		}





		/// Finds the first occurrence of the given index, starting at the given index.  -1 is returned
		/// if that item can't be found.   Uses the binary-search algorithm.
		int find(const T & val, int start_index = 0) const
		{
			int left, right;
			left = start_index;
			right = Array::mSize - 1;
			while (left <= right)
			{
				int mid = (left + right) / 2;
				if (val == Array::mData[mid])
					return mid;
				else if (val < Array::mData[mid])
					right = mid - 1;
			}
			return -1;
		}


		/// Adds the element to its correct spot in the SortedArrayList.  The 
		/// index it was inserted at is returned.
		int add(T item)
		{
			// Add the new item to the end using our base-class method
			ArrayList<T>::push_back(item);

			// Now, shift elements down until the new one is in the right spot
			int i = 0;
			for (i = ArrayList<T>::mSize - 2; i >= 0; i--)
			{
				if (out_of_order(i, i + 1))
					swap(i, i + 1);
				else
					break;
			}
			return i;
		}


		/// Re-route the insert method to add so we preserve the in-order aspect
		void insert(T val, int index) 
		{
			add(val);
		}



		/// Re-route the push_back method to add so we preserve the in-order aspect
		void push_back(T item) 
		{
			add(item);
		}

	protected:
		/// Are the elements at these two spots out of order?  For example, if increasing and
		/// mData[i] > mData[j], the result will be true.
		bool out_of_order(int i, int j)
		{
			return (mType == SortedArrayListType::INCREASING && ArrayList<T>::mData[i] > ArrayList<T>::mData[j]) ||
				(mType == SortedArrayListType::DECREASING && ArrayList<T>::mData[i] < ArrayList<T>::mData[j]);
		}


		/// Swaps the elements at position i and j
		void swap(int i, int j)
		{
			T temp = ArrayList<T>::mData[i];
			ArrayList<T>::mData[i] = ArrayList<T>::mData[j];
			ArrayList<T>::mData[j] = temp;
		}
	};
}
