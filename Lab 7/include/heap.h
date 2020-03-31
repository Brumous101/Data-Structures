//Name: Kyle Johnson
//Class: ETEC2101
//Section: 01
//Assignment: 7
#pragma once
#include <ostream>
#include <array_list.h>
//#include <SFML/Graphics.hpp>

namespace ssuds
{
	enum class HeapType {MIN_HEAP, MAX_HEAP};

	template <class T>
	///The Linked List class.
	class Heap
	{
	protected:
		HeapType mType;
		ArrayList<T> alist;
	public:
		Heap()
		{
			//intentionally empty?
		}
		Heap(HeapType d) : mType( d)//he defines it as max heap in main
		{
		}
		Heap(HeapType d, std::initializer_list<T> a) : mType(d)//he defines it as max heap in main
		{
			//for things of type T in a (the list). This is a for each loop that goes through the whole list
			for(T val: a)
			{
				push(val);
			}
		}
		void push(T val)
		{
			T temp;
			int childIndex, parentIndex;
			alist.push_back(val);
			childIndex = alist.find(val);//index of where we pushed the value to
			//binary search
			while (childIndex >= 1)//not the first element
			{
				parentIndex = (childIndex - 1) / 2;

				if (mType == HeapType::MIN_HEAP)
				{
					if (alist[parentIndex] > alist[childIndex])
					{
						//swap them
						temp = alist[parentIndex];
						alist[parentIndex] = alist[childIndex];
						alist[childIndex] = temp;
						childIndex = parentIndex;
					}
					else
					{
						break;
					}
				}
				else//mType == HeapType::MAX_HEAP
				{
					if (alist[parentIndex] < alist[childIndex])
					{
						//swap them
						temp = alist[parentIndex];
						alist[parentIndex] = alist[childIndex];
						alist[childIndex] = temp;
						childIndex = parentIndex;
					}
					else
					{
						break;
					}
				}
			}
		}

		T peek()
		{
			return alist[0];
		}

		int size()
		{
			return alist.size();
		}

		bool empty()
		{
			if (size() == 0)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		T pop()
		{
			if (alist.size() > 0)
			{
				T temp;
				temp = alist[0];
				alist[0] = alist[alist.size() - 1];
				alist[alist.size() - 1] = temp;
				alist.remove(alist.size() - 1);
				int parentIndex = 0, childIndex;

				while (true)//not the first element
				{
					childIndex = compareChildren(parentIndex);// Compares the two children of a given parent
					if (childIndex == -1)
					{
						break;
						//return std::cout << "Error out of range";
					}

					if (mType == HeapType::MIN_HEAP)
					{
						//Is the heap in order?
						//No:
						if (alist[parentIndex] < alist[childIndex] /*&& childIndex < alist.size()*/ )
						{
							//find the best child and compare it to it's parent to see if best child is better than its parent
							//best child = smallest
							break;//correct order with parent
						}
						//Yes: Swap
						//swap them
						T tempVal = alist[parentIndex];
						alist[parentIndex] = alist[childIndex];
						alist[childIndex] = tempVal;
						parentIndex = childIndex;
					}
					else//mType == HeapType::MAX_HEAP
					{
						if (alist[parentIndex] > alist[childIndex] /*&& childIndex < alist.size() */)
						{
							break;
						}
						//swap them
						T tempVal = alist[parentIndex];
						alist[parentIndex] = alist[childIndex];
						alist[childIndex] = tempVal;
						parentIndex = childIndex;
						//best child biggest z is better than a
					}
				}
				return temp;
			}
		}
		int compareChildren(int parentIndex)
		{
			int leftChild, rightChild; //working with indexes
			leftChild = (parentIndex * 2) + 1;
			rightChild = (parentIndex * 2) + 2;

			if (alist.size() <= leftChild) // No kids at all
			{
				return -1;
			}

			if (alist.size() <= rightChild)//right doesnt exists    
			{
				return leftChild;
			}

			if (alist.size() > 0 )//we have a both kids
			{
				if (mType == HeapType::MIN_HEAP)
				{
					if (alist[leftChild] < alist[rightChild])
					{
						return leftChild;
					}
					else
					{
						return rightChild;
					}
				}
				else
				{
					if (alist[leftChild] > alist[rightChild])
					{
						return leftChild;
					}
					else
					{
						return rightChild;
					}
				}
			}
			else
			{
				return -1;
			}
		}
		///Bracket overload
		T& operator [] (unsigned int index) const
		{
			if (index < alist.size())
				return alist[index];
			else
				throw std::out_of_range("Invalid index");
		}
		friend std::ostream& operator<< (std::ostream& os, const Heap<T>& overloadOperator)
		{
			os << overloadOperator.alist;
			return os;
		}
	};	
}