//Name: Kyle Johnson
//Class: ETEC2101
//Section: 01
//Assignment: 5
#pragma once
/*
push adds
pop removes
peek returns the value
empty tells if there is stuff to pop
*/

namespace ssuds
{
	template<class T>
	///The Stack class
	class Stack : protected LinkedList<T> //want protected functions
	{
	public:
		///The push function that will push an element onto the stack.
		void push(T val)
		{
			this->push_front(val);
		}
		///The peek function that will say what is about to be removed by the next call to pop
		T peek()
		{
			return (*this)[0];// LinkedList<T>::mData[0];
		}
		///The pop function that will remove the element most recently added to the stack
		T pop()
		{
			return this->remove(0);
		}
		///The empty function that checks to see if the list is empty or not
		bool empty()
		{
			if (LinkedList<T>::mSize == 0)
			{
				return true;
			}
			else//(LinkedList<T>::mSize != 0)
			{
				return false;
			}
		}
	};
}