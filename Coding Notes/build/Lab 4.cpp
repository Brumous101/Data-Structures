node* cur = llist.mstart; //it != llist.end()
while (cur != NULL)
{
	cout << node-> mData;
	cur= cur -> mNext
}

template <class T>
class LinkedList
{
	//node class
	//LList attr
	//LList methods
	//LLIter class
	//begin and rbegin
};
	//stream

//Section is over LLiter Class
class LinkedListIterator
{
	protected:
		node* mCur;
		LinkedList& mList;// Not needed because of how we traverse the while loop above (it'll fall off the array anyway)
		//Need to make a boolean to know which direction we are going in the linked list
		bool mForward
	public:
		LinkedListIterator(const LinkiedList& L, ) :mList(L)
		{
			if (!fwd)
				mCur = L.mEnd;
			else
				mCur = L.mStart;
			mForward = fwd;
		}
		LinkedListIterator() { mCur == NULL; }
};
//begin and end
ListedListIterator begin()
{
	return LinkedListIterator(*this, true);
}
ListedListIterator end()
{
	return LinkedListIterator();
}