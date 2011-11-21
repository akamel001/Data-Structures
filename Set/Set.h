/*******************************************************

     Name: Abdelrahman Kamel

     Date: March 17, 2009

     Filename: Set.h

     Description: This file contains the class Set and 
	  Set_iterator along with the member functions of 
	  those classes. 

     Implementation: The implementation of this set is
	  for a single set not a multiset. Member functions
	  such as a begin() and count where implemented using
	  using in order search (LNR).

*******************************************************/ 
#ifndef SET_H
#define SET_H

// Set.h - an implementation of Set using Node and Set_iterator

using namespace std;

template <class T> class Set;
template <class T> class Set_iterator;

template <class T>
class Node {
public:
	Node(): value(0), parent(0), leftChild(0), rightChild(0) { }
	Node(const T & x, Node * p, Node * lc, Node * rc):	value(x), parent(p), leftChild(lc), rightChild(rc) { }
	void insert(Node<T> * newNode); // this is a helper func for Set::insert()
	void inorder_count(const Node<T> * pos, const T & val, int & count);//this is a helper func for Set::count()
	Node * find(const T & x);
	Node * merge(Node<T> * left, Node<T> * right);
protected:
	T value;
	Node * parent;
	Node * leftChild;
	Node * rightChild;

friend class Set<T>;
friend class Set_iterator<T>;
};

//NEED REVIEW, TIME COMPLEXITY?
template <class T>
Node<T> * Node<T>::find(const T & x)
{
	if(x == value)
		return this;
	
	if(x < value)
	{
		if( leftChild == 0)
			return 0;
		return leftChild -> find(x);
	}

	if( rightChild == 0)
		return 0;
	return rightChild -> find(x);

}


template <class T>
void Node<T>::insert(Node<T> * newNode)
{
	if((newNode -> value) < value)
		if(leftChild)
			leftChild -> insert (newNode);
		else
		{newNode -> parent = this;
		leftChild = newNode;}

	else
		if(rightChild)
			rightChild -> insert(newNode);
		else
		{newNode -> parent = this;
		rightChild = newNode;}

}

template <class T>
void Node<T>::inorder_count(const Node<T> * pos, const T &val, int & count)
{
	if(pos)
	{
		inorder_count(pos -> leftChild, val, count);
		if(pos -> value == val) count++;
		inorder_count(pos -> rightChild, val, count);
	}
}

//NEEDS REVIEW, TIME COMPLEXITY?
template <class T>
Node<T> * Node<T>::merge(Node<T> * left, Node<T> * right)
{
	if(left == 0)
		return right;
	if(right == 0)
		return left;
	
	Node<T> * child = merge(left, right -> leftChild);

	child -> parent = right;
	right -> leftChild = child;

	return right;
			
}

template <class T>
class Set {
public:
	typedef Set_iterator<T> iterator;

	Set(): root(0), my_size(0) { }

	//homework functions	
	Set s_union(const Set<T> & operand);
	Set intersect(const Set<T> & operand);
	Set difference(const Set<T> & operand);
	bool subset(const Set<T> & operand);
		
	bool empty() const { return root == 0; }
	unsigned int size() const { return my_size; }
	void insert(const T & x);
	void erase(iterator & it);
	void erase(const T & x) { root = remove(root, x); my_size--;}
	unsigned int count(const T & x) const; // returns 1 or 0 because this is a set, not a multi-set
	iterator find(const T & x) const { return root -> find(x); }
	iterator begin() const; // for in-order traversal
	iterator end() const { return iterator(0); }
protected:
	Node<T> * root;
	unsigned int my_size;
	Node<T> * remove(Node<T> *, const T &);
};

/***********************************************************
 *	
 *	Discription: This function takes in a set as its explicit
 *	perameter. It then returns a bool value based on the implicit
 *	set. If the implicit set is a subset of the explicit set then
 *	it returns true else it returns false.
 *	
 *	Implementation: Using a Set_iterator to iterate through 
 *	the implicit set, to find elements that are in the explicit set
 *	if all of them are found then status is set to true. However,
 *	as soon as one of them is not found status is set to false, 
 *	and the loop breaks.
 *
 * ********************************************************/
template <class T>
bool Set<T>::subset(const Set<T> & operand)
{
	bool status = false;
	iterator itr = begin();

	for(;itr != end(); itr++)
	{
		if( operand.find(*itr) > 0)
			status = true;
		else
		{
			status = false;
			break;
		}
	}

	return status;
}

/***********************************************************
 *	
 *	Discription: This function find the diffence of the implicit
 *	set and the explicit set. After finding the diffrence of the
 *	sets, the function returns a result as a set. 
 *	
 *	Implementation: This function was implemented using a tempSet
 *	to hold the result and iterators to move through the elements.
 *	First we fill the tempSet with all the elements found in the
 *	implicit set. Then we search tempSet to find and remove any
 *	elements found in the expplicit set. 
 *
 * ********************************************************/
template <class T>
Set<T> Set<T>::difference(const Set<T> & operand)
{
	Set<T> tempSet;
	
	iterator itr = begin();
	for(;itr != end(); itr++)
		tempSet.insert(*itr);
	
	itr = operand.begin();
	for(;itr != operand.end(); itr++)
		if(!tempSet.empty() && tempSet.find(*itr) > 0)
			tempSet.erase(*itr);
	
	return tempSet;	
}

/***********************************************************
 *
 *	Discription: This function returns a set with the result
 *	of intersecting the implicit set with the explicit set. 
 *
 *	Implementation: The implementation was done by using a
 *	temp set and iterators. First we make a loop that loops
 *	until the end of the explicit set. With every iteration 
 *	of the loop there is a pointer pointing at the element.
 *	If the element is found in the implicit set then insert it
 *	into tempSet. After the loop we return tempSet.
 *
 * ********************************************************/
template <class T>
Set<T> Set<T>::intersect(const Set<T> & operand)
{
	Set<T> tempSet;

	iterator itr = operand.begin();

	for(;itr!=operand.end();itr++)
		if(find(*itr) != 0)
			tempSet.insert(*itr);

	return tempSet;
}

/***********************************************************
 *
 *	Discription: This function returns a set with the result
 *	of the implicit set union explicit set.
 *
 *	Implementation: This function was also implemented using
 *	a tempSet and iterators. First we loop and fill tempSet
 *	with all the elements found in the implicit set. Then 
 *	we fill tempSet with all the elements found in the explicit
 *	set. After we are done filling tempSet we return it. 
 *
 * ********************************************************/

template <class T>
Set<T> Set<T>::s_union(const Set<T> & operand)
{
	Set<T> tempSet;
	iterator itr = begin();

	for(;itr != end(); itr++)
		tempSet.insert(*itr);

	itr = operand.begin();
	for(;itr != operand.end(); itr++)
		tempSet.insert(*itr);	

	return tempSet;
}

//NEEDS REVIEW, TIME COMPLEXITY?
template <class T>
Node<T> * Set<T>::remove(Node<T> * current, const T &testEle)
{
	if(current)
	{
		Node<T> * pa = current -> parent;
		if(testEle < current -> value)
			current -> leftChild = remove(current -> leftChild, testEle);	
		else if(current -> value < testEle)
			current -> rightChild = remove(current -> rightChild, testEle);
		else
		{
			Node<T> * result = current->merge(remove(current -> leftChild,testEle),current->rightChild);
			delete current;
			if(result)
				result -> parent = pa;
			return result;
		}

	}
	return current;
}

template <class T>
unsigned int Set<T>::count(const T & element) const
{
	int count = 0;
	root -> inorder_count( root, element, count);
	return count;
}

template <class T>
void Set<T>::insert(const T & newEle)
{

	if( count(newEle))
		return; 
	
	Node<T> * newNode = new Node<T>(newEle,0,0,0);

	if(root == 0)
		root = newNode;
	else
		root -> insert(newNode);

	my_size++;
}

template <class T>
typename Set<T>::iterator Set<T>::begin() const
{
	Node<T> * current = root;//WHY DOES THIS WORK?
	while (current && current -> leftChild)
		current = current -> leftChild;

	return iterator(current); 
}


template <class T>
class Set_iterator {
public:
	Set_iterator(): n(0) { }
	Set_iterator(Node<T> * newNode): n(newNode) { }

	//helper operator for set::subset function
	bool operator>(Set_iterator it) const { return n > it.n; }

	bool operator==(Set_iterator it) const { return n == it.n; }
	bool operator!=(Set_iterator it) const { return n != it.n; }
	Set_iterator & operator++(); // inorder traversal, pre-increment
	Set_iterator operator++(int); // inorder traversal, post-increment
	T & operator*() { return n->value; }
	Set_iterator & operator=(Set_iterator<T> it) { n = it.n; return *this; }
protected:
	Node<T> * n;
friend class Set<T>;
};


template <class T>
Set_iterator<T> & Set_iterator<T>::operator++()
{
	if(n -> rightChild)
	{
		n = n -> rightChild;

		while( n -> leftChild)
			n = n -> leftChild;
	}
	else
	{
		Node<T> * child = n;
		n = n -> parent;
		
		while( n && n -> rightChild == child)
		 {
			 child = n;
			 n = n -> parent;
		 }
	}
	return *this;
}

template <class T>
Set_iterator<T> Set_iterator<T>::operator++(int)
{
	Set_iterator<T> clone(n);
	operator++();
	return clone;
}

#endif

