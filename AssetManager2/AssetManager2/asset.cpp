#include "asset.h"
#include"date.h"
#include"custodian.h"
#include<vector>
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

void Asset::setDisposalDate(Date disposalDate) {
	_disposalDate = disposalDate;
}

// TODO: finish the implementation of the Asset constructor.
Asset::Asset(const std::string &id, const std::string &brand, const std::string &model,
             double purchasePrice, const Date &purchaseDate)
	: _id{ id }, _brand{ brand }, _model{ model }, _purchasePrice{ purchasePrice }, 
	  _purchaseDate{purchaseDate} {
	_disopse = false;
}

Asset::Asset(const std::string &id, const std::string &brand, const std::string &model,
	double purchasePrice, const Date &purchaseDate,const std::string &serial)
	: _id{ id }, _brand{ brand }, _model{ model }, _purchasePrice{ purchasePrice },
	_purchaseDate{ purchaseDate }, _serial{serial} {
	_disopse = false;
}

double Asset::calculateDepreciation(const Date &date) {
	int daysHeld = date.differenceInDays(_purchaseDate);
	double depreciation = _purchasePrice*(daysHeld / 365.0) / _effectiveLifespan;
	return (depreciation >0 ? depreciation:0);
}

void Asset::setMaintenanceRecord(Date timeStamp, std::string maintenancePerson) {
	MaintenanceRecord maintenancerecord(timeStamp, maintenancePerson);
	_maintenanceRecord.push_back(maintenancerecord);
}

const int &Asset::assetType() const {
	return _assetType;
}

const std::string &Asset::serial() const {
	return _serial;
}

const std::vector<MaintenanceRecord> &Asset::getMaintenanceRecord() const {
	return _maintenanceRecord;
}

const bool Asset::getDispose() const {
	return _disopse;
}

void Asset::setDispose(bool isDispose) {
	_disopse = isDispose;
}

const Custodian &Asset::custodian() const {
	return _custodian;
}

void Asset::setCustodian(Custodian& custodian) {
	_custodian = custodian;
}
