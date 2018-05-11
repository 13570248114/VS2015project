#ifndef COMPUTER_H
#define COMPUTER_H
#include "asset.h"
#include "custodian.h"

/**
 * @brief The Computer class represents a computer in the asset register
 */
class Computer : public Asset {
public:
  Computer(const std::string &id, const std::string &brand, const std::string &model,
           double purchasePrice, const Date &purchaseDate, const std::string &serial,
           const std::string &operatingSystem);
  Computer(const std::string &id, const std::string &brand, const std::string &model,
	       double purchasePrice, const Date &purchaseDate, const std::string &serial,
	       const std::string &operatingSystem, const std::string &networkIdentifier);
  // TODO: fix the return types of these accessor member functions
  
  const std::string &operatingSystem() const;
  const std::string &networkIdentifier() const;

  // TODO: Finish implementation of this class.
private:
	std::string _operatingSystem;
	std::string _networkIdentifier;
};

#endif // COMPUTER_H
