#include"phone.h"

Phone::Phone(const std::string &id, const std::string &brand, const std::string &model,
	         const double purchasePrice, const Date &purchaseDate, const std::string &serial,
	         const std::string &operatingSystem, const std::string &phoneNumber,
	         const std::string &billingIdentifier)
	:Asset(id, brand, model, purchasePrice, purchaseDate,serial), _operatingSystem(operatingSystem),
	_phoneNumber(phoneNumber), _billingIdentifier(billingIdentifier) {
	_assetType = 2;
	_effectiveLifespan = 2;
}

const std::string &Phone::operatingSystem() const {
	return _operatingSystem;
}

const std::string &Phone::phoneNumber() const {
	return _phoneNumber;
}

const std::string &Phone::billingIdentifier() const {
	return _billingIdentifier;
}

