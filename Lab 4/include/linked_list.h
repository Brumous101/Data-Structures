//Name: Kyle Johnson
//Class: ETEC2101
//Section: 01
//Assignment: 4
#pragma once
#include <ostream>

namespace ssuds
{
	template <class T>
	class LinkedList
	{
	protected:
		class node//node is protected because the user isn't even aware of its existence 
		{
		public:
			T mData;
			node* mNext;
			node* mPrev;
			node(T d) : mData(d), mNext(NULL), mPrev(NULL) {}		//the constructor, you can initialize all the attributes outside of the body 
			//for adding or removing, you can have more constructors if you want, or you can reroute pointers within the function and just call the same constructor 
		};
		//member variables 
		node* mStart;
		node* mEnd;
		int mSize;
		//member methods 
	public:

		class LinkedListIterator
		{
		protected:
			/// The reference to the vector we're iterating through

			/// If true, we increment mPosition when we iterate.
			bool mIsForward;
			node* cur;

		public:
			/// Main (only) constructor
			
			LinkedListIterator(const LinkedList& v, bool is_forward) //: mLinkedList(v), mIsForward(is_forward)
			{
				mIsForward = is_forward;
				if (mIsForward)
					cur = v.mStart;
				else//backwards
					cur = v.mEnd;
			}
			LinkedListIterator()
			{
				cur = NULL;
			}
			/// Gets the current element's value
			T& operator*()
			{
				return cur->mData;
			}
			/// Iterates (advances) the iterator
			void operator++()
			{
				//if (cur != NULL)
					if (mIsForward)
						cur = cur->mNext;
					else
						cur = cur->mPrev;
			}
			/// Are we equal to another iterator?  We are if it's the same vector and if the position is the same
			bool operator ==(const LinkedListIterator& i)
			{
				return (i.cur == cur);
			}
			/// Are we not equal to the given iterator (just the reverse of ==)...not sure why we need both...
			bool operator != (const LinkedListIterator& i)
			{
				return !(i.cur == cur);
			}
	};
		LinkedListIterator rbegin() const
		{
			return LinkedListIterator(*this, false);
		}


		LinkedListIterator begin() const
		{
			return LinkedListIterator(*this, true);
		}
		LinkedListIterator end() const
		{
			return LinkedListIterator();
		}
		void push_back(T val)
		{
			node* newn = new node(val);
			//case 1 – empty list 
			if (mStart == NULL || mEnd == NULL || mSize == 0)
			{
				mStart = mEnd = newn; //multiple assignments to the same thing 
			//note: this changes address 
			}
			//case 2 – not-empty list 
			else
			{
				newn->mPrev = mEnd;							//-> will go access the elements in box/node/data structure. this case its the previous ptr
				//note: this changes the value of the thing pointed at 
				mEnd->mNext = newn;
				mEnd = newn;
			}
			mSize++;
		}
		void push_front(T val)
		{
			node* newn = new node(val);
			//case 1 – empty list 
			if (mStart == NULL || mEnd == NULL || mSize == 0)
			{
				mStart = mEnd = newn; //multiple assignments to the same thing 
			//note: this changes address 
			}
			//case 2 – not-empty list 
			else
			{
				newn->mNext = mStart;							//-> will go access the elements in box/node/data structure. this case its the previous ptr
				//note: this changes the value of the thing pointed at 
				mStart->mPrev = newn;
				mStart = newn;
			}
			mSize++;
		}
		~LinkedList()
		{
			clear();
		}
		LinkedList()
		{
			mStart = NULL;
			mEnd = NULL;
			mSize = 0;
		}
		LinkedList(std::initializer_list<T>ilist) : mSize(), mStart(NULL), mEnd(NULL)	  //A constructor that accepts an ArrayList as an argument
		{
			for (T val : ilist)
			{
				push_back(val);
			}
		}
		int size() const
		{
			return mSize;
		}
		void insert(T element, int index)
		{
			node* newn = new node(element);
			node* cur = mStart;
			//std::cout << mSize<< std::endl;
			//Insert at first element
			if (index == 0)
			{
				push_front(element);
			}
			//Insertion in the middle of a list
			//For all middle nodes
			else if (index > 0 && index < mSize)
			{
				for (int i = 0; i < index; i++)							 //Changing the mNext of the previous node
				{
					cur = cur->mNext;									 //moving to the next item in the linked list
				}
				cur->mPrev->mNext = newn;							 //path acur -> means go to the box.
				newn->mPrev = cur->mPrev;
				newn->mNext = cur;
				cur->mPrev = newn;
				mSize++;
			}
			//Insert at last element
			else if (index == mSize)
			{
				//std::cout << "pushback" << std::endl;
				push_back(element);
			}
			else if (index < 0 || index > mSize)
			{
				throw std::out_of_range("Invalid index");
			}
		}
		T remove(int index)
		{
			//if index
			node* cur = mStart;
			T temp;
			//std::cout << mSize << std::endl;
			//For removing 1st node
			if (index == 0 && mSize >1)
			{
				//make second nodes mPrev NULL
				//mStart needs to be at the second one
				cur->mNext->mPrev = NULL;
				mStart = cur->mNext;
				temp = cur->mData;
				delete cur;
				mSize--;
				return temp;
			}

			//For all middle nodes
			if (index > 0 && index < mSize - 1)
			{
				for (int i = 0; i < index; i++)
				{
					cur = cur->mNext;									 //moving to the next item in the linked list
				}
				cur->mPrev->mNext = cur->mNext; //path acur -> means go to the box.
				cur->mNext->mPrev = cur->mPrev;
				temp = cur->mData;
				delete cur;
				mSize--;
				return temp;
			}

			//For the last element of the LinkedList
			if (index == (mSize - 1))
			{
				cur = mEnd;
				//make second nodes mPrev NULL
				//mStart needs to be at the second one
				cur->mPrev->mNext = NULL;
				mEnd = cur->mPrev; //one before the tail
				temp = cur->mData;
				delete cur;
				mSize--;
				return temp;
			}

			//Deleting only element in list
			if (index == 0 && mSize == 1)
			{
				mStart = NULL;
				mEnd = NULL;
				temp = cur->mData;
				delete cur;
				mSize--;
				return temp;
			}
			if (index < 0 || index > mSize)
			{
				throw std::out_of_range("Invalid index");
			}
		}
		void clear()
		{
			/// Destructor -- nothing needed currently.
			node* cur = mStart;
			while (cur != NULL)
			{
				node* next = cur->mNext;
				delete cur;
				cur = next;
			}
		}
		int find(T element, int start_index = 0)                           //It's always a two argument function! int index = 0 is always going to default to the start of the array
		{
			node* cur = mStart;
			for (int i = 0; i < start_index; i++)
			{
				cur = cur->mNext;
			}
			for (int i = start_index; i < mSize; i++)
			{
				if (element == cur->mData)
					return i;
				cur = cur->mNext;
			}
			return -1;
		}
		LinkedList& operator = (LinkedList& overloadEqualsOperator)
		{
			//add code
		}
		
		//Overloading the [] operator
		//We must overload the [] to allow us to index for removal and insertion!
		//This has to be a const because we used a const in the argument in t
		T& operator[](int index) const
		{
			node* cur = mStart;
			int i = 0;
			while (i != index)
			{
				node* nextn = cur->mNext;
				cur = nextn;
				i++;
			}
			//case for if index is out of range. Go to the given index in the list and return mData
			return cur->mData;
		}
	};																  //You need a semi-colon here to represent the end of the class.
	
	template <class T>
	//Overloading the << operator
	std::ostream& operator<< (std::ostream& os, const LinkedList<T>& overloadOperator)
	{
		int i;
		os << "[";
		for (i = 0; i < overloadOperator.size() - 1; i++)
			os << overloadOperator[i] << ", ";
		os << overloadOperator[i] << "]";
		return os;													 //What the output should be
	}
}