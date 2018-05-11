#ifndef CUSTODIAN_H
#define CUSTODIAN_H
#include<string>
#include "date.h"
#include<vector>

class Custodian {
public:
	Custodian(const std::string &name, const std::string &department,
		      const std::string &phoneNumber, const Date &employmentStartDate);
	Custodian();
	const std::string &name() const;
	const std::string &department() const;
	const std::string &phoneNumber() const;
	const Date &employmentStartDate() const;
private:
	std::string _name;
	std::string _department;
	std::string _phoneNumber;
	Date _employmentStartDate;
};
#endif // CUSTODIAN_H
