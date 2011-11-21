/***********************************************************
 
 Name: Abdelrahman Kamel
 
 Filename: String.cpp
 
 Date: February 9, 2009
 
 Description: This file contains the implementation of all 
 the member functions for class String. Class string was 
 declared in a seperate file called String.h

 Implementation: All these member functions where implemented
 for the success of the main program found in String_test.cpp. 

 ***********************************************************/

#include "String.h"
#include <iostream>
#include <cassert>

using namespace std; 

String::String()
{
	buffer = 0; 
	size = 0;
}//default constructor

String::String(const char * q)
{
	buffer =0;
	size = 0;

	for(int i=0;q[i];i++)
	size++;	

	char * newBuff = new char[size];

	copy(q,q+size,newBuff);

	buffer = newBuff;

}//string constructor

String::String(const String & aString)
{
	char * newBuff = new char[aString.size];
	
	copy(aString.buffer,aString.buffer+aString.size,newBuff);	
	
	buffer = newBuff;
	size = aString.size;
}//copy constructor

String::~String()
{
	delete [] buffer;
}

void String::operator+=(const char *a)
{
	int i=0, newSize=0, rSize=0;
		
	//finding the size of incoming string a
	for(int l=0; a[l]!='\0'; l++)
		rSize++;
	
	newSize=rSize+size;
	char * newBuffer = new char[newSize];
	
	for(;i<size;i++)
		newBuffer[i]=buffer[i];
	
	for(int b=0;b<rSize;b++,i++)
		newBuffer[i]= a[b];
	
	buffer = newBuffer;
	size = newSize;
	
}//operator+= overloading

String & String::operator*(int x)
{
	static String temp;

	for(int i=0; i < x; i++)
		temp += buffer;
		
	return temp; 
}

char & String::operator[](unsigned int index)
{
	return buffer[index];

}//operator[] overloading 

String String::operator=(String & rhString)
{
	char * newBuff = new char[rhString.size];

	for(int i =0; i < rhString.size; i++)
		newBuff[i] = rhString.buffer[i];

	buffer = newBuff;
	size = rhString.size;

return *this;
}//operator= overloading

String String::operator=(const char *rHand)
{
	size = 0;
	
	if(buffer[0]!='\0')
		delete [] buffer;
		
	for(int i=0;rHand[i];i++)
		size++;
	
	char * p = new char[size];

	copy(rHand,rHand+size,p);	
	
	buffer = p;
return *this;

}//operator = overloading in case of char string

int String::length()
{
	return size; 
}//length

bool String::operator==(String & rString)
{
	bool status;

	for(int i=0; i < rString.length(); i++)
	{
		if(buffer[i]==rString.buffer[i])
			status = true;
		else
		{
			status = false;
			break;
		}
	}

return status;
}//operator== overlaoding

bool String::operator==(const char *p)
{
	bool status;
	
	for(int k=0; k < size; k++)
	{
		if(buffer[k]==p[k])
			status = true;
		else{
			status= false;
			break;
			}
	}
	return status;
}// operator == overloading in case of char string
