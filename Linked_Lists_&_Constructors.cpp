//CIS554 HW4
//Name - Anish Nesarkar
//Email - anesarka@syr.edu
//SUID - 368122582
#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
using namespace std;

template <class T> class ThreeD {
public:
	T ht;
	T wid;
	T dep;
	ThreeD() { ht = wid = dep = 0; }
	ThreeD(T i) { ht = wid = dep = i; }
	ThreeD(T a, T b, T c) { ht = a; wid = b; dep = c; }
	template<class T> friend ostream & operator<<(ostream &str, const ThreeD<T> &T);
	T const vol()
	{
		return (ht * wid * dep);
	}
	bool const operator==(ThreeD T)
	{
		return (vol() == T.vol());
	}
	//two objects are equal if their vol() are the same.
};

//operator overloading for ThreeD
template<class T> ostream & operator<<(ostream &str, const ThreeD<T> &T)
{
	str << "( " << T.ht << ", " << T.wid << ", " << T.dep << " )";
	return str;
}

//node class
template <class T> class node {
public:
	T value;
	node<T> * next;
	node<T> * previous;
	node<T>() { next = nullptr; previous = nullptr; }
	node<T>(T v) { value = v; next = nullptr; previous = nullptr; }
	bool const operator==(const node<T> &N)
	{
		return (value == N.value);
	}
};
template <class T> class linked_list {
public:
	node<T> * first; //position of first node
	node<T> * last; //position of last node
	linked_list() { first = last = nullptr; }
	~linked_list();
	void operator=(const linked_list<T> &L);
	
	linked_list(const linked_list<T> &L);
	void push_front(T t);
	void push_back(T t);
	linked_list(const initializer_list<T> &V);

	//operator== for linked list
	bool operator==(linked_list &L)
	{
		if (first == NULL)
			return false;
		node<T> *test = L.first;
		node<T> *temp = first;
		while (test != NULL)
		{
			if (test->value == temp->value)
			{
				test = test->next;
				temp = temp->next;
				continue;
			}
			else
				break;
		}
		if (test == NULL)
			return true;
		else
			return false;
	}

};


//copy constructor
template <class T> linked_list<T>::linked_list(const linked_list<T> &L) : linked_list() { 
	
	auto i = L.first;
	while (i != NULL)
	{
		node<T> *temp = new node<T>(*(i));
		temp->previous = last;
		if (last != nullptr)
			last->next = temp;
		last = temp;
		if (first == nullptr)
			first = temp;
		i = i->next;
	}

}

//operator=
template <class T> void linked_list<T>::operator=(const linked_list<T> &L) { 
	
	auto i = L.first;
	while (i != NULL)
	{
		node<T> *temp = new node<T>(*(i));
		temp->previous = last;
		if (last != nullptr)
			last->next = temp;
		last = temp;
		if (first == nullptr)
			first = temp;
		i = i->next;
	}
}

//initializer list for linked list
template <class T> linked_list<T>::linked_list(const initializer_list<T> &V) : linked_list()
{
	auto i = V.begin();
	while (i != V.end())
	{
		node<T> *temp = new node<T>(*i);
		node<T> *p;
		p = first;
		if (p == NULL)
		{
			first = temp;
			last = temp;
			i++;
			continue;
		}
		while (p->next != NULL)
		{
			p = p->next;
		}
		p->next = temp;
		temp->previous = p;
		temp->next = NULL;
		last = temp;
		i++;
	}
}

template <class T> linked_list<T>::~linked_list() {  

	
	if (first == NULL)
		return;
	while (first)
	{
		node<T> * temp = first;
		first = first->next;
		delete temp;
	}

}


//push front for linked list
template <class T> void linked_list<T>::push_front(T t)
{
	node<T> *temp = new node<T>(t);
	if (first == NULL)
	{
		first = temp;
		last = temp;
		return;
	}
	first->previous = temp;
	temp->next = first;
	temp->previous = NULL;
	first = temp;
}

//push back for linked list
template <class T> void linked_list<T>::push_back(T t)
{
	node<T> *temp = new node<T>(t);
	node<T> *p;
	p = first;
	if (p == NULL)
	{
		first = temp;
		last = temp;
		return;
	}
	while (p->next != NULL)
	{
		p = p->next;
	}
	p->next = temp;
	temp->previous = p;
	temp->next = NULL;
	last = temp;
}

//operator overloading for linked list
template<class T> ostream & operator<<(ostream &str, linked_list<T> &L)
{
	node<T> *temp = (L.first);
	while (temp != nullptr)
	{
		str << temp->value << " ";
		temp = temp->next;
	}
	return str;
}


template <class X>
class item {
public:
	X data;
	item<X> *next;
	item<X> *previous;
	item<X>(X d) { data = d; next = nullptr; previous = nullptr; }
	item<X>() { next = nullptr; previous = nullptr; }
	bool operator==(item<X> &I)
	{
		return (data == I.data);
	}
};


template <class X>
class bag {
public:
	item<X> *head; //position of first item
	item<X> *tail; //positon of last item
	int num_items;
	int size() { return num_items; }
	bag() { head = nullptr; tail = nullptr; num_items = 0; }
	~bag()
	{
		if (head == NULL)
			return;
		while (head)
		{
			item<X> * temp = head;
			head = head->next;
			delete temp;
		}		
	}
	void push_back(X d);  //insert an item with data d to the back of the bag
	void push_front(X d); //insert an item with data d to the front of the bag
	void pop_back(); //delete the last item in the bag
	void pop_front(); //delete the first item in the bag
	X &operator[](int i); //Access bag item with index. 

	X front() {  //it returns the data of the first item in the bag.
				 //if (num_items == 0) do nothing;
				 //else return head->data;
		item<X> *temp;
		temp = head;
		if (num_items != 0)
			return head->data;
		else
			return (X)NULL;
	}
	
	X back() { //it returns the data of the last item in the bag
			   /*
			   if (num_items == 0) do nothing;
			   else return tail->data;
			   */
		item<X> *temp;
		temp = tail;
		if (num_items != 0)
			return temp->data;
		else
			return (X)NULL;

	}
	void clear(); //Delete all items in the bag
	item<X> * find(X d); //return nullptr if no match for find or if the bag is empty.
						 //else, return the postion of the matched item

	void erase(int index);
	void erase(item<X> * p);
	item<X> * insert(item<X> *p, X d); //insert data d to the position before p and return the position of the inserted item
	//initializer list
	bag(const initializer_list<X> &V);
	
	//copy constructor
	bag(const bag &B);

	//operator=
	void operator=(const bag &B);


	

};


//operator=
template <class X> void bag<X>::operator=(const bag &B)
{
	auto i = B.head;
	while (i != NULL)
	{
		item<X> *temp = new item<X>(*(i));
		temp->previous = tail;
		if (tail != nullptr)
		{
			tail->next = temp;
			num_items++;
		}
		tail = temp;
		if (head == nullptr)
		{
			head = temp;
			num_items++;
		}
		i = i->next;
	}
}

//copy constructor
template<class X> bag<X>::bag(const bag &B) : bag()
{
	auto i = B.head;
	while (i != NULL)
	{	
		item<X> *temp = new item<X>(*(i));
		temp->previous = tail;
		if (tail != nullptr)
			tail->next = temp;
		tail = temp;
		if (head == nullptr)
			head = temp;
		i = i->next;
	}	
}

//initializer list for bag
template <class X> bag<X>::bag(const initializer_list<X> &V) : bag()
{
	auto i = V.begin();
	while (i != V.end())
	{
		item<X> *temp = new item<X>(*i);
		item<X> *p;
		p = head;
		if (p == NULL)
		{
			head = temp;
			tail = temp;
			num_items++;
			i++;
			continue;
		}
		while (p->next != NULL)
		{
			p = p->next;
		}
		p->next = temp;
		temp->previous = p;
		temp->next = NULL;
		tail = temp;
		num_items++;
		i++;
	}			
}



//bag functions
//push back for bag
template<class X> void bag<X>::push_back(X d)
{
	item<X> *temp = new item<X>(d);
	item<X> *p;
	p = head;
	if (p == NULL)
	{
		head = temp;
		tail = temp;
		num_items++;
		return;
	}
	while (p->next != NULL)
	{
		p = p->next;
	}
	p->next = temp;
	temp->previous = p;
	temp->next = NULL;
	tail = temp;
	num_items++;
}

//push front for bag
template<class X> void bag<X>::push_front(X d)
{
	item<X> *temp = new item<X>(d);
	if (head == NULL)
	{
		head = temp;
		tail = temp;
		num_items++;
		return;
	}
	head->previous = temp;
	temp->next = head;
	temp->previous = NULL;
	head = temp;
	num_items++;
}

//pop front for bag
template<class X> void bag<X>::pop_front()
{
	item<X> *temp;
	if (head == NULL)
		return;
	temp = head;
	head = head->next;
	head->previous = NULL;
	delete temp;
	num_items--;
}

//pop back for bag
template<class X> void bag<X>::pop_back()
{
	item<X> *temp;
	if (tail == NULL)
		return;
	temp = tail;
	tail = tail->previous;
	tail->next = NULL;
	delete temp;
	num_items--;
}

//operator overloading for bag
template<class X> ostream & operator<<(ostream &str, bag<X> &B)
{
	item<X> *temp = (B.head);
	while (temp != nullptr)
	{
		str << temp->data << " ";
		temp = temp->next;
	}
	return str;
}

//operator []
template <class X> X& bag<X>::operator[](int i)
{
	int *x = nullptr;
	if (i < 0 || i > num_items)
		return (X&)x;
	item<X> *temp = head;
	int count = 0;
	while (count < i)
	{
		temp = temp->next;
		count++;
	}
	return temp->data;
}

//clear function
template <class X> void bag<X>::clear()
{
	if (head == NULL)
		return;
	item<X> *p1 = head;
	item<X> *p2 = p1->next;
	while (p2 != NULL)
	{
		delete p1;
		num_items--;
		p1 = p2;
		p2 = p2->next;
	}
	delete p1;
	num_items--;
	head = NULL;
}

//insert function
template <class X> item<X> * bag<X>::insert(item<X> *p, X d)
{
	item<X> *temp = new item<X>(d);
	if (p == head)
	{
		temp->next = p;
		p->previous = temp;
		head = temp;
		num_items++;
		return temp;
	}
	else 
	{
		p->previous->next = temp;
		temp->next = p;
		temp->previous = p->previous;
		p->previous = temp;
		num_items++;
		return temp;
	}
}

//erase function using index
template <class X> void bag<X>::erase(int index)
{
	if ((index < 0) || (index > num_items))
		return;
	item<X> *temp = head;
	int count = 0;
	while (count < index)
	{
		temp = temp->next;
		count++;
	}
	if (index == 0)
	{
		head = temp->next;
		head->previous = NULL;
		delete temp;
		num_items--;
		return;
	}
	else if (index == (num_items - 1))
	{
		temp = tail;
		tail = tail->previous;
		tail->next = NULL;
		delete temp;
		num_items--;
		return;
	}
	else
	{
		temp->previous->next = temp->next;
		temp->next->previous = temp->previous;
		delete temp;
	}
}


//erase function for an item in the bag
template <class X> void bag<X>::erase(item<X> * p)
{
	if (head == NULL)
		return;
	item<X> *temp = head;
	while (temp != NULL)
	{
		if (temp == p)
		{
			break;
		}
		temp = temp->next;
	}
	if (p == head)
	{
		head = temp->next;
		head->previous = NULL;
		delete temp;
		num_items--;
		return;
	}
	else if (p == tail)
	{
		temp = tail;
		tail = tail->previous;
		delete temp;
		num_items--;
		return;
	}
	else
	{
		temp->previous->next = temp->next;
		temp->next->previous = temp->previous;
		delete temp;
	}
}


//operator overloading for vector
template <class T> ostream & operator<<(ostream &str, vector<T> &V)
{
	str << "[";
	for (size_t i = 0; i < (V.size() - 1); i++) {
		str << V[i] << " , ";
	}
	str << V[V.size() - 1];
	str << "]";
	return str;
}

//find function
template <class X> item<X> * bag<X>::find(X d)
{
	if (head == NULL)
		return (item<X>*)NULL;
	item<X> * temp = head;
	while (temp != nullptr)
	{
		if (temp->data == d)
			return temp;
		temp = temp->next;
	}
	return temp;

}

//operator== for vector
template <class T> bool operator==( vector<T> &lhs,  vector<T> &rhs)
{
	int count = 0;
	if (lhs.size() != rhs.size())
		return false;
	else
	{
		for(size_t i=0;i < lhs.size();i++)
		{
			if (lhs[i] == rhs[i])
			{
				count++;
				continue;
			}
			else
				break;
		}
		if (count == lhs.size())
			return true;
		else
			return false;

	}
}



int main() {


	bag<double> bag_d;
	bag_d.push_back(5.5);
	bag_d.push_back(6.6);
	bag_d.push_front(4.4);
	bag_d.push_front(3.3);
	bag_d.pop_front();
	bag_d.pop_back();
	cout << bag_d << endl;;
	bag<int> bag_i;
	bag_i.push_back(5);
	bag_i.push_back(6);
	bag_i.push_front(4);
	bag_i.push_front(3);
	bag_i.pop_front();
	bag_i.pop_back();
	cout << bag_i << endl;

	ThreeD<int> td3(3), td4(4), td5(5), td6(6), td7(100, 200, 300);
	bag<ThreeD<int>> bag_3D;
	bag_3D.push_back(td5);
	bag_3D.push_back(td6);
	bag_3D.push_front(td4);
	bag_3D.push_front(td3);
	bag_3D.pop_front();
	bag_3D.pop_back();
	cout << bag_3D << endl;;
	cout << bag_3D.front() << bag_3D.back();
	cout << bag_3D[0] << " " << bag_3D[1] << endl;
	bag_3D[1] = td7;
	cout << bag_3D[0] << " " << bag_3D[1] << endl;
	bag_3D.clear();
	cout << bag_3D << endl;;
	cout << bag_3D.size() << endl;
	linked_list<string>ls_1;
	ls_1.push_front("David");
	ls_1.push_front("John");
	ls_1.push_front("Pat");
	ls_1.push_front("Ben");
	ls_1.push_front("Jeff");
	cout << ls_1 << endl;

	linked_list<string>ls_2;
	ls_2.push_front("Wendy");
	ls_2.push_front("Mary");
	ls_2.push_front("Nancy");
	ls_2.push_front("Jennifer");
	cout << ls_2 << endl;

	bag<linked_list<string>> bag_string;

	bag_string.push_back(ls_1);

	bag_string.push_back(ls_2);

	cout << bag_string << endl;
	cout << bag_string[1] << endl;

	ThreeD<double> t10(3.2, 7.4, 8.9), t11(5.6, 7.7, 2.987), t12(4.6, 7.5, 3.1416), t13(55.6, 66.8, 333.45);
	linked_list<ThreeD<double>> LTD1;
	LTD1.push_front(t10);

	LTD1.push_front(t11);
	linked_list<ThreeD<double>> LTD2;
	LTD2.push_front(t13);
	LTD2.push_front(t12);
	LTD2.push_front(t10);
	LTD2.push_front(t11);

	bag<linked_list<ThreeD<double> > > BLTD;
	BLTD.push_back(LTD1);
	BLTD.push_back(LTD2);
	cout << BLTD << endl;

	item<linked_list<ThreeD<double>>> * p2;

	p2 = BLTD.find(LTD1);
	BLTD.erase(p2);
	cout << BLTD << endl;
	BLTD.push_back(LTD1);
	cout << BLTD << endl;
	BLTD.erase(0);
	cout << BLTD << endl;

	vector<ThreeD<int>> V1 = { { 1,2,3 },{ 4,5,6 },{ 7,8,9 } };
	cout << V1 << endl;
	//bag<bag<int>> V2 = { {1,2,3}, {4,5,6}, {7,8,9} };
	vector<bag<ThreeD<int>>> V2 = { { { 1,2,3 },{ 4,5,6 },{ 7,8,9 } },{ { 20,30,40 },{ 11,22, 33 } } };
	cout << V2 << endl;

	vector<bag<linked_list<int>>> V3 = { { { 1, 2, 3 },{ 4, 5 } },{ { 6,7 },{ 8, 9, 10 } } };
	cout << V3 << endl;

	bag<int> B10 = { 1,2,3,4,5 };
	bag<int> B11 = B10, B12;
	B12 = B10;
	cout << B10 << endl;
	B10.head->data = 1000;
	cout << B10 << endl;
	cout << B11 << endl;
	cout << B12 << endl;

	bag<vector<linked_list<ThreeD<int>>>> B13 = { { { { 1,2,3 },{ 4,5,6 } },{ { 7,8,9 },{ 10,11,12 },{ 13,14,15 } } },{ { { 16,17,18 },{ 19,20,21 },{ 22,23,24 } },{ { 25,26,27 },{ 28,29,30 } },{ { 31,32,33 },{ 34,35,36 },{ 37,38,39 },{ 40,41,42 } } } };
	cout << B13 << endl;

	bag<bag<bag<ThreeD<int>>>> B14 = { { { { 1,2,3 },{ 4,5,6 } },{ { 7,8,9 },{ 10,11,12 },{ 13,14,15 } } },{ { { 16,17,18 },{ 19,20,21 },{ 22,23,24 } },{ { 25,26,27 },{ 28,29,30 } },{ { 31,32,33 },{ 34,35,36 },{ 37,38,39 },{ 40,41,42 } } } };
	cout << B14 << endl;

	bag<linked_list<int>> * p10 = new bag<linked_list<int>>({ { 1,2,3,4 },{ 5,6,7 } });
	cout << *p10 << endl;
	delete p10;
	bag<vector<linked_list<ThreeD<int>>>> B15 = { { { { 1,2,3 },{ 4,5,6 } },{ { 7,8,9 },{ 10,11,12 },{ 13,14,15 } } },{ { { 16,17,18 },{ 19,20,21 },{ 22,23,24 } },{ { 25,26,27 },{ 28,29,30 } },{ { 31,32,33 },{ 34,35,36 },{ 37,38,39 },{ 40,41,42 } } } };
	cout << B15 << endl;
	B15.erase(1);
	cout << B15 << endl;
	bag<vector<linked_list<ThreeD<int>>>> B16 = { { { { 1,2,3 },{ 4,5,6 } },{ { 7,8,9 },{ 10,11,12 },{ 13,14,15 } } },{ { { 16,17,18 },{ 19,20,21 },{ 22,23,24 } },{ { 25,26,27 },{ 28,29,30 } },{ { 31,32,33 },{ 34,35,36 },{ 37,38,39 },{ 40,41,42 } } } };
	vector<linked_list<ThreeD<int>>> V4 = { { { 6,1,1 },{ 2,5,12 } },{ { 9,8,7 },{ 11,10,12 },{ 26,7,15 } } };
	vector<linked_list<ThreeD<int>>> V5 = { { { 6,1,1 },{ 2,5,12 } },{ { 9,8,7 },{ 11,10,12 },{ 26,7,5 } },{ { 6,1,1 },{ 2,5,12 } } };
	B16.insert(B16.head, V5);
	cout << B16.front().size() << endl;
	item<vector<linked_list<ThreeD<int>>> > * p20 = B16.find(V4);
	if (p20 != nullptr) cout << (p20->data).size() << endl;
	getchar();
	getchar();
	return 0;
}

//The following is a screenshot of a sample output
/*
4.4 5.5
4 5
( 4, 4, 4 ) ( 5, 5, 5 )
( 4, 4, 4 )( 5, 5, 5 )( 4, 4, 4 ) ( 5, 5, 5 )
( 4, 4, 4 ) ( 100, 200, 300 )
0
Jeff Ben Pat John David
Jennifer Nancy Mary Wendy
Jeff Ben Pat John David  Jennifer Nancy Mary Wendy
Jennifer Nancy Mary Wendy
( 5.6, 7.7, 2.987 ) ( 3.2, 7.4, 8.9 )  ( 5.6, 7.7, 2.987 ) ( 3.2, 7.4, 8.9 ) ( 4.6, 7.5, 3.1416 ) ( 55.6, 66.8, 333.45 )
( 5.6, 7.7, 2.987 ) ( 3.2, 7.4, 8.9 ) ( 4.6, 7.5, 3.1416 ) ( 55.6, 66.8, 333.45 )
( 5.6, 7.7, 2.987 ) ( 3.2, 7.4, 8.9 ) ( 4.6, 7.5, 3.1416 ) ( 55.6, 66.8, 333.45 )  ( 5.6, 7.7, 2.987 ) ( 3.2, 7.4, 8.9 )
( 5.6, 7.7, 2.987 ) ( 3.2, 7.4, 8.9 )
[( 1, 2, 3 ), ( 4, 5, 6 ), ( 7, 8, 9 )]
[( 1, 2, 3 ) ( 4, 5, 6 ) ( 7, 8, 9 ) , ( 20, 30, 40 ) ( 11, 22, 33 ) ]
[1 2 3  4 5  , 6 7  8 9 10  ]
1 2 3 4 5
1000 2 3 4 5
1 2 3 4 5
1 2 3 4 5
[( 1, 2, 3 ) ( 4, 5, 6 ) , ( 7, 8, 9 ) ( 10, 11, 12 ) ( 13, 14, 15 ) ] [( 16, 17, 18 ) ( 19, 20, 21 ) ( 22, 23, 24 ) , ( 25, 26, 27 ) ( 28, 29, 30 ) , ( 31, 32, 33 ) ( 34, 35, 36 ) ( 37, 38, 39 ) ( 40, 41, 42 ) ]
( 1, 2, 3 ) ( 4, 5, 6 )  ( 7, 8, 9 ) ( 10, 11, 12 ) ( 13, 14, 15 )   ( 16, 17, 18 ) ( 19, 20, 21 ) ( 22, 23, 24 )  ( 25, 26, 27 ) ( 28, 29, 30 )  ( 31, 32, 33 ) ( 34, 35, 36 ) ( 37, 38, 39 ) ( 40, 41, 42 )
1 2 3 4  5 6 7
[( 1, 2, 3 ) ( 4, 5, 6 ) , ( 7, 8, 9 ) ( 10, 11, 12 ) ( 13, 14, 15 ) ] [( 16, 17, 18 ) ( 19, 20, 21 ) ( 22, 23, 24 ) , ( 25, 26, 27 ) ( 28, 29, 30 ) , ( 31, 32, 33 ) ( 34, 35, 36 ) ( 37, 38, 39 ) ( 40, 41, 42 ) ]
[( 1, 2, 3 ) ( 4, 5, 6 ) , ( 7, 8, 9 ) ( 10, 11, 12 ) ( 13, 14, 15 ) ]
3
2
*/