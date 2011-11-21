/*************************************************

	Name: Abdelrahman Kamel

	Date: 02/20/2009

	Filename: Vector.h

	Discription: This file contains the class and 
	member functions that are tested in the file 
	Vector_test.h. 
	
	Implementation:	Implementation was done by using some generic 
	algorithms to implement the member functions. The member functions 
	that where implemented are capacity(), size(), empty(), begin(), 
	end(), front(), back(), push_back(value), pop_back(), reserve(int),
	resize(int), operator[]. Some of the member functions where implemented
	during declaration. 

**************************************************/
#ifndef VECTOR_H
#define VECTOR_H
#include<algorithm>

using namespace std;

template <class T>
class Vector
{
public:

   	typedef T * iterator;

	Vector() {buffer=0; resize(0);}
	

   	Vector(unsigned int size) {buffer=0; resize(size);} 				
   	Vector(unsigned int size, const T & initial);
   
	//copy constructor	
   	Vector(const Vector<T> & v); 
   	~Vector() {delete [] buffer;}

	//return capacity of vector (in elements)
   	unsigned int capacity() const {return my_capacity;} 

	//return the number of elements in the vector	   
	unsigned int size() const {return my_size;}         				
   	bool empty() const {return my_size == 0;}

	//return an iterator pointing to the first element
   	iterator begin() {return buffer;}  

	//return an iterator pointing to one past the last element                   			
  	iterator end() {return (buffer + my_size);} 

	//return a reference to the first element         			
   	T & front() {return buffer[0];}       	
						
	// return a reference to the last element
   	T & back() {return buffer[my_size-1];}

	//add a new element
	void push_back(const T & value); 

	//remove the last element
	void pop_back() {my_size--;}   

	//adjust the capacity
	void reserve(unsigned int capacity); 
	
	//adjust the size
	void resize(unsigned int size){reserve(size); my_size=size;}

	void swap(Vector<T> &);
	
	void erase( iterator );
	void erase( iterator, iterator );
		
	//return refence to numbered element
   	T & operator[](unsigned int index) {return buffer[index];}
   	Vector<T> & operator=(const Vector<T> & rhV);

private:
   	unsigned int my_size;
   	unsigned int my_capacity;
   	T * buffer;
};//vector

template <class T> 
Vector<T>::Vector(unsigned int size, const T & initial)
{
	buffer=0;
	
	//sets my_size & my_capacity and creats a buffer with that size
	resize(size);	
	
	//using generic alg to fill in new buffer
	fill(begin(),end(),initial);

}//constructor

template <class T>
Vector<T>::Vector(const Vector<T> & v)
{
	buffer=0;
	resize(v.my_size);
	
	//creating a temp buffer to copy explicit vector into 
	T * newBuff = new T [my_capacity];

	
	for(int i=0; i < my_size; i++)
		newBuff[i] = v.buffer[i];
	
	buffer = newBuff;

}//copy constructor

/*===============================================================
	
	Discription: This function takes two pointsers as its 
	perameter. The function is then to use the to points to 
	erase all the elements from the first pointer to the 
	second pointer.

	Implementation: This function was implemented by creating
	a new buffer and coping all the elements from the start of
	the buffer to it. The loop breaks once the buffer's index 
	location is the same as the start position. Once they are the
	same, break the loop and copy the rest of the elements unconditionaly.  

	Time complexity: This function has a time complexity of O(n)

===============================================================*/
template <class T>
void Vector<T>::erase( iterator start, iterator end)
{
	int i,j;
	i=j=0;

	T *newBuff = new T [my_capacity];
	for(;;)
	{
		//copy from the start of the buffer till location start()
		//and break when 
		if(&buffer[j] != start)
			newBuff[i++]=buffer[j++];
		else
		{
			//else buffer location is equal to starting location
			//increment j and break the loop
			j++;
			break;
		}
	}

	//skipping all the elemnts that are to be erased
	while(start != end)
	{
		j++; 
		start++;
	}
	
	//copy the rest of the buffer unconditionally
	for(;j<my_size;)
		newBuff[i++]=buffer[j++];

	my_size = i;

	delete [] buffer;
	buffer = newBuff;
}

/*===================================================================
	
	Discription: This function takes a pointer as a perameter
	that is pointing to a position in the vector and erases it.
	
	Implementation: This function was implemented by creating a
	temp buffer and copying every element from the start of the 
	buffer until it hits the address of the input perameter (remove).
	Once the loop breaks, that is copying the values, another loop
	picks off where the first loop left and copies the rest of the
	elements unconditionaly.

	Time complexity: This function has a time complexity of O(n)

====================================================================*/
template <class T>
void Vector<T>::erase( iterator remove)
{
	int i=0,j=0;	
	T * newBuff = new T [my_capacity];

	//remove_copy(begin(),end(),newBuff, *(remove));
	
	for(; i< my_size;)
	{
		//copy the content of the buffer as long as the address
		//at position "i" does not equal the address of remove
		if(&buffer[i] != remove)
			newBuff[j++] = buffer[i++];
		else
		{
			//address match, increment index of buffer, skip the element 
			//and break the loop
			i++; 
			break;
		}	
	}
//this for loop picks off where the first loop left; at the stored 
//locations of i and j. Unconditionally copy the rest of the buffer
//into the new buffer
	for(; i < my_size;)
		newBuff[j++] = buffer[i++];
	
	my_size--;	

	delete [] buffer;
	buffer = newBuff;
}

/*======================================================================
	
	Discription: This function takes a vector of type T as perameter and
	swaps the content of the implicit perameter with it. 
		
	Implementation: Using a temp vctor of type T and *this pointer. This
	function is like a normal swap function, we set a temp vector to 
	store the implicit vector. Then we set the implicit vector to equal
	the equal the explicit vector and the explicit vector equal to temp.

	Time complexity: this function has a time complexity of O(1)
	
======================================================================*/

template <class T>
void Vector<T>::swap(Vector<T> & swapVector)
{

//creating a temp vector to store the content of the implicit perameter
	Vector<T> temp;

//setting temp equal to implicit perameter, i do this here instead because
//if i did this at deleration (Vector<T> temp=*this), the copy constructor 
//will get called instead of the overloaded operator=
	temp = *this;

	*this = swapVector;

	swapVector = temp;	
}

template <class T>
Vector<T> & Vector<T>::operator=(const Vector<T> & rhV)
{
	resize(rhV.my_size);
	
	/*Same as copy constructor create temp buffer to 
	  hold right hand vector */	
	T * newBuff = new T [my_capacity];
	
	for(int i=0; i < my_size; i++)
		newBuff[i] = rhV.buffer[i];

	buffer = newBuff;
	
	//used to chain equal
	return *this;

}//operator=

template <class T>
void Vector<T>::push_back(const T & value)
{
	//if the size is greater then allocate a buffer
	//that is size+10, used 10 in preperation for more
	//values to be pushed back
	if(my_size >= my_capacity)
		reserve(my_size+10);

	buffer[my_size++]=value;

}//push_back

template <class T>
void Vector<T>::reserve(unsigned int capacity)
{
	if(buffer ==0)
	{
		my_size=0;
		my_capacity=0;
	}
	//returns if there is no need to reserve
   if(capacity <= my_capacity)	
		return;
	
	T * newBuffer = new T [capacity];
	copy(begin(), end(), newBuffer);

	my_capacity = capacity;
	buffer = newBuffer;
}//reserve

#endif
