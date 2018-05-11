#include "assetregister.h"

AssetRegister &AssetRegister::instance() {
  static AssetRegister s_instance;
  return s_instance;
}

std::shared_ptr<Asset> AssetRegister::retrieveAsset(const std::string &assetId) {
  auto assetIt = _assets.find(assetId);
  if (assetIt != _assets.end()) {
    return assetIt->second;
  }
  return nullptr;
}

std::shared_ptr<Asset> AssetRegister::retrieveAssetBySerial(const std::string &serial) {
	for (auto assetSerial : _assets)
		if (assetSerial.second->serial() == serial)
			return assetSerial.second;
	return nullptr;
}

bool AssetRegister::storeAsset(std::shared_ptr<Asset> asset) {
  if (!_assets.count(asset->id())) {
    _assets[asset->id()] = std::shared_ptr<Asset>{asset};
    return true;
  }
  return false;
}

AssetRegister::AssetRegister() {
}

const std::map<std::string, std::shared_ptr<Asset>> &AssetRegister::getAssets() const {
	return _assets;
}

std::vector<std::string> AssetRegister::CustodianMapId(const std::string &custodianName) {
	std::vector<std::string> assetIdVector;
	auto entries = _custodianMap.count(custodianName);
	auto iter = _custodianMap.find(custodianName);
	while (entries) {
		assetIdVector.push_back(iter->second);
		++iter;
		--entries;
	}
	return assetIdVector;
}
void AssetRegister::stortCustodianMap(std::string custodianName, std::string assetId) {
	_custodianMap.insert({ custodianName ,assetId });
}