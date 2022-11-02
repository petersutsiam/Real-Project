#ifndef __LINKLIST_H
#define __LINKLIST_H

class linkedList{
	private:
		
		//node class
		class node{	
			public:
				vID val;
				node *next;
			//function
				node();
				node(vID x);
				node(vID x, node *p);
		};

		node *root;	 
		node *last;	// record the number of entries in the list
		UINT64 count;	// record the number of entries in the list	

		UINT64 find(vID value, UINT64 index, node *p);
		// Postcondition: Returns the first position at which the value v was found; otherwise returns -

		void clear(node *p);
		// Postcondition: The list is emptied
		
		
		void printIt(node *p, UINT64 index);
		// Postcondition: the list to be printed; for each line, print the index and the value at that index.

	public:
		//CONSTRUCTOR				
		linkedList();
		
		//DESTRUCTOR
		~linkedList();	
		
		//MODIFICATION MEMBERS FUNCTIONS
		void clear();	
		// Postcondition: The list is emptied
		
		void addLinkList(linkedList *list);
		// Postcondition: add a copy of a given linklist to the end of the current linklist

		void setLinkList(linkedList *list);
		// Postcondition: set the current list to given list
		// such that curr list root = given list root
		// curr list last = givne list last
		// given list root last == NULL

		UINT64 insert(vID value);	  
		// Postcondition: Returns the index into which it was inserted. Returns -1 if the list was full.

		void add(vID value);
		// Postcondition: Returns the index into which it was inserted. Returns -1 if the list was full.

		UINT64 insertAt(vID value, UINT64 index);
		// Postcondition: Returns the index into which it was inserted. Returns -1 if the list was full.

		void deleteAt(UINT64 index);
		// Precondition: the index must be within the pop value
		// Postcondition: Returns the index into which it was inserted. Returns -1 if the list was full.

		void deletePop();
		// Postcondition: Delete the index zero

		//CONSTANT MEMBER FUNCTIONS
		UINT64 countReturn();	
		// Postcondition: Returns the number of entries in the list
		
		UINT64 find(vID value);
		// Postcondition: Returns the first position at which the value v was found; otherwise returns -

		void printIt();
		// Postcondition: the list to be printed; for each line, print the index and the value at that index.

		vID readAt(UINT64 index);
		// Postcondition: Return the vID of a given index
};

class range{
	
	public:
		UINT64 low;
		UINT64 high;
		range();
};
#endif