/******************************************************
 
 Name: Abdelrahman Kamel
  
 Filename: String.h
 
 Date: February 9, 2009

 Description: This file contains all the prototypes that will be
 implemented in file String.cpp and used in String_test.cpp. 
 
*******************************************************/

#ifndef STRING_H
#define STRING_H

class String{
private:	
	char * buffer;
	int size;

public:
	String();
	String(const char *);
	String(const String & aString);
	~String();
	char & operator[] (unsigned int); 
	String operator= (String &);
	String & operator*(int);
	String operator= (const char *);
	void operator+= (const char *);
	int length();
	
	bool operator==(String &);
	bool operator==(const char *);
	
}; // String

#endif
