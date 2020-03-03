//Name: Kyle Johnson
//Class: ETEC2101
//Section: 01
//Assignment: 5
#pragma once
namespace ssuds
{
	template<class T>
	///The Queue class provides functions that act as a queue
	class Queue: protected LinkedList<T> //want protected functions
	{
	public:
		///The push function that will push an element onto the opposite side of removal.
		void push(T val)
		{
			this->push_back(val);
		}
		///The peek function that will say what is about to be removed by the next call to pop
		T peek()
		{
			return (*this)[0];// LinkedList<T>::mData[0];
		}
		///The pop function that will remove the element added lastly to the queue
		T pop()
		{
			return this ->remove(0);
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