//CIS554 HW3
//Name - Anish Nesarkar
//Email - anesarka@syr.edu
//SUID - 368122582

#include <iostream>
#include <list>
#include <map>
#include <string>
using namespace std;

class course {
public:
	string name;
	int section;
	int credits;
	course() {}
	course(string n, int s, int c) { name = n; section = s; credits = c; }
	bool const operator==(course &c) 
	{
		return ((name == c.name) && (section == c.section) && (credits == c.credits));
	}
	friend ostream & operator<<(ostream &str, course* &C);
	friend ostream & operator<<(ostream &str, list<course*> &L);
	friend ostream & operator<<(ostream &str, map<int, list<course*>*> &M);
	friend ostream & operator<<(ostream &str, map<int, map<int, list<course*>*>*> &M);
	//Add additional needed member functions and implement them.
	//You also need to implement some needed functions for overloading operator<< .
};
//Implement the following functions

void add_student(map<int, map<int, list<course *> * > *> &DB, int id);
void remove_student(map<int, map<int, list<course *> * > *> &DB, int id);
void add_course(map<int, map<int, list<course *> * > *> &DB, int semester, int id, course c); //20171 Spring semester of 2017; 20172: Fall semester of 2017

void drop_course(map<int, map<int, list<course *> * > *> &DB, int semester, int id, course c);
void print_student_semester_courses(map<int, map<int, list<course *> * > *> &DB, int semester, int id);
void print_student_all_courses(map<int, map<int, list<course *> * > *> &DB, int id);
void print_DB(map<int, map<int, list<course *> * > *> &DB);

//For the print funcitons, you need to add more fucntions to overload operator<<.
//for example print_DB is simply cout << DB;

int main() {
	//Do not change code for main function
	map<int, map<int, list <course *> *> *> DB;
	add_student(DB, 11111);
	course C1("CIS554", 1, 3), C2("CSE674", 1, 3), C3("MAT296", 8, 4), C4("WRT205", 5, 3);

	add_course(DB, 20171, 11111, C1);
	add_course(DB, 20171, 11111, C4);
	add_course(DB, 20171, 11111, C3);
	add_course(DB, 20171, 11111, C2);
	print_student_semester_courses(DB, 20171, 11111);

	drop_course(DB, 20171, 11111, C1);
	print_student_semester_courses(DB, 20171, 11111);

	add_course(DB, 20172, 11111, C2);
	add_course(DB, 20172, 11111, C4);
	add_course(DB, 20172, 11111, C3);
	add_course(DB, 20172, 11111, C1);
	print_student_all_courses(DB, 11111);

	add_student(DB, 11112);
	add_course(DB, 20171, 11112, C2);
	add_course(DB, 20171, 11112, C4);
	add_course(DB, 20171, 11112, C3);
	add_course(DB, 20171, 11112, C1);
	print_student_semester_courses(DB, 20171, 11112);

	add_course(DB, 20172, 11112, C2);
	add_course(DB, 20172, 11112, C4);
	add_course(DB, 20172, 11112, C3);
	add_course(DB, 20172, 11112, C1);
	print_student_semester_courses(DB, 20172, 11112);
	print_student_all_courses(DB, 11112);
	print_DB(DB);
	remove_student(DB, 11111);
	print_DB(DB);
	getchar();
	getchar();
	return 0;
}

void add_student(map<int, map<int, list<course *> * > *> &DB, int id) {
	auto it = DB.find(id);
	if (it == DB.end())
	{
		map<int, list<course*>*> *DBTS = new map<int, list<course *>*>();
		DB.insert(pair<int, map<int, list<course *> * > *>(id, DBTS));
	}
}

void remove_student(map<int, map<int, list<course *> * > *> &DB, int id) {
	auto it = DB.find(id);
	if (it != DB.end())
	{
		auto it1 = it->second->begin(); // semesters
		while (it1 != it->second->end())
		{
			//deleting list
			auto it3 = it1->second->begin();
			while (it3 != it1->second->end())
			{
				//deleting course
					delete *it3;
					it1->second->erase(it3);
					it3 = it1->second->begin();
			}
			delete it1->second;
			it->second->erase(it1);
			it1 = it->second->begin();
		}
		delete DB[id];
		DB.erase(it);
	}
	
	
}

void add_course(map<int, map<int, list<course *> * > *> &DB, int semester, int id, course c) {
	auto it1 = DB.find(id);
	if(it1 != DB.end())
	{
		course *ptr = new course(c);
		list<course *> *clist = new list<course *>();
		clist->push_back(ptr);
		int count = 0;
		auto it2 = it1->second->find(semester);	
		if(it2 != it1->second->end())
		{
			auto it3 = it2->second->begin();
			while(it3 != it2->second->end())
			{
				if (*(*(it3)) == c)
					break;	
				count++;
				it3++;
			}
			if(count == it2->second->size())
				it2->second->push_back(ptr);
		}
		else
			(*(it1->second)).insert(pair<int, list<course *>*>(semester, clist));
	}
}

void drop_course(map<int, map<int, list<course *> * > *> &DB, int semester, int id, course c) {
	auto it = DB.find(id);
	if (it != DB.end())
	{
		auto it1 = it->second->find(semester);
		if (it1 != it->second->end())
		{
			auto it3 = it1->second->begin();
			while (it3 != it1->second->end())
			{
				if (*(*(it3)) == c)
				{
					delete *it3;
					it1->second->erase(it3);
					break;
				}
				it3++;
			}
		}
	}

}


void print_student_semester_courses(map<int, map<int, list<course *> * > *> &DB, int semester, int id) {

	auto it3 = DB.find(id);
	if (it3 != DB.end())
	{
		auto it2 = it3->second->find(semester);
		if (it2 != it3->second->end())
		{
			cout << "student id = " << it3->first << endl << "semester = " << semester << endl << (*(it2->second)) << endl;
		}
		cout << endl;
	}
}

void print_student_all_courses(map<int, map<int, list<course *> * > *> &DB, int id) 
{
	auto it3 = DB.find(id);
	if (it3 != DB.end())
	{
		cout << "student id = " << it3->first << endl;
		auto it2 = it3->second;
		cout << *it2 << endl;
	}
}

void print_DB(map<int, map<int, list<course *> * > *> &DB) 
{	
	cout << DB << endl;
}

//Some additional functions for overloading operator<<

ostream & operator<<(ostream &str, course* &C)
{
	str << C->name << " " << C->section << " " << C->credits << "  ";
	return str;
}

ostream & operator<< (ostream &str, list<course*> &L) {
	auto it1 = L.begin();
	while (it1 != L.end())
	{
		str << *it1;
		it1++;
	}
	return str;
}

ostream & operator<<(ostream &str, map<int, list<course*>*> &M)
{
	auto it2 = M.begin();
	while (it2 != M.end())
	{
		str << "semester = " << it2->first << endl << (*(it2->second)) << endl;
		it2++;
	}
	return str;
}

ostream & operator<<(ostream &str, map<int, map<int, list<course*>*>*> &M)
{
	auto it3 = M.begin();
	while (it3 != M.end())
	{
		auto it2 = it3->second;
		str << "student id = " << it3->first << endl;
		cout << *it2;
		it3++;
	}
	return str;
}


/*
//Your output needs to keep the identical format
//Sample Screenshot
student id = 11111
semester = 20171
CIS554 1 3  WRT205 5 3  MAT296 8 4  CSE674 1 3

student id = 11111
semester = 20171
WRT205 5 3  MAT296 8 4  CSE674 1 3

student id = 11111
semester = 20171
WRT205 5 3  MAT296 8 4  CSE674 1 3
semester = 20172
CSE674 1 3  WRT205 5 3  MAT296 8 4  CIS554 1 3

student id = 11112
semester = 20171
CSE674 1 3  WRT205 5 3  MAT296 8 4  CIS554 1 3

student id = 11112
semester = 20172
CSE674 1 3  WRT205 5 3  MAT296 8 4  CIS554 1 3

student id = 11112
semester = 20171
CSE674 1 3  WRT205 5 3  MAT296 8 4  CIS554 1 3
semester = 20172
CSE674 1 3  WRT205 5 3  MAT296 8 4  CIS554 1 3

student id = 11111
semester = 20171
WRT205 5 3  MAT296 8 4  CSE674 1 3
semester = 20172
CSE674 1 3  WRT205 5 3  MAT296 8 4  CIS554 1 3
student id = 11112
semester = 20171
CSE674 1 3  WRT205 5 3  MAT296 8 4  CIS554 1 3
semester = 20172
CSE674 1 3  WRT205 5 3  MAT296 8 4  CIS554 1 3

student id = 11112
semester = 20171
CSE674 1 3  WRT205 5 3  MAT296 8 4  CIS554 1 3
semester = 20172
CSE674 1 3  WRT205 5 3  MAT296 8 4  CIS554 1 3
*/