#include "menuinterface.h"
#include "assetregister.h"
#include"custodian.h"
#include"computer.h"
#include"phone.h"
#include <limits>
#include"assetregister.h"
#include"television.h"


MenuInterface::MenuInterface(std::ostream &display, std::istream &input)
    : _display{display}, _input{input} {
}

void MenuInterface::displayMainMenu() const {
  _display << "What would you like to do?" << std::endl;
  _display << " (a)dd an asset" << std::endl;
  _display << " (d)ispose an asset" << std::endl;
  _display << " (u)pdate asset custodian or location" << std::endl;
  _display << "  add asset (m)aintenance record" << std::endl;
  _display << " (l)ist assets by type" << std::endl;
  _display << "  List assets by (c)ustodian" << std::endl;
  _display << " (f)ind asset" << std::endl;
  _display << " (q)uit" << std::endl;
}

char MenuInterface::getCharacterInput() const {
  char input;
  _input >> input;
  _input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  return input;
}

bool MenuInterface::processSelection(char selection) {
  switch (selection) {
  case 'a':
    addAsset();
    break;
  case 'd':
    disposeAsset();
    break;
  case 'u':
	updateAsset();
	break;
  case 'm':
	  addMaintenance();
	  break;
  case 'l':
    listAssetsByType();
    break;
  case 'c':
    listAssetsByCustodian();
    break;
  case 'f':
    findAsset();
    break;
  case 'q':
    return false;
  default:
    _display << "Sorry, \'" << selection << "\' is not a valid option, please try again."
             << std::endl;
  }
  return true;
}



void MenuInterface::addAsset() {
	// TODO: implement this member function.
	_display << "Add an asset" << std::endl;
	_display << " add a (c)omputer" << std::endl;
	_display << " add a (p)hone" << std::endl;
	_display << " add a (t)elevision" << std::endl;
	_display << " (b)ack to main menu" << std::endl;
	AssetRegister &am = AssetRegister::instance();
	char selection = getCharacterInput();
	switch (selection){
	    case 'c':{
			bool rewrite=false;
			std::string id, brand, model, serial, operatingSystem, networkIdentifier;
			Date purchaseDate;
			Custodian custodian;
			double purchasePrice;
			do {
				_display << "please input the message of a computer:" << std::endl;
				_display << "id: brand: model: purchasePrice: serial: operatingSystem: networkIdentifier: " << std::endl;
				_input >> id >> brand >> model >> purchasePrice >> serial >> operatingSystem >> networkIdentifier;
				_display << "purchase date:" << std::endl;
				purchaseDate = inputDate();
				_display << "all message of computer have been input,do you want to cancel and modify?" << std::endl;
				_display << "input 0 to cancel ,input 1 to store the computer" << std::endl;
				_input >> rewrite;
			} while (!rewrite);
			am.storeAsset(std::make_shared<Computer>(id, brand, model, purchasePrice, purchaseDate, serial, 
				           operatingSystem, networkIdentifier));
			break;
	    }
		case 'p':{
			bool rewrite = false;
			std::string id, brand, model, serial, operatingSystem, phoneNumber, billingIdentifier;
			double purchasePrice;
			Date purchaseDate;
			do {
				_display << "please input the message of a phone:" << std::endl;
				_display << "id: brand: model: purchasePrice: serial: operatingSystem: phoneNumber: billingIdentifier:" << std::endl;
				_input >> id >> brand >> model >> purchasePrice >> serial >> operatingSystem >> phoneNumber >> billingIdentifier;
				_display << "purchase date:" << std::endl;
				purchaseDate = inputDate();
				_display << "all message of computer have been input,do you want to cancel and modify?" << std::endl;
				_display << "input 0 to cancel ,input 1 to store the phone" << std::endl;
				_input >> rewrite;
			} while (!rewrite);
			am.storeAsset(std::make_shared<Phone>(id, brand, model, purchasePrice, purchaseDate, serial,
				operatingSystem, billingIdentifier,phoneNumber));
			break;
		}
		case 't': {
			bool rewrite = false;
			std::string id, brand, model, serial, location;
			double purchasePrice;
			Date purchaseDate;
			do {
				_display << "please input the message of a television:" << std::endl;
				_display << "id: brand: model: purchasePrice: serial: location" << std::endl;
				_input >> id >> brand >> model >> purchasePrice >> serial >> location;
				_display << "purchase date:" << std::endl;
				purchaseDate = inputDate();
				_display << "all message of computer have been input,do you want to cancel and modify?" << std::endl;
				_display << "input 0 to cancel ,input 1 to store the television" << std::endl;
				_input >> rewrite;
			} while (!rewrite);
			am.storeAsset(std::make_shared<Television>(id, brand, model, purchasePrice, purchaseDate, serial,
				location));
			break;
		}
		case 'b': {
			displayMainMenu();
			break;
		}
		default:
			_display << "Sorry, \'" << selection << "\' is not a valid option, please try again."
				     << std::endl;
	}
}

void MenuInterface::disposeAsset() {
  // TODO: implement this member function.
	std::shared_ptr<Asset> asset = retrieveAsset();
	Date currentDate;
	currentDate.getCurrentDate();
	if (asset != nullptr) {
		asset->setDisposalDate(currentDate);
		asset->setDispose(true);
	}
}

void MenuInterface::updateAsset() {
  // TODO: implement this member function.
	std::shared_ptr<Asset> asset = retrieveAsset();
	Custodian custodian = inputCustodian();
	asset->setCustodian(custodian);
	AssetRegister &am = AssetRegister::instance();
	am.stortCustodianMap(custodian.name(), asset->id());
}

void MenuInterface::addMaintenance() {
  // TODO: implement this member function.
	std::shared_ptr<Asset> asset = retrieveAsset();
	std::string maintenancePersion;
	_display << "please input the maintenance person's name"<<std::endl;
	_input >> maintenancePersion;
	Date Timestamp=inputDate();
	asset->setMaintenanceRecord(Timestamp, maintenancePersion);
}

void MenuInterface::listAssetsByType() {
  // TODO: implement this member function.
	_display << "List asset by type" << std::endl;
	_display << "List (a)ll assets" << std::endl;
	_display << "List (c)omputers" << std::endl;
	_display << "List (p)hones" << std::endl;
	_display << "List (t)elevision" << std::endl;
	_display << "(b)ack to main menu" << std::endl;

	AssetRegister &am = AssetRegister::instance();
	auto assets = am.getAssets();
	char selection = getCharacterInput();
	_display << "ID\tBrand\tModel\tPurchase Price\tPurchase Date\tserial" << std::endl;
	switch (selection) {
	case 'a':
		for (auto asset : assets) {
			auto assetPtr = asset.second;
			_display << assetPtr->id() << "\t" << assetPtr->brand() << "\t" << assetPtr->model() << "\t"
				<< assetPtr->purchasePrice() << "\t\t" << assetPtr->purchaseDate().format() 
				<< "\t" <<assetPtr->serial() << std::endl;
		}
		break;
	case 'c':
		for (auto asset : assets) {
			if (asset.second->assetType() == 1) {
				std::shared_ptr<Computer> computer = std::dynamic_pointer_cast<Computer>(asset.second);
				_display << computer->id() << "\t" << computer->brand() << "\t" << computer->model() << "\t"
					<< computer->purchasePrice() << "\t\t" << computer->purchaseDate().format() 
					<< "\t" << computer->serial() << std::endl;
			}
		}
		break;
	case 'p':
		for (auto asset : assets) {
			if (asset.second->assetType() == 2) {
				std::shared_ptr<Phone> phone = std::dynamic_pointer_cast<Phone>(asset.second);
				_display << phone->id() << "\t" << phone->brand() << "\t" << phone->model() << "\t"
					<< phone->purchasePrice() << "\t\t" << phone->purchaseDate().format() 
					<< "\t" << phone->serial() << std::endl;
			}
		}
		break;
	case 't':
		for (auto asset : assets) {
			if (asset.second->assetType() == 3) {
				std::shared_ptr<Television> television = std::dynamic_pointer_cast<Television>(asset.second);
				_display << television->id() << "\t" << television->brand() << "\t" << television->model() << "\t"
					<< television->purchasePrice() << "\t\t" << television->purchaseDate().format() 
					<< "\t" << television->serial() << std::endl;
			}
		}
		break;
	case 'b': {
		displayMainMenu();
		break;
	}
	default:
		_display << "Sorry, \'" << selection << "\' is not a valid option, please try again."
			<< std::endl;
	}
}

void MenuInterface::listAssetsByCustodian() {
  // TODO: implement this member function.
	std::string name;
	std::vector<std::string> assetIdVector;
	_display << "please input the Custodian person name:" << std::endl;
	_input >> name;
	AssetRegister &am = AssetRegister::instance();
	assetIdVector = am.CustodianMapId(name);
	if (!assetIdVector.empty()) {
		_display << "ID\tBrand\tModel\tPurchase Price\tPurchase Date\tserial" << std::endl;
		for (auto assetId : assetIdVector) {
			auto assetPtr = am.retrieveAsset(assetId);
			_display << assetPtr->id() << "\t" << assetPtr->brand() << "\t" << assetPtr->model() << "\t"
				<< assetPtr->purchasePrice() << "\t\t" << assetPtr->purchaseDate().format()
				<< "\t" << assetPtr->serial() << std::endl;
		}
	}
	else
		_display << name << "isn't a custodian." << std::endl;
}

void MenuInterface::findAsset() {
  // TODO: implement this member function.
	AssetRegister &am = AssetRegister::instance();
	auto assets = am.getAssets();
	std::shared_ptr<Asset> asset = findMenu();
	displayAsset(asset);
}

Date MenuInterface::inputDate() {
	Date result;
	bool rewrite2 = false;
	do {
		_display << "please input the message of Date:(day[1-31]/month[1-12]/year[>1900])" << std::endl;
		int day, year, months;
		_input >> day >> months >> year;
		Date::Month month = (Date::Month)(months-1);
		Date temp(day, month, year);
		result = temp;
		rewrite2 = !result.valid();
	} while (rewrite2);
	return result;
}

Custodian MenuInterface::inputCustodian() {
	_display << "please input the message of Custodian" << std::endl;
	_display<<"name: department: phone: " << std::endl;
	std::string name, department, phone;
	_input >> name >> department >> phone;
	_display << "please input the Employment Start Date" << std::endl;
	Date employmentStartDate = inputDate();
	Custodian custodian(name, department, phone, employmentStartDate);
	return custodian;
}

std::shared_ptr<Asset> MenuInterface::retrieveAsset() {
	_display << "please input the id of the asset" << std::endl;
	std::string id;
	_input >> id;
	AssetRegister &am = AssetRegister::instance();
	std::shared_ptr<Asset> asset = am.retrieveAsset(id);
	return asset;
}

std::shared_ptr<Asset> MenuInterface::retrieveAssetBySerial() {
	_display << "please input the serial of the asset" << std::endl;
	std::string serial;
	_input >> serial;
	AssetRegister &am = AssetRegister::instance();
	std::shared_ptr<Asset> asset = am.retrieveAssetBySerial(serial);
	return asset;
}

void MenuInterface::maintenanceDetail(std::shared_ptr<Asset> asset) {
	_display << "MenuInterface History for asset" << asset->id()<<std::endl;
	if (!asset->getMaintenanceRecord().empty())
		for (auto recode : asset->getMaintenanceRecord())
			_display << " - " << recode.timeStamp().format() << " by " 
			         << recode.maintenancePersonName() << std::endl;
	else {
		_display << "no maintenanceRcode!" << std::endl;
	}
	_display << "(r)eturn to asset detail" << std::endl;
	_display << "(b)ack to main menu" << std::endl;
	char selection = getCharacterInput();
	switch (selection) {
	case 'r': {
		displayAsset(asset);
		break;
	}
	case 'b': {
		displayMainMenu();
		break;
	}
	default:
		_display << "Sorry, \'" << selection << "\' is not a valid option, please try again."
			<< std::endl;
	}
}

void MenuInterface::custodianDetails(std::shared_ptr<Asset> asset) {
	if (asset->custodian().name() == "undefined")
		_display << "custodian undefined!" << std::endl;
	else {
		std::string Month[] = {
			"January" , "February" , "March" , "April" , "May" , "June" , "July ",
			"August" , "September" ,"October" , "November" ,"December"
		};
		_display << "custodian for asset" << asset->id() << std::endl;
		_display << "Name:\t\t\t" << asset->custodian().name() << std::endl;
		_display << "Date of Employment:\t" << asset->custodian().employmentStartDate().day() << " "
			<< Month[asset->custodian().employmentStartDate().month()] << " "
			<< asset->custodian().employmentStartDate().year() << std::endl;
		_display << "Depatrment:\t\t" << asset->custodian().department() << std::endl;
	}
	_display << "(r)eturn to asset detail" << std::endl;
	_display << "(b)ack to main menu" << std::endl;
	char selection = getCharacterInput();
	switch (selection) {
	case 'r': {
		displayAsset(asset);
		break;
	}
	case 'b': {
		break;
	}
	default:
		_display << "Sorry, \'" << selection << "\' is not a valid option, please try again."
			<< std::endl;
	}
}

std::shared_ptr<Asset> MenuInterface::findMenu() {
	_display << "Find asset" << std::endl;
	_display << " search by (a)sset id" << std::endl;
	_display << " search by (s)erial" << std::endl;
	_display << " (b)ack to main menu" << std::endl;
	char selection = getCharacterInput();
	switch (selection) {
	case 'a': {
		std::shared_ptr<Asset> asset = retrieveAsset();
		return asset;
	}
	case 's': {
		std::shared_ptr<Asset> asset = retrieveAssetBySerial();
		return asset;
	}
	case 'b': {
		return nullptr;
	}
	default:
		_display << "Sorry, \'" << selection << "\' is not a valid option, please try again."
			<< std::endl;
		return nullptr;
	}
}

void MenuInterface::displayAsset(std::shared_ptr<Asset> asset) {
	Date currentDay;
	currentDay.getCurrentDate();
	if (asset == nullptr)
		_display << "NULL!" << std::endl;
	else {
		_display << "Asset ID:\t\t" << asset->id() << std::endl;
		_display << "Brand:\t\t\t" << asset->brand() << std::endl;
		_display << "Model:\t\t\t" << asset->model() << std::endl;
		_display << "Purchase Price:\t\t$" << asset->purchasePrice() << std::endl;
		_display << "Purchase Date:\t\t" << asset->purchaseDate().format() << std::endl;
		if (!asset->getDispose()) {

			switch (asset->assetType()) {
			case 1: {
				std::shared_ptr<Computer> computer = std::dynamic_pointer_cast<Computer>(asset);
				_display << "Depreciated Value:\t$" << asset->purchasePrice() - computer->calculateDepreciation(currentDay)
					<< " (depreciation of $" << computer->calculateDepreciation(currentDay) << " at "
					<< currentDay.format() << ")" << std::endl;
				_display << "Serial Number:\t\t" << computer->serial() << std::endl;
				_display << "Network Identifier:\t" << computer->networkIdentifier() << std::endl;
				_display << "Operating System:\t" << computer->operatingSystem() << std::endl;
				_display << "Custodian:\t\t" << computer->custodian().name() << std::endl;
				break;
			}
			case 2: {
				std::shared_ptr<Phone> phone = std::dynamic_pointer_cast<Phone>(asset);
				_display << "Depreciated Value:\t$" << asset->purchasePrice() - phone->calculateDepreciation(currentDay)
					<< " (depreciation of $" << phone->calculateDepreciation(currentDay) << " at "
					<< currentDay.format() << ")" << std::endl;
				_display << "Serial Number:\t\t" << phone->serial() << std::endl;
				_display << "Phone Number:\t\t" << phone->phoneNumber() << std::endl;
				_display << "Operating System:\t" << phone->operatingSystem() << std::endl;
				_display << "Billing Identifier:\t" << phone->billingIdentifier() << std::endl;
				_display << "Custodian:\t\t" << phone->custodian().name() << std::endl;
				break;
			}
			case 3: {
				std::shared_ptr<Television> television = std::dynamic_pointer_cast<Television>(asset);
				_display << "Depreciated Value:\t$" << asset->purchasePrice() - television->calculateDepreciation(currentDay)
					<< " (depreciation of $" << television->calculateDepreciation(currentDay) << " at "
					<< currentDay.format() << ")" << std::endl;
				_display << "Serial Number:\t\t" << television->serial() << std::endl;
				_display << "Location:\t\t" << television->location() << std::endl;
				break;
			}
			}
			if (!asset->getMaintenanceRecord().empty())
				_display << "Last Maintenance:\t" << asset->getMaintenanceRecord().back().timeStamp().format()
				<< " by " << asset->getMaintenanceRecord().back().maintenancePersonName() << std::endl;
			_display << "(c)ustodian details" << std::endl;
		}
		else {
			_display << "Disposal Date\t" << asset->disposalDate().format() << std::endl;
			switch (asset->assetType()) {
			case 1: {
				std::shared_ptr<Computer> computer = std::dynamic_pointer_cast<Computer>(asset);
				_display << "Depreciated Value:\t$" << asset->purchasePrice() - computer->calculateDepreciation(currentDay)
					<< " (depreciation of $" << computer->calculateDepreciation(currentDay) << " at "
					<< currentDay.format() << ")" << std::endl;
				break;
			}
			case 2: {
				std::shared_ptr<Phone> phone = std::dynamic_pointer_cast<Phone>(asset);
				_display << "Depreciated Value:\t$" << asset->purchasePrice() - phone->calculateDepreciation(currentDay)
					<< " (depreciation of $" << phone->calculateDepreciation(currentDay) << " at "
					<< currentDay.format() << ")" << std::endl;
				break;
			}
			case 3: {
				std::shared_ptr<Television> television = std::dynamic_pointer_cast<Television>(asset);
				_display << "Depreciated Value:\t$" << asset->purchasePrice() - television->calculateDepreciation(currentDay)
					<< " (depreciation of $" << television->calculateDepreciation(currentDay) << " at "
					<< currentDay.format() << ")" << std::endl;
				break;
			}
			}
			if (!asset->getMaintenanceRecord().empty())
				_display << "Last Maintenance:\t" << asset->getMaintenanceRecord().back().timeStamp().format()
				<< " by " << asset->getMaintenanceRecord().back().maintenancePersonName() << std::endl;
		}
		_display << " (m)aintenance history" << std::endl;
		_display << " (b)ack to main menu" << std::endl;
		char selection2 = getCharacterInput();
		switch (selection2) {
		case 'c':
			custodianDetails(asset);
			break;
		case 'm':
			maintenanceDetail(asset);
			break;
		case 'b':
			displayMainMenu();
			break;
		}
	}
}



