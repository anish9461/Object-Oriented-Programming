//CIS554 HW5
//Name - Anish Nesarkar
//Email - anesarka@syr.edu
//SUID - 368122582

#include <iostream>
#include <memory>

using namespace std;

class node {
public:
	shared_ptr<node> east;
	shared_ptr<node> south;
	int value;
	node() {}
	node(int i) { value = i; }
};

class ring {
public:
	//Implement all functions described below
	//funciton operator[] can be invoked by other functions


	shared_ptr<node> head;
	int num_rows;
	int num_cols;
	ring() {}
	ring(int i, int j);//constructor
					   //i rows and j cols
					   //values from 0 to i*j-1
					//See the photo for ring structures.

	~ring();//destructor; do as little work as possible
	ring(const ring &r); //copy constructor
	ring(ring &&r); //move constructor
	void operator=(ring &&r);//R-value operator=
	void operator=(const ring &r); //L-value operator=
	ring(const initializer_list<int> &V);//see the explanation in main function
	int & operator[](int a);
	int & operator[](pair<int, int> p); //first is row number and second is col number

	void DelCol(int i);//delete col i of *this
	ring Threetimes();
	//return a ring with the same dimenstion as *this, and the value of every node is three times of that of *this.

};


//constructor
ring::ring(int i, int j)
{
	num_rows = i;
	num_cols = j;
	shared_ptr<node> temp;
	for (int k = 0; k < i * j; k++)
	{
		shared_ptr<node> p = make_shared<node>(k);
		if (!head) 
		{ 
			head = temp = p;  
			p->east = p; 
		}
		else 
		{
			temp->east = p;
			temp = p;
			p->east = head;
		}
	}

	shared_ptr<node> p = head;
	shared_ptr<node> p1 = head;
	shared_ptr<node> p2 = head;

	int k = 0;
	while (k != (num_rows * num_cols))
	{
		for (int i = 0; i < num_cols; i++)
		{
			p = p->east;
		}

		if (p == p2)
		{		
			p = p->east;
			p2 = p;
		}

		p1->south = p;
		p1 = p;
		if (p->east == head)
		{
			p1->south = head;
			break;
		}
		k++;
	}
}

//destructor
ring::~ring()
{
	if (!head)
	{
		num_rows = 0;
		num_cols = 0;
		return;
	}	
	shared_ptr<node> p = head;
	shared_ptr<node> p1 = head;
	int count = 1;
	while (count != (num_rows * num_cols - 1))
	{
		p = p->east;
		p1 = p1->south;
		count++;
	}
	p->east.reset();
	p1->south.reset();
	num_rows = 0;
	num_cols = 0;
}

//operator[] //index from 0
int& ring:: operator[](int a)
{
	int *x = nullptr;
	if (a >= num_cols * num_rows || a < 0)
	{
		cout << "out of bound" << endl;
		return (int&)x;
	}
		
	if (a == 0)
		return head->value;
	shared_ptr<node> p = head;
	while (a != 0)
	{
		p = p->east;
		a--;
	}
	return p->value;
}


//pair operator[] row = 1,2,3.. and column = 1,2,3..
int& ring::operator[](pair<int, int> p)
{
	int *x = nullptr;
	if (p.first > num_rows || p.second > num_cols || p.first <= 0 || p.second <= 0)
	{
		cout << "out of bound" << endl;
		return (int&)x;
	}

	shared_ptr<node> temp = head;
	for (int i = 0; i < p.first - 1; i++)
		temp = temp->south;
	for (int i = 0; i < p.second - 1; i++)
		temp = temp->east;
	return temp->value;
}


//Delete Column indexed from 0
void ring::DelCol(int i)
{
	if (i > num_cols - 1)
		return;
	shared_ptr<node> p = head;
	shared_ptr<node> p1 = head->east;
	int j = 0;
	if (i == 0)
	{
		while (j != num_cols - 1)
		{
			p = p->east;
			p1 = p1->east;
			j++;
		}
	}
	else
	{
		while (j != (i - 1))
		{
			p = p->east;
			p1 = p1->east;
			j++;
		}
	}

	for (int k = 0; k < num_rows - 1; k++)
	{
		p->east = p1->east;
		p1.reset();
		p = p->south;
		p1 = p->east;
	}

	p->east = p1->east;
	if (i == 0)
	{
		p->south = p1->east;
		head = p1->east;
	}
	else
		p->south = p1->south;
	p1.reset();
	num_cols--;
}

//copy constructor
ring::ring(const ring &r) : ring()
{
	shared_ptr<node> temp  = r.head;
	num_rows = r.num_rows;
	num_cols = r.num_cols;

	shared_ptr<node> tail;
	for (int k = 0; k < num_rows * num_cols; k++)
	{
		shared_ptr<node> p = make_shared<node>(temp->value);
		if (!head)
		{
			head = tail = p;
			p->east = p;
			temp = temp->east;
		}
		else
		{
			tail->east = p;
			tail = p;
			p->east = head;
			temp = temp->east;
		}
	}

	shared_ptr<node> p = head;
	shared_ptr<node> p1 = head;
	shared_ptr<node> p2 = head;

	int k = 0;
	while (k != (num_rows * num_cols))
	{
		for (int i = 0; i < num_cols; i++)
		{
			p = p->east;
		}

		if (p == p2)
		{

			p = p->east;
			p2 = p;
		}

		p1->south = p;
		p1 = p;
		if (p->east == head)
		{
			p1->south = head;
			break;
		}
		k++;
	}
}


//Initializer list
ring::ring(const initializer_list<int> &V) : ring()
{
	auto i = V.begin();
	num_rows = *i; i++;
	num_cols = *i; i++;
	shared_ptr<node> tail;
	while (i != V.end())
	{
		shared_ptr<node> p = make_shared<node>(*i);
		if (!head)
		{
			head = tail = p;
			p->east = p;
		}
		else
		{
			tail->east = p;
			tail = p;
			p->east = head;
		}
		i++;
	}

	shared_ptr<node> p = head;
	shared_ptr<node> p1 = head;
	shared_ptr<node> p2 = head;

	int k = 0;
	while (k != (num_rows * num_cols))
	{
		for (int i = 0; i < num_cols; i++)
		{
			p = p->east;
		}
		if (p == p2)
		{
			p = p->east;
			p2 = p;
		}
		p1->south = p;
		p1 = p;
		if (p->east == head)
		{
			p1->south = head;
			break;
		}
		k++;
	}
}


//L-value operator
void ring::operator=(const ring &r)
{
	shared_ptr<node> temp = r.head;
	num_rows = r.num_rows;
	num_cols = r.num_cols;

	shared_ptr<node> tail;
	for (int k = 0; k < num_rows * num_cols; k++)
	{
		shared_ptr<node> p = make_shared<node>(temp->value);
		if (!head)
		{
			head = tail = p;
			p->east = p;
			temp = temp->east;
		}
		else
		{
			tail->east = p;
			tail = p;
			p->east = head;
			temp = temp->east;
		}
	}

	shared_ptr<node> p = head;
	shared_ptr<node> p1 = head;
	shared_ptr<node> p2 = head;

	int k = 0;
	while (k != (num_rows * num_cols))
	{
		for (int i = 0; i < num_cols; i++)
		{
			p = p->east;
		}

		if (p == p2)
		{

			p = p->east;
			p2 = p;
		}

		p1->south = p;
		p1 = p;
		if (p->east == head)
		{
			p1->south = head;
			break;
		}
		k++;
	}
}


//Three times
ring ring::Threetimes()
{
	shared_ptr<node> p = head;
	ring temp(num_rows, num_cols);
	shared_ptr<node> test = temp.head;
	for (size_t i = 0; i < num_rows * num_cols; i++)
	{
		test->value = 3 * p->value;
		p = p->east;
		test = test->east;
	}
	return move(temp);
}


//move constructor
ring::ring(ring &&r) : ring()
{
	num_rows = r.num_rows;
	num_cols = r.num_cols;
	head = r.head;
	r.head = nullptr;
}

//r-value operator
void ring::operator=(ring &&r)
{
	num_rows = r.num_rows;
	num_cols = r.num_cols;
	head = r.head;
	r.head = nullptr;
}

//overload operator<<
ostream & operator<<(ostream &str, const ring &R)
{
	shared_ptr<node> p = R.head;
	if (!R.head) { return str; }
	int count = 0;
	do {
		if (p->value > 9999)
			str << p->value << "      ";
		else if (p->value >= 100 && p->value < 999)
			str << p->value << "        ";
		else if(p->value >= 1000)
			str << p->value << "       ";
		else if(p->value < 10)
			str << p->value << "          ";
		else
			str << p->value << "         ";
		p = p->east;
		count++;
		if ((count % R.num_cols) == 0)
			str << endl;
	} while (p != R.head);
	return str;
}



int main() {
	ring R1(4, 6);//24 numbers from 0 to 23 will be initialized to nodes.
	cout << R1 << endl;
	R1[14] = 1000;
	R1[{2, 4}] = 2000;
	cout << R1[14] << " " << R1[{2, 4}] << endl;
	R1.DelCol(3);
	cout << R1 << endl;
	R1.DelCol(4);
	cout << R1 << endl;
	R1.DelCol(0);
	cout << R1 << endl;
	shared_ptr<ring> p1 = make_shared<ring>(3, 5);
	cout << *p1 << endl;
	p1.reset();
	ring R2 = { 3, 5, 10,20,30,40,50, 100, 200, 300, 400, 500, 1000, 2000, 3000, 4000, 5000 };//
	 //first two numbers are num_rows and num_cols; followed by values of nodes of ring
	cout << R2 << endl;
	ring R3(R2);
	cout << R3 << endl;
	ring R4;
	R4 = R3;
	cout << R4 << endl;
	ring R5;
	R5 = R4.Threetimes();
	cout << R5 << endl;

	getchar();
	getchar();
	return 0;
}