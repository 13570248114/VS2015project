#include"television.h"

Television::Television(const std::string &id, const std::string &brand, const std::string &model,
	const double purchasePrice, const Date &purchaseDate, const std::string &serial,
	const std::string &location)
	: Asset(id, brand, model, purchasePrice, purchaseDate, serial), _location(location) {
	_assetType = 3;
	_effectiveLifespan = 6;
}

const std::string &Television::location() const {
	return _location;
}