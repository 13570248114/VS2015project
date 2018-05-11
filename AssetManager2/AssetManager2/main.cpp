#include "menuinterface.h"
#include <iostream>
#include"date.h"

/**
 * @brief main simple main function runs the MenuInterface until quit.
 * @return
 */
int main() {

  MenuInterface m{std::cout, std::cin};
  m.displayMainMenu();
  while (m.processSelection(m.getCharacterInput())) {
    m.displayMainMenu();
  }
  
  return 0;
}
