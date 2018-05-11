#ifndef HMD_H
#define HMD_H
#include<string>
#include"asset.h"
#include"custodian.h"

class HMD :public Asset {
public:
	HMD(const std::string &id, const std::string &brand, const std::string &model,
		double purchasePrice, const Date &purchaseDate, const std::string &serial,
		const Custodian &custodian);
	const Custodian &custodian() const;
private:
	Custodian _custodian;
};
#endif // !HMD_H
