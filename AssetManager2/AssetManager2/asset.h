#ifndef ASSET_H
#define ASSET_H
#include "date.h"
#include <string>
#include<vector>
#include"custodian.h"
#include"maintenanceRecord.h"

/**
 * @brief The Asset class the abstract base class for an asset in the asset register.
 */
class Asset {
public:
  /**
   * @brief id retrieve the unique identifier for this asset.
   * @return the unique identifier
   */
  const std::string &id() const;
  /**
   * @brief purchaseDate
   * @return the date on which this asset was purchased.
   */
  const Date &purchaseDate() const;

  // TODO: fix return types of these accessor member functions
  virtual const Date &disposalDate() const;
  virtual const std::string &brand() const;
  virtual const std::string &model() const;
  virtual const double &purchasePrice() const;
  virtual void setDisposalDate(Date disposalDate);
  virtual void setMaintenanceRecord(Date timeStamp, std::string maintenancePerson);
  virtual const int &assetType() const;
  virtual const std::string &serial() const;
  virtual double calculateDepreciation(const Date &date);
  virtual const std::vector<MaintenanceRecord> &getMaintenanceRecord() const;
  virtual const bool getDispose() const;
  virtual void setDispose(bool isDisposed);
  virtual const Custodian &custodian() const;
  virtual void setCustodian(Custodian& custodian);

protected:
  /**
   * @brief Asset constructor for the base class asset
   * @param id the unique identifier for this asset
   * @param brand
   * @param model
   * @param purchasePrice
   * @param purchaseDate
   */
  int _assetType;
  double _effectiveLifespan;
  Asset(const std::string &id, const std::string &brand, const std::string &model,
        const double purchasePrice, const Date &purchaseDate);
  Asset(const std::string &id, const std::string &brand, const std::string &model,
	  double purchasePrice, const Date &purchaseDate, const std::string &serial);
  
private:
  std::string _id;    /**< a unique identifier for the asset */
  Date _purchaseDate; /**< the date on which the asset was purchased */
  std::string _brand;
  std::string _model;
  double _purchasePrice;
  Date _disposalDate;
  std::vector<MaintenanceRecord> _maintenanceRecord;
  std::string _serial;
  bool _disopse;
  Custodian _custodian;
};

#endif // ASSET_H
