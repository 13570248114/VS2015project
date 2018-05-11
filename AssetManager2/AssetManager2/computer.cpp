#include "computer.h"

Computer::Computer(const std::string &id, const std::string &brand, const std::string &model,
                   const double purchasePrice, const Date &purchaseDate, const std::string &serial,
                   const std::string &operatingSystem)
    : Asset(id, brand, model, purchasePrice, purchaseDate,serial),
	  _operatingSystem(operatingSystem) , _networkIdentifier("undefined"){
	_assetType = 1;
	_effectiveLifespan=3;
}

Computer::Computer(const std::string &id, const std::string &brand, const std::string &model,
	               const double purchasePrice, const Date &purchaseDate, const std::string &serial,
	               const std::string &operatingSystem, const std::string &networkIdentifier) 
	 : Asset(id, brand, model, purchasePrice, purchaseDate,serial),
	   _operatingSystem(operatingSystem), _networkIdentifier(networkIdentifier){
	_assetType = 1;
	_effectiveLifespan = 3;
}


const std::string &Computer::operatingSystem() const {
	return _operatingSystem;
}

const std::string &Computer::networkIdentifier() const {
	return _networkIdentifier;
}

