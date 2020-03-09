#pragma once
#include <linked_list.h>

namespace ssuds
{
	/// A Stack is a simple LIFO data structure (last-in-first-out).  Here I implement
	/// it using linked list as these support fast push / pop from the ends of the list,
	/// which is what you'll primarily use with a stack.  For illustration, I 
	/// implemented this class using a "has-a" (rather than a "is-a" / inheritance) approach.
	template <class T>
	class Stack
	{
	protected:
		/// The "contained" linked list
		LinkedList<T> mList;

	public:
		/// Adds the given element to the beginning of the underlying list
		void push(T val)
		{
			mList.push_front(val);
		}

		/// Removes and returns the first element in the underlying list
		T pop()
		{
			return mList.remove(0);
		}


		/// Returns a reference to the next item to be popped, or raises an execption if the stack is empty.
		T& peek()
		{
			if (mList.size() > 0)
				return mList[0];
			else
				throw std::out_of_range("Can't peek into an empty stack");
		}


		/// Returns true if this stack is empty
		bool empty()
		{
			return mList.size() == 0;
		}
	};
}

