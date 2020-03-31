#pragma once
#include <linked_list.h>

namespace ssuds
{
	/// A Queue is a simple FIFO data structure (first-in-first-out).  Here I implement
	/// it using linked list as these support fast push / pop from the ends of the list,
	/// which is what you'll primarily use with a queue.
	template <class T>
	class Queue : protected LinkedList<T>
	{
	public:
		/// Adds this element to the front of the underlying list
		void push(T val)
		{
			LinkedList<T>::push_front(val);
		}

		/// Removes and returns the element at the end of the list
		T pop()
		{
			return LinkedList<T>::remove(LinkedList<T>::mSize - 1);
		}


		/// Return the next item that will be popped (raises an exception if the queue is empty)
		T& peek()
		{
			if (LinkedList<T>::mSize > 0)
				return LinkedList<T>::mEnd->mData;
			else
				throw std::out_of_range("Can't peek into an empty queue");
		}


		/// Returns true if the underlying list size is 0.
		bool empty()
		{
			return LinkedList<T>::mSize == 0;
		}
	};
}
