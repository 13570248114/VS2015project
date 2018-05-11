#include "asset.h"
#include"date.h"
#include <ctime>

const std::string &Asset::id() const {
  return _id;
}

const Date &Asset::purchaseDate() const {
  return _purchaseDate;
}

const Date &Asset::disposalDate() const {
	return _disposalDate;
}

const std::string &Asset::brand() const {
	return _brand;
}

const std::string &Asset::model() const {
	return _model;
}

const double &Asset::purchasePrice() const {
	return _purchasePrice;
}

// TODO: finish the implementation of the Asset constructor.
Asset::Asset(const std::string &id, const std::string &brand, const std::string &model,
             double purchasePrice, const Date &purchaseDate)
	: _id{ id }, _brand{ brand }, _model{ model }, _purchasePrice{ purchasePrice }, 
	  _purchaseDate{purchaseDate} {
}

double Asset::calculateDepreciation(const Date &date) {
	time_t tt = time(NULL);
	tm* t = localtime(&tt);
	Date::Month month = (Date::Month)t->tm_mon;
	Date currentTime(t->tm_mday, month ,t->tm_year + 1900 );
	int daysHeld = currentTime.differenceInDays(_purchaseDate);
	double depreciation = _purchasePrice*(daysHeld / 365) / _effectiveLifespan;
	return depreciation;
}
