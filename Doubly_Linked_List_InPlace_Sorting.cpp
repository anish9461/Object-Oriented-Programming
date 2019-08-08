//CIS554 HW1
//Name - Anish Nesarka
//Email - anesarka@syr.edu
//SUID - 368122582

#include <iostream>
using namespace std;

class node {
public:
	int value;
	node * next;
	node * previous;
	node(int i) { value = i; next = previous = nullptr; }
	node() { next = previous = nullptr; }
};

class doubly_linked_list {
public:
	node * head;
	node * tail;
	doubly_linked_list() { head = tail = nullptr; }
	void make_random_list(int m, int n);
	void print_forward();
	void print_backward();

	//inplement the following member functions:

	void sort();//sort all values based on frequency.
						  //In case of ties, the values occur earlier will appear earlier
						  //Example:  for list with values  7 6 12 4 33 12 6 6 7
						  //sorted results: 6 6 6 7 7 12 12 4 33

	void insert(int k);
	//after insert(12) to the above,
	//we have 6 6 6 12 12 12 7 7 4 33
	//Insert value k to a frequency_sorted list
	//After insert, the list remains frequency_sorted

	void remove(int k, int n); //remove value k n times from a frequency_sorted list.
							   //if there are fewer than n occurances of k, then remove all occurnces of k
							   //The final result will remain a frequency_sorted list.
							   //For example, if the list is 7 7 7 2 2 4 4 5 5 44 3
							   //After remove(2,5), the list will become 7 7 7 4 4 5 5 44 3
};



void doubly_linked_list::make_random_list(int m, int n) {
	for (int i = 0; i < m; i++)
	{
		node * p1 = new node(rand() % n);
		p1->previous = tail;
		if (tail != nullptr) tail->next = p1;
		tail = p1;
		if (head == nullptr) head = p1;
	}
}

void doubly_linked_list::print_forward() {
	cout << endl;
	node * p1 = head;
	while (p1 != nullptr) {
		cout << p1->value << " ";
		p1 = p1->next;
	}
}

void doubly_linked_list::print_backward() {
	cout << endl;
	node * p1 = tail;
	while (p1 != nullptr) {
		cout << p1->value << " ";
		p1 = p1->previous;
	}
}

void doubly_linked_list::sort()
{
	int f = 0, fmax = 0, temp2, count = 0, sizeOflist = 0;;
	node *temp, *p, *temp1, *ttail, *p1, *p2, *test;
	test = head;
	while (test != NULL)
	{
		sizeOflist++;
		test = test->next;
	}
	temp = head;
	ttail = tail;
	while (count != sizeOflist)
	{
		p = head;
		temp = head;
		for (int i = 0; i < (sizeOflist - count); i++)
		{
			while (p != ttail->next)
			{
				if (temp->value == p->value)
				{
					f = f + 1;
				}
				p = p->next;
			}
			if (fmax < f)
			{
				fmax = f;
				temp2 = temp->value;
			}
			else if (fmax == f)
			{
				f = 0;
				temp = temp->next;
				continue;
			}
			p = head;
			f = 0;
			temp = temp->next;
		}
		node *p1, *p2;
		p1 = head;
		p2 = head->next->next;
		for (int k = 0; k < (sizeOflist - count); k++)
		{
			if (head->value == temp2)
			{
				head->previous = tail;
				tail->next = head;
				tail = head;
				p1 = p1->next;
				tail->next = NULL;
				head = p1;
				p1->previous = NULL;
				p2 = p2->next;
			}
			else if (p1->next->value == temp2)
			{

				temp1 = p1->next;
				tail->next = temp1;
				temp1->previous = tail;
				tail = temp1;
				tail->next = NULL;
				p1->next = p2;
				p2->previous = p1;
				p2 = p2->next;
			}
			else {
				p1 = p1->next;
				if (p2 == NULL)
				{
					return;
				}
				p2 = p2->next;
			}
		}
		count = count + fmax;
		fmax = 0;
	}
}

void doubly_linked_list::insert(int k)
{
	node *p1, *p2;
	node *temp = new node(k);
	p1 = head;
	p2 = head->next;
	while (p1->next != NULL)
	{
		if (p1->value == k)
		{
			p1->next = temp;
			temp->previous = p1;
			temp->next = p2;
			p2->previous = temp;
			sort();
			return;
		}
		else
		{
			p1 = p1->next;
			p2 = p2->next;
		}
	}
	p1->next = temp;
	temp->previous = p1;
	tail = temp;
	sort();
}

void doubly_linked_list::remove(int k, int n)
{
	node *p1, *p2;
	p1 = head;
	p2 = head->next->next;
	for (int i = 0; i < n; i++)
	{
		while (p1->next != NULL)
		{
			if (head->value == k)
			{
				head = p1->next;
				p1 = p1->next;
				p1->previous = NULL;
				p2 = p2->next;
				break;
			}
			else if ((p1->next->value == k) && p1->next == tail)
			{
				tail = p1;
				p1->next = NULL;
				break;
			}
			else if (p1->next->value == k)
			{
				p1->next = p2;
				p2->previous = p1;
				p2 = p2->next;
				break;
			}
			else
			{
				p1 = p1->next;
				if (p2 == NULL)
					break;
				p2 = p2->next;
			}
		}
	}
	sort();
}

int main() {
	doubly_linked_list d1;
	d1.make_random_list(50, 20);
	d1.print_forward();
	d1.print_backward();

	d1.sort();
	d1.print_forward();
	d1.print_backward();

	d1.insert(16);
	d1.print_forward();
	d1.print_backward();

	d1.insert(16);
	d1.print_forward();
	d1.print_backward();

	d1.insert(16);
	d1.print_forward();
	d1.print_backward();

	d1.insert(16);
	d1.print_forward();
	d1.print_backward();

	d1.remove(4, 3);
	d1.print_forward();
	d1.print_backward();

	getchar();
	getchar();
	return 0;
}