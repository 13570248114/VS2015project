#include"HMD.h"

HMD::HMD(const std::string &id, const std::string &brand, const std::string &model,
	     double purchasePrice, const Date &purchaseDate, const std::string &serial,
	     const Custodian &custodian)
	     :Asset(id, brand, model, purchasePrice, purchaseDate,serial),
	      _custodian(custodian) {
}


const Custodian &HMD::custodian() const {
	return _custodian;
}