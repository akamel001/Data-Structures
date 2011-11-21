/********************************************************************
 *
 *  Name: Abdelrahman Kamel
 *
 *  Date:February 27, 2009
 *
 *  Filename: List.h
 *
 *  Description: This file contains the implementation of
 *  a list class, link class, and list_iterator class. All
 *  three clases and member functions are implemented in this
 *  file. 
 *
 *	 Implementation: The list class was implemented with the help of
 *  3 constructors, and 12 member functions. However the link class
 *  was implemented with 1 constructor and 2 friend functions. The
 *  list_iterator class has 8 member functions and 3 constructors. 
 *  These classes utilize the operator -> in the implementation of
 *  its member functions. 
 *
 *******************************************************************/

#ifndef LIST_H
#define LIST_H

// List.h - a doubly-linked list

#include <algorithm>
using namespace std;

// forward declaration of classes defined in this header
template <class T> class List;
template <class T> class Link;
template <class T> class List_iterator;

template <class T> 
class List
{
public:
   typedef List_iterator<T> iterator;

   List();
   List(const List & l);
   ~List();

   bool empty() const {return first_link == 0;} 
   unsigned int size() const; 
   T & back() const {return last_link -> value;}
   T & front() const {return first_link -> value;}
   void push_front(const T & x);
   void push_back(const T & x);
   void pop_front();
   void pop_back();
   iterator begin() const {return iterator(first_link);} 
   iterator end() const {return iterator(last_link -> next_link);}
	void add(const iterator & pos, const List<T> & newList);   
	void insert(iterator pos, const T & x); // insert x before pos
   void erase(iterator & pos);             // pos must be valid after erase() returns

private:
   Link<T> * first_link;
   Link<T> * last_link;
   unsigned int my_size;
};//class list

/*******************************************************************
 *
 * Discription: This function takes as its a list as its explicit 
 * perameter and a pointer to a link position. Then the function
 * procedes to add the explicit list to the implicit list at the 
 * pointer position. 
 *
 * Implementation: This function was implemented using the List
 * copy constructor. Once a copy of the explicit list is made,
 * then we modify the next_link and prev_link accordingly.
 * After we make the modifications then we update the list size.
 * 
 * Time complexity: The time coplexity of this function is O(1)
 *
 *******************************************************************/
template <class T>
void List<T>::add(const iterator & pos, const List<T> & newList)
{
	//modified on march 24, 2009: added static to tempList
	//static creates tempList and distroys it at the end of main scope not this scope
	static List<T> tempList = newList;
	Link<T> * current = pos.current_link;
	Link<T> * pos_right_link = current -> next_link;

	current -> next_link = tempList.first_link;
	tempList.first_link -> prev_link = current;
	
	if( pos_right_link != 0)
	{
		pos_right_link -> prev_link = tempList.last_link;
		tempList.last_link -> next_link = pos_right_link;
	}
	
	if(pos == last_link)
		last_link = newList.last_link;	
	
	my_size += tempList.my_size;	
}

template <class T>
List<T>::List()
{
        first_link = 0;
        last_link = 0;
        my_size = 0;
}//list constructor

template <class T>
void List<T>::erase(iterator & pos)
{
	Link<T> * current = pos.current_link;
	
	Link<T> * left = current -> prev_link; 
	Link<T> * right = current -> next_link;
	
	if(left == 0 && right == 0)
	{
		first_link = 0;
		last_link =0;
		my_size =0;
		delete current;
		return;
	}
	
	if(left == 0)	
	{
		right -> prev_link =0;
		first_link = right;
	}	

	if(right == 0)
	{
		left -> next_link = 0;
		last_link = left;
	}	

	if( left != 0 && right != 0)
	{
		left -> next_link = right;
		right -> prev_link = left;
	}

	delete current;
	--my_size;		
}//erase

template <class T>
void List<T>::pop_front()
{
	Link<T> * temp_first_link = first_link;

	first_link = first_link -> next_link;
	
	if( first_link != 0)
		first_link -> prev_link = 0;
	else
		last_link = 0;

	delete temp_first_link; 

	--my_size;
}//pop_front

template <class T>
void List<T>::pop_back()
{
	Link<T> * temp_last_link = last_link;
	
	last_link = last_link -> prev_link;

	if(last_link != 0 )
		last_link -> next_link = 0;
	else
	{
		first_link = 0;
	}
	delete temp_last_link;

	--my_size;
}//pop_back

template <class T>
int unsigned List<T>::size() const 
{
	int elements=0;
	Link<T> * ptr = first_link;
		
	for(;ptr;ptr=ptr->next_link)
		elements++;
	
		return elements;	
}//size

template <class T>
List<T>::List(const List & l)
{
        first_link = 0;
        last_link = 0;
        my_size = 0;
        
	for (Link<T> * current = l.first_link; current != 0; current = current -> next_link)
                push_back(current -> value);
}//list copy constructor

template <class T>
List<T>::~List()
{
	Link<T> * newFirst = first_link;
	Link<T> * next;
	
	while(newFirst != 0)
	{	
		next = newFirst -> next_link;
		delete newFirst;
		newFirst = next;
	}
}//list destructor

template <class T>
void List<T>::insert( iterator pos, const T & x)
{
	Link<T> * newLink = new Link<T>(x);
	Link<T> * current = pos.current_link;

	newLink -> next_link = current;
	newLink -> prev_link = current -> prev_link;
	current -> prev_link = newLink;
	
	current = newLink -> prev_link;

	if(current !=0)
		current -> next_link = newLink;
	else
		first_link = newLink;

	++my_size;
	
}//insert

template <class T>
void List<T>::push_back(const T & x)
{
	Link<T> * newLink = new Link<T>(x);
	
	if(first_link == 0)
		first_link = last_link = newLink;
	else
	{
		newLink -> next_link = 0;
		newLink -> prev_link = last_link;
		last_link -> next_link = newLink;
		last_link = newLink;
	}

	++my_size;	
}//push_back

template <class T>
void List<T>::push_front(const T & value)
{
	Link<T> * newLink = new Link<T>(value);
	
	if(first_link == 0)
		first_link = last_link = newLink;
	else
	{
		newLink -> next_link = first_link;
		first_link -> prev_link = newLink;
		first_link = newLink;
	}
	
	++my_size;	
}//push_front

template <class T> 
class Link 
{
private:
   Link(const T & x): value(x), next_link(0), prev_link(0) {}
   
	T value;     
   Link<T> * next_link;
   Link<T> * prev_link;

   friend class List<T>;
   friend class List_iterator<T>;
};//class link

template <class T> class List_iterator
{
public:
   typedef List_iterator<T> iterator;

   List_iterator(Link<T> * source_link): current_link(source_link) { }
   List_iterator(): current_link(0) { }
   List_iterator(List_iterator<T> * source_iterator): current_link(source_iterator.current_link) { }

   T & operator*(){return (*current_link).value;}  // dereferencing operator
   iterator & operator=(const iterator & rhs){ current_link = rhs.current_link; return *this;}
   bool operator==(const iterator & rhs) const {return current_link == rhs.current_link;}
   bool operator!=(const iterator & rhs) const {return current_link != rhs.current_link;}
   iterator & operator++();  // pre-increment, ex. ++it
   iterator operator++(int); // post-increment, ex. it++
   iterator & operator--();  // pre-decrement
   iterator operator--(int); // post-decrement

protected:
   Link<T> * current_link;

   friend class List<T>;
};//class List_iterator

template <class T>
List_iterator<T> & List_iterator<T>::operator--()
{
	current_link = current_link -> prev_link;
	return *this;
}//pre-decrement operator-- 

template <class T>
List_iterator<T> List_iterator<T>::operator--(int)
{
	List_iterator<T> clone(*this);
	--(*this);
	return clone;
}//post-decrement operator-- 

template <class T>
List_iterator<T> & List_iterator<T>::operator++() // pre-increment
{
        current_link = current_link -> next_link;
        return *this;
}//pre-increment operator++

template <class T>
List_iterator<T>  List_iterator<T>::operator++(int) // post-increment
{
		List_iterator<T> copy(*this);
		++(*this);
		return copy;
}//post-increment operator++


#endif

