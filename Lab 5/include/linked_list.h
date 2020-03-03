//Name: Kyle Johnson
//Class: ETEC2101
//Section: 01
//Assignment: 5
#pragma once
#include <ostream>

namespace ssuds
{
	template <class T>
	///The Linked List class.
	class LinkedList
	{
	protected:
		///The protected node that holds the data in the linked list.
		class node//node is protected because the user isn't even aware of its existence 
		{
		public:
			///The Data inside of the node of the linked list
			T mData;
			///The pointer that points to the next node of the linked list
			node* mNext;
			///The pointer that points to the previous element of the linked list
			node* mPrev;
			///the constructor, you can initialize all the attributes outside of the body 
			node(T d) : mData(d), mNext(NULL), mPrev(NULL) {}
			//for adding or removing, you can have more constructors if you want, or you can reroute pointers within the function and just call the same constructor 
		};
		//member variables 
		///The pointer that keeps track of the start of the linked list
		node* mStart;
		///The pointer that keeps track of the end of the linked list
		node* mEnd;
		///Keeps track of the size of the linked list
		int mSize;
		//member methods 
	public:
		///The LinkedListIterator class
		class LinkedListIterator
		{
		protected:
			/// The reference to the vector we're iterating through

			/// If true, we increment mPosition when we iterate.
			bool mIsForward;
			///The node pointer that will point to the current node in the list.
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
		///The linked_list iterator that keeps track of the beginning of the linked_list in reverse
		LinkedListIterator rbegin() const
		{
			return LinkedListIterator(*this, false);
		}

		///The linked_list iterator that keeps track of the beginning of the linked_list
		LinkedListIterator begin() const
		{
			return LinkedListIterator(*this, true);
		}
		///The linked_list iterator that keeps track of the end of the linked_list
		LinkedListIterator end() const
		{
			return LinkedListIterator();
		}
		///The push_back function that will do an insertion on the start of the list
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
		///the push_front function that will insert a node at the end of the linked_list
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

		///A constructor that accepts an ArrayList as an argument
		LinkedList(std::initializer_list<T>ilist) : mSize(), mStart(NULL), mEnd(NULL)	  
		{
			for (T val : ilist)
			{
				push_back(val);
			}
		}
		///the size function that will return the mSize of the linked_list
		int size() const
		{
			return mSize;
		}
		///The insert function that will insert a node at a given index
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
		///The remove function that will remove an element at a given index
		T remove(int index)
		{
			if (index < 0 || index >= (int)mSize)
				throw std::out_of_range("Invalid index");

			if (mSize == 1)
			{
				// There's only one element here.  We're clearing the list
				T val = mStart->mData;
				delete mStart;
				mStart = mEnd = NULL;
				mSize = 0;
				return val;
			}
			else if (index == 0)
			{
				// Remove the first element
				node* next = mStart->mNext;
				next->mPrev = NULL;
				T val = mStart->mData;
				delete mStart;
				mStart = next;
				mSize--;
				return val;
			}
			else if (index == mSize - 1)
			{
				// Remove the last element
				node* prev = mEnd->mPrev;
				prev->mNext = NULL;
				T val = mEnd->mData;
				delete mEnd;
				mEnd = prev;
				mSize--;
				return val;
			}
			else
			{
				// We're somewhere in the middle.  First navigate to the proper spot.  As a (small)
				// optimization, I pick the closer side to get to the current node
				node* cur;
				if (index < (int)mSize / 2)
				{
					cur = mStart;
					for (int i = 0; i < index; i++)
						cur = cur->mNext;
				}
				else
				{
					cur = mEnd;
					for (int i = mSize - 1; i > index; i--)
						cur = cur->mPrev;
				}
				node* next = cur->mNext;
				node* prev = cur->mPrev;
				next->mPrev = prev;
				prev->mNext = next;
				T val = cur->mData;
				delete cur;
				mSize--;
				return val;
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

		///The find function that will look for an element given a starting index
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
		///Overload for the equals operator
		LinkedList& operator = (LinkedList& overloadEqualsOperator)
		{
			//add code
		}
		
		///Overloading the [] operator. We must overload the [] to allow us to index for removal and insertion! This has to be a const because we used a const in the argument in t
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