//CIS554 HW2
//Name - Anish Nesarkar
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
	void make_random_list(int m, int n); //create m nodes with value randomly in 0 ... n-1
	void print_forward();
	void print_backward();

	//inplement the following member functions:

	void sort(node * p1, node * p2);
	//Range of sort is from *p1 to *p2
	//Use in-place quick sort algorithm to sort the linked list in ascending order.
	//You are only allowed to modify the pointers of nodes, but not values of nodes

};


void doubly_linked_list::make_random_list(int m, int n) {

	for (int i = 0; i < m; i++) {
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

void doubly_linked_list::sort(node *p1, node *p2) {

	if ((p1 != NULL) && (p2 != NULL) && (p1 != p2) && (p1->next != NULL))
	{
		node *j, *temp, *i, *i1, *i2, *j1, *j2, *temp2; //pointers used to traverse and swap
		temp2 = p1->previous; // stores the previous pointer of pivot ( used for connecting subarrays )
		i = p1->next; //traverses till we get next pivot ( 'i' acts as partition pointer)
		i1 = j1 = p1; //i1 is pointer before "i"
		i2 = i->next; //i2 is pointer after "i"
		j2 = p1->next->next;
		//example if list is 4,3,5,2,1,6 - for loop gets elements smaller than '4' to left of 'i'(partition) - 4,3,2,1,5,6 (i is '5') 
		for (j = p1->next; j != p2->next; j = j->next)
		{
			if (j->value < p1->value)
			{
				if (i == j)
				{
					i1 = i1->next;
					i = i->next;
					if (i != NULL)
					{
						i2 = i->next;
					}
				}
				else if ((i == j1) && (j->next != NULL))
				{
					i1->next = j;
					j->previous = i1;
					j->next = j1;
					j1->previous = j;
					j1->next = j2;
					j2->previous = j1;

					temp = j1;
					j1 = j;
					j = temp;

					i1 = i1->next;
					i2 = i->next;
				}
				else
				{
					if ((j->next == NULL) && (p1->previous == NULL) && (i1 == p1))
					{
						j->next = i;
						i->previous = j;
						j->previous = i1;
						i1->next = j;
						j1->next = NULL;
						i1 = i1->next;

					}
					else if ((j->next == NULL) && (p1->previous == NULL))
					{
						j->next = i;
						i->previous = j;
						j->previous = i1;
						i1->next = j;
						j1->next = NULL;
						i1 = i1->next;
					}
					else if ((p1->previous != NULL) && (j->next == NULL))
					{
						i1->next = j;
						j->previous = i1;
						j->next = i;
						i->previous = j;
						j = j1;
						j->next = NULL;
						i1 = i1->next;
					}
					else
					{
						i1->next = j;
						j->previous = i1;
						j->next = i2;
						i2->previous = j;

						j1->next = i;
						i->previous = j1;
						i->next = j2;
						j2->previous = i;

						temp = i;
						i = j;
						j = temp;

						i1 = i1->next;
						i = i->next;
						i2 = i2->next;
					}
				}
			}
			j1 = j1->next;
			if (j2 == NULL)
			{
				break;
			}
			j2 = j2->next;
		}

		//swapping pivot to its appropriate position i.e. previous of 'i'
		if ((p1->previous == NULL) && (p1->next == i1))
		{
			p1->next = i;
			i->previous = p1;
			i1->next = p1;
			p1->previous = i1;
			p1 = i1;
			p1->previous = NULL;
		}
		else if ((p1->previous == NULL) && (i1 != p1))
		{
			i1->previous->next = p1;
			i1->next = p1->next;
			p1->next->previous = i1;
			p1->previous = i1->previous;

			if (i != NULL)
			{
				p1->next = i;
				i->previous = p1;
			}
			else
			{
				p1->next = NULL;
				i = p1;
			}
			p1 = i1;
			p1->previous = NULL;
		}

		else if ((p1->next == i1) && (i1->next == NULL))
		{
			temp2->next = i1;
			i1->previous = temp2;
			i1->next = p1;
			p1->previous = i1;
			p1->next = NULL;
			i = p1;
			p1 = i1;
		}
		else if (i1 != p1)
		{
			temp2->next = i1;
			i1->previous->next = p1;
			p1->previous = i1->previous;
			i1->next = p1->next;
			p1->next->previous = i1;
			i1->previous = temp2;
			p1->next = i;
			if (i != NULL)
			{
				i->previous = p1;
			}
			else
			{
				i = i1;
			}
			p1 = i1;
		}
		//recursive calling of 1st and 2nd sub linked list
		sort(p1, i->previous);
		sort(i, p2);
	}
	//to set the head pointer
	while (head->previous != NULL)
	{
		head = head->previous;
	}
	//to set the tail pointer
	while (tail->next != NULL)
	{
		tail = tail->next;
	}
}

int main() {
	doubly_linked_list d1;
	d1.make_random_list(50, 20);
	d1.print_forward();
	d1.print_backward();

	d1.sort(d1.head, d1.tail);
	d1.print_forward();
	d1.print_backward();


	getchar();
	getchar();
	return 0;
}