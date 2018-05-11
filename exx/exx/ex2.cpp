#include <iostream>
#include <stdlib.h>
#include <stdexcept>
#include <vector>
#include <string>
#include <algorithm>
#include "Student.h"
#include "ReadWords.h"
#include "ReadFilteredWords.h"
using namespace std;

bool comp(const Student &a, const Student &b) {

	return a.getRegNo() < b.getRegNo();
}

//display all the student info which has a no less module mark then mark
void additional_function1(vector<Student> StudentList, float mark) {
	
	vector<Student>::iterator it;
	int counter = 0;

	sort(StudentList.begin(), StudentList.end(), comp);

	it = StudentList.begin();
	for (; it != StudentList.end(); it++){
		
		try{
			if ( it->maximum() >= mark ) {

				cout << (*it);
				counter ++;
				continue;
			}
		}
		catch (NoMarkException) {
		}
	}

	if(counter == 0) { 
		cout << "No such student found!" << endl;
	}
}

// print on the screen the name and mark for student
// who has a mark for that module
void additional_function2(vector<Student> StudentList, string module, float mark) {
	
	int counter = 0;
	vector<Student>::iterator it;
	float module_mark = 0;

	sort(StudentList.begin(), StudentList.end(), comp);

	it = StudentList.begin();
	for (; it != StudentList.end(); it++){
		
		try{
				module_mark = it->getMark(module);
				counter ++;
				cout << it->getName() << " " << module_mark << endl; 
				continue;
		}
		catch (NoMarkException) {
		}
	}

	if(counter == 0) { 
		cout << "No such student found!" << endl;
	}

}


int main()
{
	vector<Student> StudentList;
	vector<Student>::iterator it;

	//string filename;
	char student_filename[] = "studs.txt";
	char mark_filename[] = "marks.txt";

	ReadFilteredWords reader(student_filename);

	while ( reader.isNextWord() ) {
		int regNo = atoi(reader.getNextWord().c_str());
		string name  = reader.getNextWord() + " " + reader.getNextWord();
		Student * s = new Student(name,regNo);
		//cout << s->getName() << " " << s->getRegNo() << endl;
		StudentList.push_back(*s);
	}

	ReadFilteredWords mark_reader(mark_filename);

	while ( mark_reader.isNextWord() ) {
		int regNo = atoi(mark_reader.getNextWord().c_str());
		it = StudentList.begin();
		for (; it != StudentList.end(); it++){
			if ( it->getRegNo() == regNo ) {
				string module = mark_reader.getNextWord();
				float mark = atof(mark_reader.getNextWord().c_str());
				it->addMark(module, mark);

				break;
			}
		}	
		if(it == StudentList.end()){
			cout << "Warning: no student with regNo " << regNo << " found!" << endl;
		}
	}

	//display all details of the students and their marks
	it = StudentList.begin();
	/*for (; it != StudentList.end(); it++){
		it->display();	
		cout << endl;
	}*/

	//for test the additional functions
	float mark = 0;
	string module = "CE151";
	additional_function2(StudentList, module, mark);
	
	int choice = 1;
	while(choice == 1 || choice == 2){
		cout << "Please input your choice: " << endl;
		cout << "1. test the first function. " << endl;
		cout << "2. test the second function. " << endl;
		cout << "3. quit. " << endl;
		cin >> choice;
		if ( choice == 1){
			cout << "please input the mark: " << endl;
			cin >> mark;
			cout << "The search result:" << endl;
			additional_function1(StudentList, mark);
		}
		else if ( choice == 1){
			cout << "please input the module: " << endl;
			cin >> module;
			cout << "The search result:" << endl;
			additional_function2(StudentList, module, mark);
		}
	}



}
