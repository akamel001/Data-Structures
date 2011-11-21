/********************************************************

  Name: Abdelrahman Kamel 

  Date: March 03, 2009

  Filename: Queue_test.cpp

  Description: This file tests the correctness of member
  functions found in class Queue. If any of the member 
	functions fail to work as expected the program crashes.

  Implementation: Using the assert function to test what 
	we expect returned. 

*********************************************************/

 
#include <iostream>
#include <cassert>
#include "Queue.h"
#include "../lab3/String.h"
#include "../lab5/List.h"

using namespace std;

main()
{
	//cannot create a queue of vector because class vector
	//does not have a push_front member function
	//Queue<int, Vector> q1;
	Queue<int, List> q1;
	assert(q1.size() == 0);
	assert(q1.empty());

	q1.push(3); //que contains 3
	assert(q1.size() == 1);
	assert(q1.front() == 3);

	q1.pop(); //que contains nothing
	assert(q1.size() == 0);
	
	q1.push(9);  //queue 9
	q1.push(7);  //queue 9,7
	q1.push(18); //queue 9,7,18
	q1.push(13); //queue 9,7,18,13

	assert(q1.size() == 4);
	assert(q1.front() == 9);
	assert(q1.back() == 13);	
	
	Queue<String, List> q2;
	q2.push("this");
	q2.push("is");
	q2.push("a");
	q2.push("test");
	q2.push("string.");

	assert(q2.size() == 5);
	assert(q2.front() == "this");
	q2.pop();
	assert(q2.front() == "is");
	assert(q2.back() == "string.");	

	cout << "SUCCESS" << endl;
}
