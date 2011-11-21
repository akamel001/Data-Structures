/**-----------------*
Name: Abdelrahman Kamel
Date: 01/13/2009
File Name: lab1.cpp
Description: To translate from infix to postfix expressions, using an algorithm.
Implementation: Using an algorithm provided in lab. 
 **-----------------*/

#include <iostream>
#include <string>
#include <string.h>
#include <sstream>
#include <stack>

using namespace std;

int  prec(char);

int main(){

 cout << "Please Enter the operand or operator followed by a space (exp: ( a + b )): ";
string s1; 
getline(cin, s1);
stringstream iss(s1);
stack<char> stk;
 
while( getline(iss,s1,' ')){

char *cp = new char[s1.length()]; // a needed character pointer to be able to make the transision from string to characters to be used in the stack
strcpy(cp,s1.c_str());

	if (isalpha(*cp) || isdigit(*cp)) 
		cout << cp; 	
	else{
			if( *cp == '(')
				stk.push(*cp);
			else if( *cp == ')'){
					while(!stk.empty() && (stk.top() != '(')){
							cout << stk.top();
							stk.pop();}
					if(!stk.empty())
						stk.pop();
						}
			else if( stk.empty() || prec(stk.top()) < prec(*cp))
					stk.push(*cp);
			else if( prec(stk.top()) >= prec(*cp)){
					while(!stk.empty() && (prec(stk.top()) >= prec(*cp))){
							cout << stk.top();
							stk.pop();
					}stk.push(*cp);
				 }
		}

};//end main while loop

while(!stk.empty()){
	cout << stk.top();
	stk.pop();
}

 cout << endl;
return 0;
}//main

int prec(char a){
/*---------*
Description: This function takes a character from usually an operator and determins which has higher precedence, then returns a number.
Implementation: Using a classic case switch then returning a value based on what operator it is.
 *---------*/
	switch (a) {
	case '(': return 0;
	case '+': 
	case '-': return 1;
	case '*': 
	case '/': return 2;
	}
}//prec
