/**************************************************
 
 Name: Abdelrahman Kamel

 Filename: String_test.cpp

 Date: February 9, 2009

 Description: This file tests the success of the member
 functions found in String.cpp. If any of the test conditions
 fail the program quits. There are a total of 6 overloaded 
 operators and 3 constructors that are being tested. 

 Implementation: 
 
**************************************************/
#include <iostream>
#include <cassert>
#include "String.h"

using namespace std;

int main()
{
   String s1; // s1 == ""
   assert(s1.length() == 0);

   String s2("hi");  // s2 == "hi"
   assert(s2.length() == 2);

   String s3(s2);  // s3 == "hi"
   assert(s3.length() == 2);
   assert(s3[0] == 'h');
   assert(s3[1] == 'i');
   s1 = s2;  // s1 == "hi"
	assert(s1[1] == 'i');	
   assert(s1 == s2);
   
	s3 = "bye";  // s3 == "bye"
   assert(s3.length() == 3);
   assert(s3[0] == 'b');
   assert(s3[1] == 'y');
   assert(s3[2] == 'e');
   
	s1 += "re";  // s1 == "hire"
   assert(s1 == "hire");

   s1 += "d"; // s1 == "hired"
   assert(!(s1 == "hire"));

	String s4;

	s4 = s2 * 3;
	assert(s4 == "hihihi");

   cout << "SUCCESS" << endl;

return 0;
}
