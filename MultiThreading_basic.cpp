//CIS554 HW6
//Name - Anish Nesarkar
//Email - anesarka@syr.edu
//SUID - 368122582
#include <iostream>
#include <thread>
#include <fstream>

using namespace std;

class node {
public:
	int value;
	node * next;
	node() { next = nullptr; }
	node(int i) {
		value = i; next = nullptr;
	}
};

class linked_list {
public:
	int num_nodes;
	node * head;
	linked_list() { num_nodes = 0; head = nullptr; }
	void make_list(int m, int n) {
		for (int i = 0; i < m; i++) {
			node * p = new node(rand() % n);
			p->next = head;
			head = p;
		}
		num_nodes = m;
	}
};

void merge(linked_list & L, node * p1, int n1, node * p2, int n2);
void sort(linked_list & L, node * p, int n);//using merge_sort to n nodes of L, with					   //first nodes pointed by p



//For the sort and merge, you can change both node values and pointers.
//Your implementation has to be an in-place sorting -- no external data structures are allowed

int main() {
	linked_list L;
	L.make_list(10000, 1500);
	//sort(L, L.head, L.num_nodes);

	//Create 4 threads to speed up the merge sort.
	//Implement the sort and merge funcitons
	//Write the sorted results to HW6data.txt

	//output file
	ofstream HW6data;
	HW6data.open("HW6data.txt");

	//head node for thread 1 sort
	node *hs1 = L.head;
	int numofNodes = (L.num_nodes / 4);
	
	//head node for thread 2 sort
	node *hs2 = hs1;
	for (int i = 0; i < numofNodes; i++)
		hs2 = hs2->next;

	//head node for thread 3 sort
	node *hs3 = hs2;
	for (int i = 0; i < numofNodes; i++)
		hs3 = hs3->next;

	//head node for thread 4 sort
	node *hs4 = hs3;
	for (int i = 0; i < numofNodes; i++)
		hs4 = hs4->next;

	//if number of nodes are less than 4
	if (L.num_nodes >= 0 && L.num_nodes < 4)
	{
		thread t1(sort, ref(L), L.head, L.num_nodes);
		t1.join();
	}
	else
	{
		//Threading sort function
		thread t1(sort, ref(L), hs1, numofNodes);
		t1.join();
		thread t2(sort, ref(L), hs2, numofNodes);
		t2.join();
		thread t3(sort, ref(L), hs3, numofNodes);
		t3.join();
		thread t4(sort, ref(L), hs4, numofNodes);
		t4.join();
		//

		
		
		
		


		//head nodes for merging
		node *hm1 = L.head;

		node *hm2 = hm1;
		for (int i = 0; i < numofNodes; i++)
			hm2 = hm2->next;

		node *hm3 = hm2;
		for (int i = 0; i < numofNodes; i++)
			hm3 = hm3->next;

		node *hm4 = hm3;
		for (int i = 0; i < numofNodes; i++)
			hm4 = hm4->next;


		//merge sorted nodes

		merge(L, hm1, numofNodes, hm2, numofNodes);
		merge(L, hm3, numofNodes, hm4, numofNodes);
		merge(L, hm1, numofNodes * 2, hm3, numofNodes * 2);
	}

	//Write the sorted results to HW6data.txt
	node *output = L.head;
	for (; output != NULL; output = output->next)
	{
		HW6data << output->value << " ";
	}
	HW6data.close();


	getchar();
	getchar();
	return 0;
}


////Sort
void sort(linked_list & L, node * p, int n)
{
	int n1 = 0, n2 = 0;
	node *h1 = NULL;
	node *h2 = p;

	if (n > 1)
	{
		for (int i = 0; i < (n / 2); i++)
		{
			n1++;
			h1 = h2;
			h2 = h2->next;
		}
		n2 = n - n1;

		h2 = h1->next;
		h1->next = NULL;
		h1 = p;

		sort(L, h1, n1);
		sort(L, h2, n2);
		merge(L, h1, n1, h2, n2);

	}
	else
		return;


}
void merge(linked_list & L, node * p1, int n1, node * p2, int n2)
{
	node *iter = p1;
	node *connect = p1;
	int connectCount = 0;
	while (connectCount < (n1 - 1) && connect->next != NULL)
	{
		connect = connect->next;
		connectCount++;
	}
	node *temp2 = p2;
	int swap;

	for (; (iter != NULL) && (iter != p2); iter = iter->next)
	{
		while (temp2)
		{
			if (iter->value <= temp2->value)
				temp2 = temp2->next;
			else
			{
				swap = iter->value;
				iter->value = temp2->value;
				temp2->value = swap;
				temp2 = temp2->next;
			}
		}
		temp2 = p2;
	}

	iter = p2;
	temp2 = p2->next;
	int count = 0;
	for (; iter != NULL && count < n2 + 2; iter = iter->next, count++)
	{
		while (temp2)
		{
			if (iter->value <= temp2->value)
				temp2 = temp2->next;
			else
			{
				swap = iter->value;
				iter->value = temp2->value;
				temp2->value = swap;
				temp2 = temp2->next;
			}
		}
		temp2 = iter->next;
	}
	connect->next = p2;
}


