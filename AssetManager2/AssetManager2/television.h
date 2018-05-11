#ifndef TELEVISION_H
#define TELEVISION_H
#include<string>
#include"asset.h"
#include"custodian.h"

class Television : public Asset {
public:
	Television(const std::string &id, const std::string &brand, const std::string &model,
		       const double purchasePrice, const Date &purchaseDate, const std::string &serial,
		       const std::string &location);
	const std::string &location() const;
private:
	std::string _location;
};

#endif // !TELEVISION_H

