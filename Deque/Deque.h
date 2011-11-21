/*****************************************************************************
*	
*	Name: Abdelrahman Kamel
*	
*	Date: March 11, 2009
*	
*	Filename: Deque.h
*	
*	Discription: This file contains both, member functions 
*	and declarations for class Deque and DequeIterator.
*	
*	Implementation: This file was implemented to match the functions
*	found in the STL. Using two vectors, I implemnted a double ended 
*	queue. The rest of the implementation was done by the STL's functions
*	for class vector. 															
*	
*****************************************************************************/
#ifndef DEQUE_H
#define DEQUE_H

#include <vector>

using namespace std;

template <class T> class DequeIterator;

template <class T>
class Deque {

public:
	typedef DequeIterator<T> iterator;
	
	Deque(): vecOne(), vecTwo() { }
	Deque(unsigned int size, T& initial): vecOne(size/2, initial), vecTwo(size-(size/2), initial) { }
	Deque(Deque<T> & d): vecOne(d.vecOne), vecTwo(d.vecTwo) { }

	T & operator[](unsigned int);
	T & front();
	T & back();
	bool empty() {return (vecOne.empty() && vecTwo.empty());}
	iterator begin() {return iterator(this,0);}
	iterator end() {return iterator(this,size());}
	void erase(const iterator &);
	void erase(const iterator &, const iterator &);
	void insert(const iterator &, const T &);
	int size(){return vecOne.size()+vecTwo.size();}
	void push_front(const T & value) {vecOne.push_back(value);}
	void push_back(const T & value) {vecTwo.push_back(value);}
	void pop_front();
	void pop_back();

protected:
	vector<T> vecOne;
	vector<T> vecTwo;
};

template <class T>
void Deque<T>::erase(const iterator & pos)
{
	int index = pos.index;
	int vOneSize = vecOne.size();
	
	if(index < vOneSize)
		vecOne.erase(vecOne.begin() + ((vOneSize-1)-index));
	else
		vecTwo.erase(vecTwo.begin() + (index - vOneSize));		
}

template <class T>
void Deque<T>::insert(const iterator & pos, const T & value)
{
	int index = pos.index;
	int n = vecOne.size();

	if(index < n)
		vecOne.insert(vecOne.begin() + ((n)-index), value);
	else
		vecTwo.insert((vecTwo.begin() + (index-n)),value);
}

template <class T>
void Deque<T>::erase(const iterator & start, const iterator & stop)
{
	const int vec_one_size = vecOne.size();
	iterator pos;
	
	if(start.index < vecOne.size() && stop.index > (vecOne.size()-1))
	{
		vecOne.erase(vecOne.begin(), (vecOne.begin() + (vec_one_size- start.index)));
		vecTwo.erase(vecTwo.begin(), (vecTwo.begin() + (stop.index - vec_one_size)));
	}
	else if(start.index < vecOne.size() && stop.index < vecOne.size())
	{
		for(pos=start; pos != stop; pos++)
			erase(pos);
	}
	else if(start.index >= vecOne.size() && stop.index > vecOne.size())
	{
		for(pos=start; pos != stop; pos++)
			erase(pos);
	}	
}

template <class T>
void Deque<T>::pop_back()
{
	if(vecTwo.empty())
		vecOne.erase(vecOne.begin());
	else
		vecTwo.pop_back();	
}

template <class T>
void Deque<T>::pop_front()
{
	if(vecOne.empty())
		vecTwo.erase(vecTwo.begin());
	else
		vecOne.pop_back();
}

template <class T>
T & Deque<T>::front()
{
	if(vecOne.empty())
		return vecTwo.front();
	else
		return vecOne.back();
}

template <class T>
T & Deque<T>::back()
{
	if (vecTwo.empty())
		return vecOne.front();
	else
		return vecTwo.back();
}

template <class T>
T & Deque<T>::operator[](unsigned int index)
{
	int vec_one_size = vecOne.size();
	
	if( vec_one_size > index)
		return vecOne[ (vec_one_size-1)-index ];	
	else
		return vecTwo[ (index - vec_one_size) ];
}

template <class T>
class DequeIterator {
	friend class Deque<T>;
	typedef DequeIterator<T> iterator;

public:
	DequeIterator(): theDeque(0), index(0) { }
	DequeIterator(Deque<T> * d, int i): theDeque(d), index(i) { }
	DequeIterator(const iterator & d): theDeque(d.theDeque), index(d.index) { }

	T & operator*(){return (*theDeque)[index];}
	iterator & operator++(){++index; return *this;}
	iterator operator++(int){iterator clone(theDeque,index);++index;return clone;}
	iterator & operator--(){--index;return *this;}
	iterator operator--(int){iterator clone(theDeque,index);--index;return clone;}
	bool operator==(const iterator & r){ return (r.theDeque == theDeque && index == r.index);}
	bool operator!=(const iterator & r) {return (theDeque == r.theDeque && index != r.index);}
	bool operator<(const iterator & r){return (theDeque == r.theDeque && index < r.index);}
	bool operator<=(const iterator & r){return (theDeque == r.theDeque && index <= r.index);}
	T & operator[](unsigned int i){return (*theDeque)[index+i];}
	iterator operator=(const iterator & r) {theDeque = r.theDeque; index = r.index;return *this;}
	iterator operator+(int i){return iterator(theDeque, index + i);}
	iterator operator-(int i){return iterator(theDeque, index - i);}

protected:
	Deque<T> * theDeque;
	int index;
};
#endif

