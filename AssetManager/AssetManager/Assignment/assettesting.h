#ifndef ASSETTESTING_H
#define ASSETTESTING_H
#include "asset.h"
#include "testingsetting.h"
#include <memory>
#include <ostream>
#include <random>
#include <sstream>

/* DO NOT edit this file, final testing will run on an unmodified version of this file
*/
#define TESTING_TELEVISION TEST_TELEVISION
#if TEST_CUSTODIAN
#define TESTING_CUSTODIAN 1
#define TESTING_COMPUTER TEST_COMPUTER
#define TESTING_PHONE TEST_PHONE
#define TESTING_HMD TEST_HMD
#else
#define TESTING_CUSTODIAN 0
#define TESTING_COMPUTER 0
#define TESTING_PHONE 0
#define TESTING_HMD 0
#endif

class ConcreteAsset;

// Forward declare asset types
class Computer;
class Phone;
class Television;
class HMD;
class Custodian;

/**
 * @brief The AssetTesting class contains a suite of unit tests for the asset types.
 * The tests cover correct operation from constructors, accessors and, where appropriate, mutators.
 * If you have compilation trouble, add a virtual destructor to your Asset class declaration
 * ( virtual ~Asset(){} )
 */
class AssetTesting {
public:
  AssetTesting();
  ~AssetTesting();
  void initialize();
  std::string testDate();
  std::string testAsset();
  std::string testComputer();
  std::string testPhone();
  std::string testTelevision();
  std::string testHMD();
  std::string testCustodian();

  void printFailures(std::ostream &ostream);

private:
  std::stringstream _failMessages;
  std::mt19937 _randomEngine;
  std::uniform_int_distribution<time_t> *_dateDistribution;
  // Used for storing generated parameters
  std::shared_ptr<ConcreteAsset> _asset;
  static const double s_maxEpsilon;
  static const char *s_validCharacters;

  std::string generateSerialNumber();
  std::string generateAssetId();
  void prepareRandomDateGenerator();
  Date generateRandomDate();
  char randomCharacter();
  void generateAssetDetails(double price, Date purchaseDate);
  std::shared_ptr<Custodian> generateCustodian();

  std::shared_ptr<Computer> generateComputer(std::string &os, bool laptop = false,
                                             double price = 0.0, Date purchaseDate = Date());
  std::shared_ptr<Phone> generatePhone(std::string &os, std::string &billingId,
                                       std::string &phoneNumber, double price = 0.0,
                                       Date purchaseDate = Date());
  std::shared_ptr<Television> generateTelevision(std::string &location, double price = 0.0,
                                                 Date purchaseDate = Date());
  std::shared_ptr<HMD> generateHMD(double price = 0.0, Date purchaseDate = Date());

  template <class T> bool validateAsset(std::shared_ptr<Asset> asset, const std::string &type) {
    std::shared_ptr<T> ownAsset = std::dynamic_pointer_cast<T>(asset);
    if (ownAsset == nullptr) {
      _failMessages << "Downcasting error" << std::endl;
      return false;
    }
    return validateAsset(ownAsset, _asset->id(), _asset->brand(), _asset->model(),
                         _asset->purchasePrice(), _asset->purchaseDate(), type);
  }
  template <class T>
  bool validateAsset(std::shared_ptr<T> asset, const std::string &id, const std::string &brand,
                     const std::string &model, double purchasePrice, const Date &purchaseDate,
                     const std::string &type) {
    bool failure = false;
    if (asset->id() != id) {
      _failMessages << type << " ->id() does not match constructor argument." << std::endl;
      failure = true;
    }
    if (asset->brand() != brand) {
      _failMessages << type << " ->brand() does not match constructor argument." << std::endl;
      failure = true;
    }
    if (asset->model() != model) {
      _failMessages << type << " ->model() does not match constructor argument." << std::endl;
      failure = true;
    }
    if (asset->purchasePrice() != purchasePrice) {
      _failMessages << type << " ->price() does not match constructor argument." << std::endl;
      failure = true;
    }
    if (asset->purchaseDate() != purchaseDate) {
      _failMessages << type << " ->purchaseDate() does not match constructor argument."
                    << std::endl;
      failure = true;
    }
    // Test disposal
    if (asset->disposalDate().valid()) {
      _failMessages << type << " ->disposalDate() has a valid date, before being disposed."
                    << std::endl;
      failure = true;
    }
    Date disposeDate(1, Date::January, 2018);
    asset->dispose(disposeDate);
    if (!asset->disposalDate().valid() || !(asset->disposalDate() == disposeDate)) {
      _failMessages << type
                    << " ->disposalDate() does not match date argument passed to ->dispose()."
                    << std::endl;
      failure = true;
    }
    return !failure;
  }

  template <class T> bool testAssetCustodian(std::shared_ptr<T> asset, const std::string &type) {
    bool failure = false;
    std::shared_ptr<Custodian> cust = generateCustodian();
    asset->setCustodian(cust);
    std::shared_ptr<Custodian> set = asset->custodian();
    if (set != cust) {
      _failMessages << type << " unable to verify set custodian." << std::endl;
      failure = true;
    }
    // Remove custodian from asset
    asset->setCustodian(nullptr);
    if (asset->custodian() != nullptr) {
      _failMessages << type << " unable to set no custodian." << std::endl;
      failure = true;
    }
    return !failure;
  }

  bool testDeprecation(const std::string &type);
};

#endif // ASSETTESTING_H
