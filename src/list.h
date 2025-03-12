#ifndef LIST_H
#define LIST_H
/*
                                  ,-._.-._.-._.-._.-.
                                  `-.             ,-'
  .----------------------.          |             |
 | Author:                |         |             |
 |     Sam Allmon         |         |             |
 | Assignment:            |         |             |
 |     Linked List        |        ,';".________.-.
 | Description:           |        ;';_'         )]
 |     Create a doubly    |       ;             `-|
 | Linked list and all    `.       `T-            |
 | Its member function-y  _ \       |             |
 | Goodness.              |`-;      |             |
 |                        |         |..________..-|
 | Due:                   |        /\/ |________..|
 |     04.06.10           |   ,'`./  >,(           |
 | Date Created:          |   \_.-|_/,-/   ii  |   |
 |     04.05.10           |    `."' `-/  .-"""||    |
 | Date Modified:         |     /`^"-;   |    ||____|
 |     04.06.10           |    /     /   `.__/  | ||
 \_______________________/          /           | ||
                                                | ||
 
 
*/

/*
Author                 :: Mark Duncan
Assignment Title       :: Templated Double Linked List
Assignment Description :: Create a Templated Double Linked List
						  that will hold any data type.
Due Date               :: 4/6/2010
Date Created           :: 3/29/2010
Date Last Modified     :: 4/3/2010

Data Abstraction: 
 	-Creates a single default node object that points to null and contains a
	 back and next pointer for convenience, as well as data of some type T.
		
Output:	
	-The list can be outputted using the [] operator for a single element or the 
	front or back functions for those respective values.

Input: 
	-Requires a list object to be declared of templated type <T>.
	-Values can be added to the list using the "push" functions or removed using
	the "pop" functions

Implementation:
	-The steps for setting up and utilizing the list class are as follows.
	Create a list object of type <datatype> (templated), and then add values
	to that list using pop or remove using push. The lists can then be erased,
	item in list referenced by [x], where x is the item in the list, or set equal to
	each other using the assignment operator = . The number of elements can also be 
	returned using getSize, or boolean tested to see if they are epty or not using
	isEmpty. An insert implementation to insert an element into the middle of a list
	is included but has been commented out.

Assumptions:
	-The user knows how to initialize a templated object.
*/




#include <memory> //Included here because it is included in the container file
#include <iostream>
#include "containerInterface.h"

using namespace std;


/*
Description of structure :: Creates a node that is linkable to other nodes.
						    The node holds some type of data and is able to know
						    where its next node is and where it's previous one
						    is using pointers. The pointers "next" and "back" are 
							NULL by default.
Precondition			:: None
Postcondition			:: A node will be created with default NULL values and 
						   datatype T.
Return type				:: Structure type T (templated)
*/
template<class T>
struct node
{
	T data;
	node<T> *next;
	node<T> *back;
	node(T e)
	{
		data = e;
		next = NULL;
		back = NULL;
	}
};

/*
Description of class :: The list class creates a templated double
                        linkable list object using node structures and allows for
						operations to be performed on the linked list 
						such as popping and pushing the list, returning
						the size of the list, testing the list if it is empty
						or not, and retrieving values from the list using
						the [] operator, or the "front" and "back" functions.
						The list can also be erased using "erase" or set equal 
						to another list object properly using the = operator.
Precondition			:: The node structure must exist, and in this case, the 
						   containerInterface container.
Postcondition			:: List object will be created of specified type T.
Return type				:: Class object type T
*/
template<class T>
class list:public containerInterface<T>
{
	public:
		list();
		virtual ~list();
		list(const list&);
		list<T>& pushFront(T);
		list<T>& pushBack(T);
		list<T>& popFront(T&)	throw(BADINDEX);
		list<T>& popBack(T&)	throw(BADINDEX);
		//list<T>& insert(int n);
		int  getSize();
		void remove(int) throw(BADINDEX);
		bool isEmpty();
		T  front()			throw(BADINDEX);
		T  back()			throw(BADINDEX);
		T& operator [](int)	throw(BADINDEX);
        void erase();
		list<T>& operator = (list&);
	private:
		void kill(node<T>*);
		node<T> *head;
};




/********Begin Definitions*******/

/*
Description of function :: Constructor; sets the node type T pointer 
						   head equal to NULL by default.
Precondition			:: A list object must exist
Postcondition			:: Head is NULL
Return type				:: None, constructor
*/
template<class T>
list<T>::list()
{
	head = NULL;
}


/*
Description of function :: Class copy constructor; creates a copy
						   of the list from an existing list object.
Precondition			:: Another list object must exist to copy
Postcondition			:: The new list will equal the passed in list
						   by reference &a.
Return type				:: None, copy constructor
*/
template<class T>
list<T>::list(const list<T> &a)
{
	head = NULL;
	node<T>* p = a.head;
	while(p)
	{
		pushBack(p->data);
		p = p->next;
	}
}

//destructor using recursive solution
/*
Description of function :: Destructor; calls the kill function
						   to dereference and delete the list
						   recursively.
Precondition			:: The kill function must exist
Postcondition			:: The list will be empty and dereferenced
Return type				:: None, destructor
*/
template<class T>
list<T>::~list()
{
	kill(head);
}

//private function kill to delete all nodes
/*
Description of function :: Private function kill; can only be accessed
						   from within the class. Sets all the pointers
						   to NULL recursively, which creates a blank list
						   (essentially erases the list.)
Precondition			:: A list object with data must exist
Postcondition			:: The list will point to NULL and the pointers
						   will be deleted.
Return type				:: Void
*/
template<class T>
void list<T>::kill(node<T>* p)
{
	if(p == NULL) //recursive base case
		return;
	kill(p->next);
	delete p;
}

//erase function
/*
Description of function :: Erase will deallocated the list using
						   the kill function and set head to NULL.
Precondition			:: A list must exist and the kill function must
						   exist
Postcondition			:: The list will be deallocated and head is NULL
Return type				:: Void
*/
template<class T>
void list<T>::erase()
{
	kill(head);
	head = NULL;
}


/*
Description of function :: The overloaded assignment operator;
						   will assign an existing list the values
						   of another existing list while retaining
						   its distinct address using the
						   = operator.
Precondition			:: Two list object must exist a and b, such that
						   a != b (a is not b).
Postcondition			:: The list left of the operand will be equal to the 
						   list passed by reference &a.
Return type				:: List object type T by reference (allows for chaining).
*/
template<class T>
list<T>& list<T> :: operator = (list<T> &a)
{
	if(this != &a) //if it is not itself
	{
		kill(head);
		head = NULL;

		node<T>* p = a.head;

		while(p)
		{
			pushBack(p->data);
			p = p->next;
		}
	}

	return *this;
}


/*
Description of function :: [] operator; allows for a value within
						   the list to be retrieved using [x] such that x is
						   the desired element in the list.
Precondition			:: A list object with data must exist.
Postcondition			:: The function will return the desired address from the
						   list for array type behavior.
Return type				:: T& where T is the templated datatype
*/
template<class T>
T& list<T>:: operator [] (int n) throw(BADINDEX)
{ 
	node<T>* p = head;

	if(n < 0 || n >= getSize())
	{
		throw BADINDEX();
	}

		while(n > 0)
		{
			p = p->next;
			n--;
		}

	return p->data;
}

//push front function
/*
Description of function :: pushFront; will store data element 
						   nnode in a New node and add the Node to the front
						   of the list
Precondition			:: A list object must exist
Postcondition			:: A new node will be added to the front
	                       of the list with data.
Return type				:: A list<T> by reference, self (for chaining).
*/
template<class T>
list<T>& list<T>::pushFront(T nnode)
{
	node<T>* p = new node<T>(nnode);
	p->next = head;
	head = p;
	p->next->back = p;

	return *this;
}

/*
Description of function :: pushBack; Will store data element d
						   in a New node and add the Node to the end
						   of the list.
Precondition			:: A list object exists
Postcondition			:: A new node will be added to the back of the list
Return type				:: A list type T by reference, self (for chaining.)
*/
template<class T>
list<T>& list<T>::pushBack(T d)
{
	node<T>* p = new node<T>(d);

	if (head == NULL) //case if head is NULL
		head = p;

	else if(head->next==NULL) // case if there is one element
	{
		head->next = p;
		p->back = head->next;
	}
	else // case with multiple elements
	{
		node<T>* pp= head->next;
		while(pp->next)
		{
			pp = pp->next;
		}

		pp->next = p;
		p->back = pp;
	}

	return *this;
}



/*
Description of function :: popFront; removes a Node from the front
						   of the list
Precondition			:: A list object must exist
Postcondition			:: A node will be removed from the front of the list
						   pointed to be the head error: if the list is empty
						   throw a BADINDEX exception.
Return type				:: A list<T> by reference, self.
*/
template<class T>
list<T>& list<T> :: popFront(T& r)	throw(BADINDEX)
{
	if(head)
	{
		node<T>* temp = head;
		r = head->data;//store value by reference for later
		head = head->next;
		delete temp;
	}

	else if(isEmpty()) // if there are no elements
	{
		throw BADINDEX();
	}

	return *this;
}



/*
Description of function :: popBack; removes a Node from the end
							of the list
Precondition			:: A list object must exist
Postcondition			:: A node will be removed from the back of
						   linked list pointed to by head error:
						   if the list is empty, throw a BADINDEX exception.
Return type				:: Integer
*/
template<class T>
list<T>& list<T>::popBack(T& r)	throw(BADINDEX)
{
	node<T>* p = head;
	
	if (isEmpty()) // if there are no elements
	{
		throw BADINDEX();
	}

	else if(head)
	{
		if(head->next == NULL)
		{
			head = NULL;
			r = p->data; //return current position's data
			delete p;
		}
		else
		{
			while(p->next->next)
			{
				p = p->next;
			}

			r = p->next->data; // return the data of the position you are about to delete

			delete p->next;
			p->next = NULL;
		}
	}

	return *this;
}

/*insert function
template <class T>
list<T>& list<T>::insert(int n)
{
	node<T>* p = head;
	if(head == NULL || n < head->data )
		pushFront(n);
	else
	{
		while(p->next && n > p->data)
		{
			p = p->next;
		}

		if(n < p->data)
		{
			node<T>* newNode = new node(n);
			newNode->next = p;
			newNode->back = p->back;
			p->back = newNode;
			newNode->back->next=newNode;
		}
		else
		{
			pushBack(n);
		}
	}

	return *this;
}
*/

/*
Description of function :: Returns the current number of nodes in the
						   the linked list
Precondition			:: A list object exists
Postcondition			:: The list is unchanged
Return type				:: Integer representing the number of elements
						   in the list.
*/
template<class T>
int list<T>:: getSize()
{ 
	int n = 0;
	node<T>* p = head;

	if(p == NULL) // no elements exist
		return 0;
	else
	{ 
		n = 1; //at this point, at least one node exists.
		while(p->next)
		{
			p = p->next;
			n++; //increment for each additional value in the list
		}
	}

	return n;
}


/*
Description of function :: Tests to see if the node is empty or not
						   (has values or is NULL)
Precondition			:: A list object must exist
Postcondition			:: The list is unchanged
Return type				::Returns true if the list is empty, otherwise false
*/
template<class T>
bool list<T>::isEmpty()
{
	if(head == NULL) // if head is NULL, then the list is empty
		return true;
	else
		return false;
}


/*
Description of function ::Returns a copy of the first data item in
						  the linked list
Precondition			:: A linked list object must exist
Postcondition			:: The list is unchanged
Return type				:: Returns a copy T 
*/
template<class T>
T list<T>::  front()	throw(BADINDEX)
{

	//if the list is empty
	if(isEmpty())
		throw BADINDEX();
	else
	{
		return head->data;
	}

}


/*
Description of function :: Returns a copy of the last item
						   in the linked list
Precondition			:: A list object must exist
Postcondition			:: The list is unchanged
Return type				:: Returns a copy T
*/
template<class T>
T list<T>::  back()	throw(BADINDEX)
{
	node<T>* p = head;

	//if the list is empty
	if(isEmpty())
		throw BADINDEX();
	else
	{
		while (p->next) // chain to the end of the list
		{
			p = p->next;
		}
	}

	return p->data;
}

template <class T>
void list<T>::remove(int index)
{
	if(isEmpty() || index < 0 || index > size()) throw BADINDEX();
	node<T>* p = head;

	if(index == 0)
	{
		if(p->next)
		{
			head = p->next;
		}
		else
		{
			head = NULL;
		}
		delete p;
	}
	else if(index == 1)
	{
		p = head->next;
		p->next->back = p->back;
		delete p;
	}
	else if(index == size()-1)
	{
		while(p->next)
		{
			p=p->next;
		}
		p->back->next = NULL;
		delete p;
	}
	else
	{
		for(int i = 0; i < index; i++)
		{
			p = p->next;
		}

 		p->back->next =p->next;
		p->next->back = p->back;
		delete p;
	}
	
}

#endif