#include "menuinterface.h"
#include "assetregister.h"
#include <limits>

MenuInterface::MenuInterface(std::ostream &display, std::istream &input)
    : _display{display}, _input{input} {
}

void MenuInterface::displayMainMenu() const {
  _display << "What would you like to do?" << std::endl;
  _display << " (a)dd an asset" << std::endl;
  _display << " (d)ispose an asset" << std::endl;
  _display << " (l)ist assets by type" << std::endl;
  _display << " List assets by (c)ustodian" << std::endl;
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
}

void MenuInterface::disposeAsset() {
  // TODO: implement this member function.
}

void MenuInterface::updateAsset() {
  // TODO: implement this member function.
}

void MenuInterface::addMaintenance() {
  // TODO: implement this member function.
}

void MenuInterface::listAssetsByType() {
  // TODO: implement this member function.
}

void MenuInterface::listAssetsByCustodian() {
  // TODO: implement this member function.
}

void MenuInterface::findAsset() {
  // TODO: implement this member function.
}
