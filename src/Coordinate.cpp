#include "Coordinate.h"

Coordinate::Coordinate(std::string s){
    if(s.size() != 2)
      throw invalid_location_error("Too many or too few dimensions.");

    x = toupper(s[0]) - 'A';
    y = s[1] - '1';
}
