#include"maintenanceRecord.h"

MaintenanceRecord::MaintenanceRecord(const Date &timeStamp, const std::string &maintenancePersonName)
	:_timeStamp(timeStamp), _maintenancePersonName(maintenancePersonName) {

}

MaintenanceRecord::MaintenanceRecord() {
	_maintenancePersonName = "undefined";
	_timeStamp.getCurrentDate();
}

const Date &MaintenanceRecord::timeStamp() const {
	return _timeStamp;
}

const std::string &MaintenanceRecord::maintenancePersonName() const {
	return _maintenancePersonName;
}

void MaintenanceRecord::setMaintenanceRecord(Date timeStamp, std::string maintenancePerson) {
	_timeStamp = timeStamp;
	_maintenancePersonName = maintenancePerson;
}