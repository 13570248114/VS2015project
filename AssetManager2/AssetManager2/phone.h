#ifndef PHONE_H
#define PHONE_H
#include "asset.h"
#include "custodian.h"
#include<string>

class Phone:public Asset{
public:
	Phone(const std::string &id, const std::string &brand, const std::string &model,
		  const double purchasePrice, const Date &purchaseDate, const std::string &serial,
		  const std::string &operatingSystem, const std::string &phoneNumber,
		  const std::string &billingIdentifier);
	const std::string &operatingSystem() const;
	const std::string &phoneNumber() const;
	const std::string &billingIdentifier() const;
private:
	std::string _operatingSystem;
	std::string _phoneNumber;
	std::string _billingIdentifier;
};
#endif // !PHONE_H

