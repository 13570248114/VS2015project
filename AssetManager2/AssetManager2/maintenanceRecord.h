#ifndef MAINTENANCERECORD_H
#define MAINTENANCERECORD_H

#include"date.h"
#include<string>

class MaintenanceRecord {
public:
	MaintenanceRecord(const Date &timeStamp, const std::string &maintenancePersonName);
	MaintenanceRecord();
	const Date &timeStamp() const;
	const std::string &maintenancePersonName() const;
	void setMaintenanceRecord(Date timeStamp, std::string maintenancePerson);
	
private:
	Date _timeStamp;
	std::string _maintenancePersonName;
};
#endif // !MAINTENANCERECORD_H

