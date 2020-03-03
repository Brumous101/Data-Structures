//Name: Kyle Johnson
//Class: ETEC2101
//Section: 01
//Assignment: ADD THIS AS IT IS YOUR DEFAULT TEMPLATE AND NEEDS TO BE RENAMED
/*
	Iterators look gross because they are but the functionality is important.
	iterators are classes inside a class
	the .begin and the .end are a part of the #include vector
	If it's not here go to the next thing in the list. If it's not here go to the next thing in the list.

	Now talking about the prettier interface to iterators:

	for (string s : slist)
		cout << s << endl;

	Is very similar to the for each loop in python

	std::string temp = *cur this will change it at that address 
	
	======================================================Looking at first half of Lab 3==============================================================
	//main.cpp
	ssuds::ArrayList<string>slist;
	{

	}
	ssuds::ArrayList<string>::ArrayListIterator cur = slist.begin();
	while(cur != slist.end())
	{
		cout << *cur << endl;
		++cur;
	}
	//We are building this on top of Lab 2
	public:
		void push_back(T val)
		{
			...
		}
		class ArrayListIterator
		{
			protected:
				ArrayList &mArray;
				int mPos;//The indexing variable
			public:
				ArrayListIterator(ArrayList &a, int p): mArray(a) //BUG: Can never have an ArrayList that never points at nothing. Won't initialize it? Use initializer list from lab 1. the :mArray(a) should fix it 
				{
					mArray = a;
					mPos = p;
				}
				bool operator != (ArrayListIterator & other)
				{
					return mPos != othermPos || &mArray != &other.mArray; //Make sure we are at the correct index
					//We also need to make sure it isn't the same array. We can do this by comparing addresses
				}
				bool operator ==(ArrayListIterator & other)
				{
					
				}
				T& operator * ()
				{
					return mArray[mPos];
				}
				void operator++()
				{
					return mPos++; //may not be a return
				}
		};
		ArrayListIterator begin()
		{
			return ArrayListIterator(*this, (the index number where we want to start));
		}
		ArrayListIterator end()
		{
			return ArrayListIterator(   );
		}

		======================================================Looking at second half of Lab 3=============================================================
		The pre processor does not even see the variable VAL. It will get replaced by the number 5 because VAL is not anything in c++.

		When it goes to the compiler, all of the main and b


			Preprocessor takes out all variables. 
			Compiler makes .obj files out of what is made from the preprocessor which will just be all machine code.
			The Linker will get addresses for all the obj files and uses them to construct an exe

			The difference between a program and a process is a process is a running version of the code.

		CHECK OUT THE PICS ON YOUR PHONE
		Renaming your default template folders, 
			open the .sln in notepad. Project -> rename to file type and there should be two tags
			open the vc.proj in notepad <ROOT NAME SPACE>
			Make sure to get the correct \\SMFL\\  for x64 or whatever bit you are using
			We are going to put the SMFL in the dependencies section of the project

*/