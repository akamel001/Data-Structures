/*************************************************************

     Name: Abdelrahman Kamel

     Date: March 19, 2009

     Filename: Priority_queue.h

     Description: This file contains the class structure
	  of priority queue and its member functions. The 
	  implementation of the member functions are also provided
	  in this file.

     Implementation: The implementation was done by using a
	  vector but manipulating it in such a way it represents
	  a binary tree. Each element in the vector would then 
	  represent a child or parent of the tree. To go to any parent
	  or child we would have to use the following equations: 
	  pa = (pos -1) /2,  child = (position*2) + 1

**************************************************************/ 

#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

// Priority_queue.h  -- a priority_queue implemented as a heap

#include <vector>
#include <algorithm>

using namespace std;

template <class T> 
class Priority_queue {
public:
   Priority_queue() : c() { }
   bool empty() { return c.empty(); }
   unsigned int size() { return c.size(); }
   void push(const T & x);
   void pop(); 
   T & top() { return c.front(); }
private:
   vector<T> c;
};

template <class T>
void Priority_queue<T>::push(const T &x)
{
	c.push_back(x);

	unsigned int position = ( c.end() - c.begin() ) - 1;
	unsigned int parent = (position-1)/2;

	while(position > 0 && c[position] > c[parent])
	{
		swap(c[position], c[parent]);
		position = parent;
		parent = (position -1)/2;
	}

}

template <class T>
void Priority_queue<T>::pop()
{
	unsigned int lastPosition = (c.end() - c.begin()) -1;
	unsigned int position = 0;

	swap(c[0], c[lastPosition]);

	while(position < lastPosition)
	{
		unsigned int childPos = position*2+1;

		if(childPos < lastPosition)
		{
			if((childPos+1) < lastPosition && c[childPos+1] > c[childPos])
				childPos++;

			if(c[position] > c[childPos])
				break;	
			else
				swap(c[position],c[childPos]);
		}
		position = childPos;
	}
	c.pop_back();	

}

// your code goes here ...

#endif

