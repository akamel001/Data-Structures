/*******************************************************

  Name: Abdelrahman Kamel

  Date: March 03, 2009

  Filename: Stack.h

  Description: This file contains the protype member functions
  of class Stack. This class is suppost to simulate LIFO data
  structure. 

  Implementation: Using a list to implement a stack of diffrent
  data types. We also use the lists member functions to simulate
  a stack.

*********************************************************/ 

#ifndef STACK_H
#define STACK_H

// Stack.h  -- a stack implemented as an adapter (of vector or list or ...)

#include "../lab5/List.h"

using namespace std;

template <class T, template <class T> class Container = List>
class Stack
{
public:
   //We don't need a constructor or destructor because the Container has/should have one
   //Stack(): container() { }
   //~Stack() { ~container(); }
   bool empty() const { return container.empty(); }
   unsigned int size() const {return container.size();}
   void push(const T & x) { container.push_back(x); }
   void pop() {container.pop_back();}
   T & top() {container.back();}

private:
   Container<T> container;
};

#endif
