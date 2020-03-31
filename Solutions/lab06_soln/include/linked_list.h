#pragma once
#include <iostream>

namespace ssuds
{
	template <class T>
	/// A LinkedList is a collection of non-contiguous nodes.  To get to
	/// a certain spot, you must traverse the list.
	class LinkedList
	{
	protected:
		/// This is a *hidden* class.  It is used to represent a single
		/// "link" in the node.  It contains the data (payload) and pointers
		/// to the next and previous nodes.
		class node
		{
		public:
			T mData;
			node * mNext;
			node * mPrev;

			node(T val) : mData(val), mNext(NULL), mPrev(NULL)
			{
				// Intentionally blank
			}

			node(T val, node * prev, node * next) : mData(val), mNext(next), mPrev(prev)
			{
				// Intentionally blank
			}
		};

		/// This is the pointer to the first node in the linked list (NULL if the list is empty)
		node * mStart;

		/// This is the pointer to the last node in the linked list (NULL if the list is empty)
		node * mEnd;

		/// The number of elements in the list
		unsigned int mSize;

	public:
		/// The default constructor
		LinkedList() : mSize(0), mStart(NULL), mEnd(NULL)
		{
			// Intentionally blank
		}


		/// Copy constructor.  Makes a deep copy of the given LinkedList
		LinkedList(const LinkedList& L) : mStart(NULL), mEnd(NULL), mSize(0)
		{
			LinkedListIterator it = L.begin();
			while (it != L.end())
			{
				push_back(*it);
				++it;
			}
		}

		/// Destructor
		~LinkedList()
		{
			// Very important -- we have to clean up all our memory!
			clear();
		}


		/// Gets an element at the given "position".  Note: since LinkedList's don't support
		/// random-access (unlike ArrayList), this is a costly operation
		T& operator[](int index) const
		{
			if (index < 0 || index >= (int)mSize)
				throw std::out_of_range("Invalid index");
			node* cur = mStart;
			for (int i = 0; i <= index; i++)
			{
				if (i == index)
					return cur->mData;
				cur = cur->mNext;
			}
			// We should ever get here, but if we do, it means something's wrong with our mSize
			throw std::out_of_range("Invalid index");
		}


		/// Replaces this linked list with a copy of the data in the other LinkedList.  This *should* work
		/// even if the (silly) user assigns a LinkedList to itself
		LinkedList& operator=(const LinkedList& L)
		{
			if (&L != this)
			{
				clear();
				for (T val : L)
					push_back(val);
			}

			// Return a reference to ourself
			return *this;
		}


		/// Resets the linked list back to its original state
		void clear()
		{
			node* temp = mStart;
			while (temp != NULL)
			{
				// We need this because after we delete temp, the memory isn't ours anymore!
				node* next = temp->mNext;

				// Delete the current node
				delete temp;

				// Advance to the next node (if any) using the saved pointer.
				temp = next;
			}

			// Reset all of our attributes
			mStart = mEnd = NULL;
			mSize = 0;
		}


		/// Finds the first occurrence of the given value starting at the given "index"
		/// Since we can't do random-access, there's some extra overhead with this method
		/// (compared to ArrayList) to get to that initial spot
		int find(T val, int start_index = 0) const
		{
			node* cur = mStart;
			for (int i = 0; i < start_index; i++)
				cur = cur->mNext;
			for (int i = start_index; i < (int)mSize; i++)
			{
				if (cur->mData == val)
					return i;
				cur = cur->mNext;
			}
			return -1;
		}


		/// Inserts the given value at the currently occupied spot.  There's some extra overhead
		/// here to get to the given spot
		void insert(const T& item, int index)
		{
			if (index == 0)
				push_front(item);
			else if (index == mSize)
				push_back(item);
			else if (index < 0 || index > (int)mSize)
				throw std::out_of_range("Invalid index");
			else
			{
				// Get to the node at spot "index"
				node* cur = mStart;
				for (int i = 0; i < index; i++)
					cur = cur->mNext;

				// Because of our initial checks, we can be sure that this node will be between two 
				// existing nodes
				node* new_node = new node(item);
				new_node->mPrev = cur->mPrev;
				new_node->mNext = cur;
				cur->mPrev->mNext = new_node;
				cur->mPrev = new_node;

				// Increase our size
				mSize++;
			}
		}


		/// Adds a new node containing this data to the end of the linked list
		void push_back(T val)
		{
			if (mStart == NULL)
			{
				// Case I: This is the first node.  start and end will both point towards it
				mStart = mEnd = new node(val);
			}
			else
			{
				// Case II -- we already have a head -- add the new node to the end
				node * new_node = new node(val);
				new_node->mPrev = mEnd;
				mEnd->mNext = new_node;
				mEnd = new_node;
			}
			mSize++;
		}

		/// Adds a new node containing this data to the beginning of the linked list
		void push_front(T val)
		{
			if (mStart == NULL)
			{
				// Case I: This is the first node.  start and end will both point towards it
				mStart = mEnd = new node(val);
			}
			else
			{
				// Case II -- we already have a head -- add the new node before it
				node * new_node = new node(val);
				new_node->mNext = mStart;
				mStart->mPrev = new_node;
				mStart = new_node;
			}
			mSize++;
		}


		/// Removes the node at the given "position".  Getting to that position is costly
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


		/// Gets the number of elements in the linked list.  Don't implement it this way, but interesting
		/// challenge: how would you get the size of a linked-list if you weren't storing our mSize int?
		int size() const
		{
			return mSize;
		}

	public:
		/// The iterator used to traverse our linked list
		class LinkedListIterator
		{
		protected:
			/// The node we're currently at in our traversal
			node * mCurrent;

			/// Are we going forward or bacwards?
			bool mForward;

		public:
			/// Constructor that sets the current node to either the beginning (if is_forward is true) or end (if not)
			LinkedListIterator(const LinkedList& L, bool is_forward) : mForward(is_forward)
			{
				if (is_forward)
					mCurrent = L.mStart;
				else
					mCurrent = L.mEnd;
			}
			
			/// Constructor that's meant to be called internally that sets the current node to NULL
			LinkedListIterator() : mForward(true), mCurrent(NULL)
			{
				// intentionally empty
			}

		
			/// Advances the iterator.  Note this goes in the direction of mForward (so if mForward is false, this
			/// actually goes to the previous node in the list).
			void operator++()
			{
				if (mForward)
					mCurrent = mCurrent->mNext;
				else
					mCurrent = mCurrent->mPrev;
			}


			/// Is this iterator equal to the given one?
			bool operator==(const LinkedListIterator& it)
			{
				// Note: No need to check that the list is the same -- each list has its
				// own nodes, so we couldn't have the same node* but a different list
				return mCurrent == it.mCurrent;
			}


			/// Is this iterator not equal to the given one?
			bool operator!=(const LinkedListIterator& it)
			{
				return mCurrent != it.mCurrent;
			}

			/// Gets a reference to the data held by the current node.
			T& operator*()
			{
				return mCurrent->mData;
			}
		};

		/// Returns an iterator to the beginning of the list
		LinkedListIterator begin() const
		{
			return LinkedListIterator(*this, true);
		}


		/// Returns a reverse iterator starting at the end of the list.
		LinkedListIterator rbegin() const
		{
			return LinkedListIterator(*this, false);
		}

		/// Returns a "sentinel" value -- if an iterator is equal to this, we're done traversing
		LinkedListIterator end() const
		{
			return LinkedListIterator();
		}
	};


	





	/// Stream operator definition for our linked list class
	template<class T>
	std::ostream& operator<<(std::ostream& os, const LinkedList<T>& L)
	{
		os << "[";
		int i = 0;
		for (T val : L)
		{
			os << val;
			i++;
			if (i < L.size())
				os << ", ";
		}
		os << "]";
		return os;
	}
}