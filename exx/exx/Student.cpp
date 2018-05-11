#include "Student.h"
#include <string>
#include <iostream>
using namespace std;

// method to initialize Student
Student::Student(const string &name, int regNo) : Person(name) {
	this->regNo = regNo;
}

// method to return registration number
int Student::getRegNo() const {
	return this->regNo;   
}

// method to add the mark to the map
// if a mark for the module is already present it should be overwritten
void Student::addMark(const string& module, float mark) {
	map<string, float>::iterator it = marks.find(module);
	if (it==marks.end()){
		marks.insert(make_pair(module,mark));
	}
	else
		it->second = mark;
}

// method to retrieve the mark for a module
// should throw NoMarkException if student has no mark for that module
float Student::getMark(const string &module) throw (NoMarkException) {

	NoMarkException ne;
	map<string, float>::iterator it = marks.find(module);
	if(it==marks.end())
		throw (ne);
		
	return it -> second;
}

// method to calculate the average score of the student
float Student::getAverageMark() throw (NoMarkException) {

	float sum = 0;
	int num = 0;
	NoMarkException ne;
	map<string, float>::iterator it = marks.begin();

	if(it == marks.end())
		throw (ne);

	for( ; it != marks.end(); it++ ){
			
		sum += it->second;
		num ++;
	}

	return sum / num;
}

float Student::minimum() throw (NoMarkException) {

	float min = 0;
	NoMarkException ne;
	map<string, float>::iterator it = marks.begin();

	if(it == marks.end())
		throw (ne);

	for( ; it != marks.end(); it++ ){
			
		if( it->second < min )
			min = it->second;
	}

	return min;
}


float Student::maximum() throw (NoMarkException) {

	float max = 0;
	NoMarkException ne;
	map<string, float>::iterator it = marks.begin();

	if(it == marks.end())
		throw (ne);

	for( ; it != marks.end(); it++ ){
			
		if( it->second > max )
			max = it->second;
	}

	return max;
}

string Student::getName() const {
	return name;
}

    //private:
	//   int regNo;
	//   map<string, float> marks;  // keys are modules, values are marks in range 0.0 to 100.0

    // friend function to output details of student to stream
    // should output name, regno, and minimum, maximum and average marks on a single line
    // if the student has no marks "has no marks" should be output instead of the marks
    ostream& operator<<(ostream &str, Student &s){
		str << s.getName() << " " << s.getRegNo() << " ";
	    try{
			s.getAverageMark();
			str	<< s.minimum() << " "
		    << s.maximum() << " "
			<< s.getAverageMark() << "\n";
		}
		catch(NoMarkException){
			str << "has no marks\n";
		}
		return str;
	}

//show info message and all the marks of a student
void Student::display() {
	cout << getName() << " " << getRegNo() << endl;
	map<string, float>::iterator it = marks.begin();

	if ( it == marks.end() ){
		cout << "has no marks" << endl;
	}

	for( ; it != marks.end(); it++ ){
			
		cout << it->first << " " << it->second << endl;
	}
}


//};

//#endif
