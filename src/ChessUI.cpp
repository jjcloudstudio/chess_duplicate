#include "ChessUI.h"
#include <iostream>

std::string ChessUI::getLocation(Colour side, const std::string desc) {
  std::string input;

  std::string player = (side == Colour::WHITE) ? "White" : "Black";
  std::cout << "[" + player + "]: Enter location " << desc;
  std::cin >> input;
  return input;
}

void ChessUI::invalidMove(const std::runtime_error& e) {
  std::cerr << e.what() << std::endl;
}

void ChessUI::gameOver(Colour side) {
  std::cout << "Game over! " << ((side == Colour::WHITE) ? "White" : "Black") << " has lost all of their pawns.";
}
