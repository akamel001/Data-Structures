/*******************************************************

     Name: Abdelrahman Kamel

     Date: March 19, 2009

     Filename: Priority_queue_test.cpp

     Description: This file tests the correctness of 
	  implemented member functions of class Priority_queue.

     Implementation: Using the assert function to test 
	  and see if all member functions return the expected
	  values. If one of the functions does not return the
	  expected value then the program crashes. 

*******************************************************/ 

// Priority_queue_test.cpp to test Priority_queue

#include <iostream>
#include <cassert>

#include "Priority_queue.h"

using namespace std;

int main()
{
   Priority_queue<int> pq;

   assert(pq.size() == 0);
   assert(pq.empty());

   pq.push(10);
   assert(pq.top() == 10);

   pq.push(20);
   assert(pq.top() == 20);

   pq.push(30);
   assert(pq.top() == 30);

   pq.push(40);
   assert(pq.top() == 40);

   pq.push(50);
   assert(pq.top() == 50);

   pq.push(5);
   assert(pq.top() == 50);

   pq.pop();
   assert(pq.top() == 40);

   pq.pop();
   assert(pq.top() == 30);

   pq.pop();
   assert(pq.top() == 20);

   pq.pop();
   assert(pq.top() == 10);

   pq.pop();
   assert(pq.top() == 5);

   pq.pop();
   assert(pq.size() == 0);

   Priority_queue<int> pq2;
   pq2.push(30);
   pq2.push(11);
   pq2.push(7);
   pq2.pop();
   assert(pq2.top() == 11);
   pq2.pop();
   assert(pq2.top() == 7);
   pq2.pop();
   assert(pq2.empty());

   cout << "All tests passed." << endl;
}

