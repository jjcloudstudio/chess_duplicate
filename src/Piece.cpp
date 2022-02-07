#include "Piece.h"
#include <typeinfo>

bool Piece::isValidMove(Coordinate* start, Coordinate* destination, std::vector<std::vector<Piece*>>* board) {
    throw std::runtime_error("Unknown piece.");
}

bool Piece::operator==(const Piece& p) const {
    return side == p.getSide() && typeid(this) == typeid(p);
}

Colour Piece::getSide() const {
    return side;
}
