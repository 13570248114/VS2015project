#include "computer.h"

Computer::Computer(const std::string &id, const std::string &brand, const std::string &model,
                   double purchasePrice, const Date &purchaseDate, const std::string &serial,
                   const std::string &operatingSystem)
    : Asset(id, brand, model, purchasePrice, purchaseDate) {
	_serial = serial;
	

}
