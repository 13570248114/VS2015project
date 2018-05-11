#include"custodian.h"
#include "date.h"

const std::string &Custodian::name() const{
	return _name;
}

const std::string &Custodian::department() const {
	return _department;
}

const std::string &Custodian::phoneNumber() const {
	return _phoneNumber;
}
const Date &Custodian::employmentStartDate() const {
	return _employmentStartDate;
}

Custodian::Custodian(const std::string &name, const std::string &department,
	                 const std::string &phoneNumber, const Date &employmentStartDate)
	                 :_name(name), _department(department), _phoneNumber(phoneNumber),
	                  _employmentStartDate(employmentStartDate){
}


Custodian::Custodian() {
	_name = "undefined";
	_department = "undefined";
	_phoneNumber = "undefined";
	_employmentStartDate.getCurrentDate();
}


