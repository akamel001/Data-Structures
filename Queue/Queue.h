/*******************************************************

  Name: Abdelrahman Kamel

  Date: March 03, 2009

  Filename: Queue.h

  Description: This file contains the protype member functions
  of class Queue. This class is suppost to simulate FIFO data
  structure. 

  Implementation: Using a list to implement a Queue.
  We also use the lists member functions to simulate
  the Queue. 

*********************************************************/ 


#ifndef QUEUE_H
#define QUEUE_H

#include "../lab5/List.h"

using namespace std;

template <class T, template <class T> class Container = List> 
class Queue
{
	public:
		//no need for a constructor or destructor since the container has them already

	bool empty() const { return container.empty(); }
	unsigned int size() const { return container.size(); }
	void push(const T & x) { container.push_back(x); }
	void pop() { container.pop_front(); }
	T & front() { return container.front(); }
	T & back() { return container.back(); }

	private:
		Container<T> container;
};

#endif
